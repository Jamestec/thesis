/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * \file
 *   This file contains the source code for the SPEEDTEST App.
 */

/*
** Include Files:
*/
#include "speedtest_app_events.h"
#include "speedtest_app_version.h"
#include "speedtest_app.h"
#include "speedtest_app_table.h"

#include <string.h>

#include "fpgam_lib.h"
#include "mmio_lib.h"

/*
** global data
*/
SPEEDTEST_APP_Data_t SPEEDTEST_APP_Data;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/* SPEEDTEST_APP_Main() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SPEEDTEST_APP_Main(void)
{
    int32            status;
    CFE_SB_Buffer_t *SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(SPEEDTEST_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = SPEEDTEST_APP_Init();
    if (status != CFE_SUCCESS)
    {
        SPEEDTEST_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** SPEEDTEST Runloop
    */
    while (CFE_ES_RunLoop(&SPEEDTEST_APP_Data.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(SPEEDTEST_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, SPEEDTEST_APP_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(SPEEDTEST_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            SPEEDTEST_APP_ProcessCommandPacket(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(SPEEDTEST_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SPEEDTEST APP: SB Pipe Read Error, App Will Exit");

            SPEEDTEST_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(SPEEDTEST_APP_PERF_ID);

    CFE_ES_ExitApp(SPEEDTEST_APP_Data.RunStatus);

} /* End of SPEEDTEST_APP_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SPEEDTEST_APP_Init() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 SPEEDTEST_APP_Init(void)
{
    int32 status;

    SPEEDTEST_APP_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    SPEEDTEST_APP_Data.CmdCounter = 0;
    SPEEDTEST_APP_Data.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    SPEEDTEST_APP_Data.PipeDepth = SPEEDTEST_APP_PIPE_DEPTH;

    strncpy(SPEEDTEST_APP_Data.PipeName, "SPEEDTEST_APP_CMD_PIPE", sizeof(SPEEDTEST_APP_Data.PipeName));
    SPEEDTEST_APP_Data.PipeName[sizeof(SPEEDTEST_APP_Data.PipeName) - 1] = 0;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(CFE_MSG_PTR(SPEEDTEST_APP_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(SPEEDTEST_APP_HK_TLM_MID),
                 sizeof(SPEEDTEST_APP_Data.HkTlm));

	// Init CMD BinFile packet
	CFE_MSG_Init(CFE_MSG_PTR(SPEEDTEST_APP_Data.BinFile_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(SPEEDTEST_APP_Data.BinFile_Pkt));
	
	// Init Input packet
	CFE_MSG_Init(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SPEEDTEST_APP_CMD_MID),
                 sizeof(SPEEDTEST_APP_Data.Input_Pkt));

	// Init input output telem counter
	SPEEDTEST_APP_Data.In_Count = 0;
	SPEEDTEST_APP_Data.Out_Count = 0;

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&SPEEDTEST_APP_Data.CommandPipe, SPEEDTEST_APP_Data.PipeDepth, SPEEDTEST_APP_Data.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SPEEDTEST_APP_SEND_HK_MID), SPEEDTEST_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SPEEDTEST_APP_CMD_MID), SPEEDTEST_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    /*
    ** Register Table(s)
    */
    status = CFE_TBL_Register(&SPEEDTEST_APP_Data.TblHandles[0], "STAppTable", sizeof(SPEEDTEST_APP_Table_t),
                              CFE_TBL_OPT_DEFAULT, SPEEDTEST_APP_TblValidationFunc);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error Registering Table, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }
    else
    {
        status = CFE_TBL_Load(SPEEDTEST_APP_Data.TblHandles[0], CFE_TBL_SRC_FILE, SPEEDTEST_APP_TABLE_FILE);
    }

    CFE_EVS_SendEvent(SPEEDTEST_APP_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "SPEEDTEST App Initialized.%s",
                      SPEEDTEST_APP_VERSION_STRING);

    return (CFE_SUCCESS);

} /* End of SPEEDTEST_APP_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SPEEDTEST_APP_ProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the SPEEDTEST    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SPEEDTEST_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case SPEEDTEST_APP_CMD_MID:
            SPEEDTEST_APP_ProcessGroundCommand(SBBufPtr);
            break;

        case SPEEDTEST_APP_SEND_HK_MID:
            SPEEDTEST_APP_ReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(SPEEDTEST_APP_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SPEEDTEST App: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End SPEEDTEST_APP_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SPEEDTEST_APP_ProcessGroundCommand() -- SPEEDTEST ground commands                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SPEEDTEST_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    /*
    ** Process "known" SPEEDTEST app ground commands
    */
    switch (CommandCode)
    {
        case SPEEDTEST_APP_NOOP_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_NoopCmd_t)))
            {
                SPEEDTEST_APP_Noop((SPEEDTEST_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case SPEEDTEST_APP_NOSB_PSPL_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_NoSB_PSPL_t)))
            {
                SPEEDTEST_APP_NoSB_PSPL((SPEEDTEST_APP_NoSB_PSPL_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_NOSB_PLPS_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_NoSB_PLPS_t)))
            {
                SPEEDTEST_APP_NoSB_PLPS((SPEEDTEST_APP_NoSB_PLPS_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_SELFSB_PSPL_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_SelfSB_PSPL_t)))
            {
                SPEEDTEST_APP_SelfSB_PSPL((SPEEDTEST_APP_SelfSB_PSPL_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_SELFSB_PSPL_R_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_Input_t)))
            {
                SPEEDTEST_APP_SelfSB_PSPL_R((SPEEDTEST_APP_Input_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_SELFSB_PLPS_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_SelfSB_PLPS_t)))
            {
                SPEEDTEST_APP_SelfSB_PLPS((SPEEDTEST_APP_SelfSB_PLPS_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_SELFSB_PLPS_R_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_Input_t)))
            {
                SPEEDTEST_APP_SelfSB_PLPS_R((SPEEDTEST_APP_Input_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_CONTROLSN_PSPL_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_ControlSB_PSPL_t)))
            {
                SPEEDTEST_APP_ControlSB_PSPL((SPEEDTEST_APP_ControlSB_PSPL_t *)SBBufPtr);
            }
            break;

		case SPEEDTEST_APP_CONTROLPSPL_CC:
            if (SPEEDTEST_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SPEEDTEST_APP_ControlSB_PLPS_t)))
            {
                SPEEDTEST_APP_ControlSB_PLPS((SPEEDTEST_APP_ControlSB_PLPS_t *)SBBufPtr);
            }
			break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(SPEEDTEST_APP_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SPEEDTEST App: Invalid ground command code: CC = %d", CommandCode);
            break;
    }

    return;

} /* End of SPEEDTEST_APP_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SPEEDTEST_APP_ReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SPEEDTEST_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg)
{

    /*
    ** Get command execution counters...
    */
    SPEEDTEST_APP_Data.HkTlm.Payload.CommandErrorCounter = SPEEDTEST_APP_Data.ErrCounter;
    SPEEDTEST_APP_Data.HkTlm.Payload.CommandCounter      = SPEEDTEST_APP_Data.CmdCounter;

	/*
	** Do other housekeeping...
	*/
	for (int i = 0; i < 200; i++) {
		SPEEDTEST_APP_Data.HkTlm.Payload.Inputs[i] = '\0';
		SPEEDTEST_APP_Data.HkTlm.Payload.Outputs[i] = '\0';
	}
	char *inputs = SPEEDTEST_APP_Data.HkTlm.Payload.Inputs;
	char *outputs = SPEEDTEST_APP_Data.HkTlm.Payload.Outputs;
	*inputs++ = '[';
	*outputs++ = '[';
	if (SPEEDTEST_APP_Data.In_Count > 0) {
		for (int i = 0; i < SPEEDTEST_APP_Data.In_Count; i++) {
			inputs = inputs + snprintf(inputs, 18, "%0.3f MB/s, ", SPEEDTEST_APP_Data.Inputs[i]);
		}
		*--inputs = '\0';
		*--inputs = ']';
	} else {
		*inputs++ = ']';
		*inputs++ = '\0';
	}
	if (SPEEDTEST_APP_Data.Out_Count > 0) {
		for (int i = 0; i < SPEEDTEST_APP_Data.Out_Count; i++) {
			outputs = outputs + snprintf(outputs, 18, "%0.3f MB/s, ", SPEEDTEST_APP_Data.Outputs[i]);
		}
		*--outputs = '\0';
		*--outputs = ']';
	} else {
		*outputs++ = ']';
		*outputs++ = '\0';
	}

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (int i = 0; i < SPEEDTEST_APP_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(SPEEDTEST_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;

} /* End of SPEEDTEST_APP_ReportHousekeeping() */





int32 SPEEDTEST_APP_Noop(const SPEEDTEST_APP_NoopCmd_t *Msg)
{

    SPEEDTEST_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(SPEEDTEST_APP_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "SPEEDTEST: NOOP command %s, %d",
                      SPEEDTEST_APP_VERSION, SPEEDTEST_APP_Data.CmdCounter);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_Reset(const SPEEDTEST_APP_NoSB_PSPL_t *Msg)
{

    SPEEDTEST_APP_Data.CmdCounter = 0;
    SPEEDTEST_APP_Data.ErrCounter = 0;

    CFE_EVS_SendEvent(SPEEDTEST_APP_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "SPEEDTEST: RESET command");

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_NoSB_PSPL(SPEEDTEST_APP_NoSB_PSPL_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/PSPL.bin";
	program_pl(bin, 0);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	int32 *reset = mapped;
	int32 *max = mapped + 1;
	int32 *data_in = mapped + 2;
	int32 *data_out = mapped + 3;
	*reset = 1;
	*max = TIME_CLK;
	*data_in = 0;
	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Testing cFS to PL speed over %d seconds...", TIME_S);
	const int32 rounds = (TIME_CLK / 17 / 2) + 1000;
	*reset = 0;
	for (int32 i = 0; i < rounds; i++) {
		*data_in = -1;
		*data_in = 0;
	}

	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"%d transfers of 31bits happened in %d seconds", *data_out, TIME_S);
	double pl_clk = (double)TIME_CLK / (double)*data_out;
	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Average PL clock cycles per transfer: %.2f", pl_clk);
	double speed = ((double)*data_out * 31) / 8 / 1000 / 1000 / TIME_S;
	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"cFS to PL speed = %.2f MB/s", speed);

	mmio_lib_DeleteMapping(mapping, newSize);

	// Housekeeping
	// Make space
	for (int32 i = SPEEDTEST_APP_Data.In_Count; i > 0; i--) {
		SPEEDTEST_APP_Data.Inputs[i] = SPEEDTEST_APP_Data.Inputs[i-1];
	}
	// Increase count
	if (SPEEDTEST_APP_Data.In_Count < SPEEDTEST_APP_INOUT_BUFFER_LEN-1) {
		SPEEDTEST_APP_Data.In_Count = SPEEDTEST_APP_Data.In_Count + 1;
	}
	SPEEDTEST_APP_Data.Inputs[0] = speed;

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_NoSB_PLPS(SPEEDTEST_APP_NoSB_PLPS_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/PSPL.bin";
	program_pl(bin, 0);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	int32 *reset = mapped;
	int32 *max = mapped + 1;
	int32 *data_in = mapped + 2;
	int32 *data_out = mapped + 3;
	*reset = 1;
	*max = TIME_CLK;
	*data_in = 0;
    CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PLPS_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Testing PL to cFS speed over %d seconds...", TIME_S);
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), SPEEDTEST_APP_SELFSB_PSPL_R_CC);
	const int32 rounds = (TIME_CLK / 17 / 4) + 1000;
	*reset = 0;
	for (int32 i = 0; i < rounds; i++) {
		*data_in = -1;
		*data_in = -500;
		*data_in = 0;
		*data_in = 500;
	}

	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PLPS_INF_EID, CFE_EVS_EventType_INFORMATION,
		"%d transfers of 32bits happened in %d seconds", *data_out, TIME_S);
	double pl_clk = (double)TIME_CLK / (double)*data_out;
	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PLPS_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Average PL clock cycles per transfer: %.2f", pl_clk);
	double speed = ((double)*data_out * 32) / 8 / 1000 / 1000 / TIME_S;
	CFE_EVS_SendEvent(SPEEDTEST_APP_NOSB_PLPS_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL to cFS speed = %.2f MB/s", speed);

	mmio_lib_DeleteMapping(mapping, newSize);

	// Housekeeping
	// Make space
	for (int32 i = SPEEDTEST_APP_Data.Out_Count; i > 0; i--) {
		SPEEDTEST_APP_Data.Outputs[i] = SPEEDTEST_APP_Data.Outputs[i-1];
	}
	// Increase count
	if (SPEEDTEST_APP_Data.Out_Count < SPEEDTEST_APP_INOUT_BUFFER_LEN-1) {
		SPEEDTEST_APP_Data.Out_Count = SPEEDTEST_APP_Data.Out_Count + 1;
	}
	SPEEDTEST_APP_Data.Outputs[0] = speed;

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_SelfSB_PSPL(SPEEDTEST_APP_SelfSB_PSPL_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/PSPL.bin";
	program_pl(bin, 0);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	int32 *reset = mapped;
	int32 *max = mapped + 1;
	int32 *data_in = mapped + 2;

	*reset = 1;
	*max = TIME_CLK;
	*data_in = 0;
    CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Testing Software Bus PS to PL speed over %d seconds...", TIME_S);
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), SPEEDTEST_APP_SELFSB_PSPL_R_CC);
	const int32 rounds = (TIME_CLK / 11000);
	*reset = 0;
	SPEEDTEST_APP_Data.Input_Pkt.Payload.number = rounds;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), true);

	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_SelfSB_PSPL_R(SPEEDTEST_APP_Input_t *Msg)
{

	SPEEDTEST_APP_Input_Payload_t *Payload = &(Msg->Payload);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	if (Payload->number > 0) {
		int32 *data_in = mapped + 2;
		if (Payload->number % 2 == 0) {
			*data_in = -1;
		} else {
			*data_in = 0;
		}
		SPEEDTEST_APP_Data.Input_Pkt.Payload.number = SPEEDTEST_APP_Data.Input_Pkt.Payload.number - 1;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), true);
	} else {
		int32 *data_out = mapped + 3;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"%d transfers of 31bits happened in %d seconds", *data_out, TIME_S);
		double pl_clk = (double)TIME_CLK / (double)*data_out;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Average PL clock cycles per transfer: %.2f", pl_clk);
		double speed = ((double)*data_out * 31) / 8 / 1000 / 1000 / TIME_S;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Software Bus PS to PL speed = %.3f MB/s", speed);

		// Housekeeping
		// Make space
		for (int32 i = SPEEDTEST_APP_Data.In_Count; i > 0; i--) {
			SPEEDTEST_APP_Data.Inputs[i] = SPEEDTEST_APP_Data.Inputs[i-1];
		}
		// Increase count
		if (SPEEDTEST_APP_Data.In_Count < SPEEDTEST_APP_INOUT_BUFFER_LEN-1) {
			SPEEDTEST_APP_Data.In_Count = SPEEDTEST_APP_Data.In_Count + 1;
		}
		SPEEDTEST_APP_Data.Inputs[0] = speed;
	}
	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_SelfSB_PLPS(SPEEDTEST_APP_SelfSB_PLPS_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/PSPL.bin";
	program_pl(bin, 0);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	int32 *reset = mapped;
	int32 *max = mapped + 1;
	int32 *data_in = mapped + 2;

	*reset = 1;
	*max = TIME_CLK;
	*data_in = 0;
    CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Testing Software Bus PL to PS speed over %d seconds...", TIME_S);
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), SPEEDTEST_APP_SELFSB_PLPS_R_CC);
	const int32 rounds = (TIME_CLK / 11000);
	*reset = 0;
	SPEEDTEST_APP_Data.Input_Pkt.Payload.number = rounds;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), true);

	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_SelfSB_PLPS_R(SPEEDTEST_APP_Input_t *Msg)
{

	SPEEDTEST_APP_Input_Payload_t *Payload = &(Msg->Payload);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int32 *mapped = mapping;
	if (Payload->number > 0) {
		int32 *data_in = mapped + 2;
		switch (Payload->number % 4)
		{
			case 0:
				*data_in = -1;
				break;
			case 1:
				*data_in = -500;
				break;
			case 2:
				*data_in = 0;
				break;
			default: //3
				*data_in = 500;
				break;
		}
		SPEEDTEST_APP_Data.Input_Pkt.Payload.number = SPEEDTEST_APP_Data.Input_Pkt.Payload.number - 1;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.Input_Pkt.CmdHeader), true);
	} else {
		int32 *data_out = mapped + 3;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"%d transfers of 32bits happened in %d seconds", *data_out, TIME_S);
		double pl_clk = (double)TIME_CLK / (double)*data_out;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Average PL clock cycles per transfer: %.2f", pl_clk);
		double speed = ((double)*data_out * 32) / 8 / 1000 / 1000 / TIME_S;
		CFE_EVS_SendEvent(SPEEDTEST_APP_SELFSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Software Bus PL to PS speed = %.3f MB/s", speed);

		// Housekeeping
		// Make space
		for (int32 i = SPEEDTEST_APP_Data.In_Count; i > 0; i--) {
			SPEEDTEST_APP_Data.Inputs[i] = SPEEDTEST_APP_Data.Inputs[i-1];
		}
		// Increase count
		if (SPEEDTEST_APP_Data.In_Count < SPEEDTEST_APP_INOUT_BUFFER_LEN-1) {
			SPEEDTEST_APP_Data.In_Count = SPEEDTEST_APP_Data.In_Count + 1;
		}
		SPEEDTEST_APP_Data.Inputs[0] = speed;
	}
	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_ControlSB_PSPL (SPEEDTEST_APP_ControlSB_PSPL_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/count1.bin";
	program_pl(bin, 0);

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int *mapped = mapping;
	int *start = mapped + 1;
	int *input = mapped + 2;
	int *count_out = mapped + 3;
	int results[20];
	for (int i=100;i<120;i++) {
		*mapped = 1;
		*mapped = 0;
		*input = i;
		*start = 1;
		*start = 0;
		results[i-100] = *count_out;
	}
	mmio_lib_DeleteMapping(mapping, newSize);

	char string[200];
	for (int i = 0; i < 200; i++) {
		string[i] = '\0';;
	}
	char *outputs = string;
	*outputs++ = '[';
	for (int i = 0; i < 20; i++) {
		outputs = outputs + snprintf(outputs, 6, "%d, ", results[i]);
	}
	*--outputs = '\0';
	*--outputs = ']';


	CFE_EVS_SendEvent(SPEEDTEST_APP_CONTROLSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
		"cFS next instruction delay in PL clock cycles:\n%s", string);

    return CFE_SUCCESS;

}

int32 SPEEDTEST_APP_ControlSB_PLPS (SPEEDTEST_APP_ControlSB_PLPS_t *Msg)
{

	char bin[] = "/home/ubuntu/bitstreams/count1.bin";
	program_pl(bin, 0);

	// Test send SB message speed
	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int *mapped = mapping;
	int *start = mapped + 1;
	int *input = mapped + 2;
	int *count_out = mapped + 3;
	//int *done = mapped + 4;
	//int d = -1;
	int c_o = -1;
	int nums[20];
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SPEEDTEST_APP_Data.NoArgs_Pkt.CmdHeader), SPEEDTEST_APP_NOOP_CC);
	for (int i = 20000; i < 20005; i++) {
		*mapped = 1;
		*start = 0;
		*mapped = 0;
		*input = i;
		*start = 1;
		SPEEDTEST_APP_Data.Input_Pkt.Payload.number = i;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SPEEDTEST_APP_Data.NoArgs_Pkt.CmdHeader), true);
		*start = 0;
		c_o = *count_out;
		nums[i-20000] = c_o;
	}
	for (int i = 0; i < 5; i++) {
		CFE_EVS_SendEvent(SPEEDTEST_APP_CONTROLSB_PSPL_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Count_Test: i = %d, counter = %d\n", i+20000, nums[i]);
	}
	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

}




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SPEEDTEST_APP_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool SPEEDTEST_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
{
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(SPEEDTEST_APP_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SPEEDTEST App: Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        SPEEDTEST_APP_Data.ErrCounter++;
    }

    return (result);

} /* End of SPEEDTEST_APP_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SPEEDTEST_APP_TblValidationFunc -- Verify contents of First Table      */
/* buffer contents                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SPEEDTEST_APP_TblValidationFunc(void *TblData)
{
    int32               ReturnCode = CFE_SUCCESS;
    SPEEDTEST_APP_Table_t *TblDataPtr = (SPEEDTEST_APP_Table_t *)TblData;

    /*
    ** SPEEDTEST Table Validation
    */
    if (TblDataPtr->Int1 > SPEEDTEST_APP_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = SPEEDTEST_APP_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;

} /* End of SPEEDTEST_APP_TBLValidationFunc() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SPEEDTEST_APP_GetCrc -- Output CRC                                     */
/*                                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SPEEDTEST_APP_GetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SPEEDTEST App: Error Getting Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("SPEEDTEST App: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }

    return;

} /* End of SPEEDTEST_APP_GetCrc */
