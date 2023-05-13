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
 *   This file contains the source code for the FIR2 App.
 */

/*
** Include Files:
*/
#include "fir2_app_events.h"
#include "fir2_app_version.h"
#include "fir2_app.h"
#include "fir2_app_table.h"

#include <string.h>

#include "fpgam_lib.h"
#include "mmio_lib.h"

/*
** global data
*/
FIR2_APP_Data_t FIR2_APP_Data;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/* FIR2_APP_Main() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void FIR2_APP_Main(void)
{
    int32            status;
    CFE_SB_Buffer_t *SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(FIR2_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = FIR2_APP_Init();
    if (status != CFE_SUCCESS)
    {
        FIR2_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** FIR2 Runloop
    */
    while (CFE_ES_RunLoop(&FIR2_APP_Data.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(FIR2_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, FIR2_APP_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(FIR2_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            FIR2_APP_ProcessCommandPacket(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(FIR2_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR2 APP: SB Pipe Read Error, App Will Exit");

            FIR2_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(FIR2_APP_PERF_ID);

    CFE_ES_ExitApp(FIR2_APP_Data.RunStatus);

} /* End of FIR2_APP_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* FIR2_APP_Init() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 FIR2_APP_Init(void)
{
    int32 status;

    FIR2_APP_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    FIR2_APP_Data.CmdCounter = 0;
    FIR2_APP_Data.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    FIR2_APP_Data.PipeDepth = FIR2_APP_PIPE_DEPTH;

    strncpy(FIR2_APP_Data.PipeName, "FIR2_APP_CMD_PIPE", sizeof(FIR2_APP_Data.PipeName));
    FIR2_APP_Data.PipeName[sizeof(FIR2_APP_Data.PipeName) - 1] = 0;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(CFE_MSG_PTR(FIR2_APP_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(FIR2_APP_HK_TLM_MID),
                 sizeof(FIR2_APP_Data.HkTlm));

	// Init CMD BinFile packet
	CFE_MSG_Init(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR2_APP_Data.BinFile_Pkt));
	
	// Init Reset packet
	CFE_MSG_Init(CFE_MSG_PTR(FIR2_APP_Data.Reset_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR2_APP_Data.Reset_Pkt));
	
	// Init Input packet
	CFE_MSG_Init(CFE_MSG_PTR(FIR2_APP_Data.Input_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR2_APP_Data.Input_Pkt));

	// Init Release packet
	CFE_MSG_Init(CFE_MSG_PTR(FIR2_APP_Data.Release_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR2_APP_Data.Release_Pkt));

	// Init input output telem counter
	FIR2_APP_Data.InOut_Count = 0;

	// Init HasPL
	FIR2_APP_Data.HasPL = 0;

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&FIR2_APP_Data.CommandPipe, FIR2_APP_Data.PipeDepth, FIR2_APP_Data.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(FIR2_APP_SEND_HK_MID), FIR2_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(FIR2_APP_CMD_MID), FIR2_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    /*
    ** Register Table(s)
    */
    status = CFE_TBL_Register(&FIR2_APP_Data.TblHandles[0], "FIR2AppTable", sizeof(FIR2_APP_Table_t),
                              CFE_TBL_OPT_DEFAULT, FIR2_APP_TblValidationFunc);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error Registering Table, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }
    else
    {
        status = CFE_TBL_Load(FIR2_APP_Data.TblHandles[0], CFE_TBL_SRC_FILE, FIR2_APP_TABLE_FILE);
    }

    CFE_EVS_SendEvent(FIR2_APP_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR2 App Initialized.%s",
                      FIR2_APP_VERSION_STRING);

    return (CFE_SUCCESS);

} /* End of FIR2_APP_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  FIR2_APP_ProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the FIR2    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void FIR2_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case FIR2_APP_CMD_MID:
            FIR2_APP_ProcessGroundCommand(SBBufPtr);
            break;

        case FIR2_APP_SEND_HK_MID:
            FIR2_APP_ReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(FIR2_APP_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR2 App: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End FIR2_APP_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* FIR2_APP_ProcessGroundCommand() -- FIR2 ground commands                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void FIR2_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    /*
    ** Process "known" FIR2 app ground commands
    */
    switch (CommandCode)
    {
        case FIR2_APP_NOOP_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_NoopCmd_t)))
            {
                FIR2_APP_Noop((FIR2_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case FIR2_APP_RESET_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_ResetCmd_t)))
            {
                FIR2_APP_Reset((FIR2_APP_ResetCmd_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_FULLFIR1_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_FullFIR1_t)))
            {
                FIR2_APP_FullFIR1((FIR2_APP_FullFIR1_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_FULLFIR0_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_FullFIR0_t)))
            {
                FIR2_APP_FullFIR0((FIR2_APP_FullFIR0_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_PARTIALFIR1_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_PartialFIR1_t)))
            {
                FIR2_APP_PartialFIR1((FIR2_APP_PartialFIR1_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_PARTIALFIR0_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_PartialFIR0_t)))
            {
                FIR2_APP_PartialFIR0((FIR2_APP_PartialFIR0_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_INPUT_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_Input_t)))
            {
                FIR2_APP_Input((FIR2_APP_Input_t *)SBBufPtr);
            }
			break;

		case FIR2_APP_OUTPUT_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_Output_t)))
            {
                FIR2_APP_Output((FIR2_APP_Output_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_DELAY_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_NoopCmd_t)))
            {
                FIR2_APP_Delay((FIR2_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_RELEASE_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_NoopCmd_t)))
            {
                FIR2_APP_Release((FIR2_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

		case FIR2_APP_PL_REPLY_CC:
            if (FIR2_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR2_APP_Reply_t)))
            {
                FIR2_APP_PL_Reply((FIR2_APP_Reply_t *)SBBufPtr);
            }
            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(FIR2_APP_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR2 App: Invalid ground command code: CC = %d", CommandCode);
            break;
    }

    return;

} /* End of FIR2_APP_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  FIR2_APP_ReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 FIR2_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg)
{

    /*
    ** Get command execution counters...
    */
    FIR2_APP_Data.HkTlm.Payload.CommandErrorCounter = FIR2_APP_Data.ErrCounter;
    FIR2_APP_Data.HkTlm.Payload.CommandCounter      = FIR2_APP_Data.CmdCounter;
	for (int i = 0; i < 200; i++) {
		FIR2_APP_Data.HkTlm.Payload.Inputs[i] = '\0';
		FIR2_APP_Data.HkTlm.Payload.Outputs[i] = '\0';
	}
	char *inputs = FIR2_APP_Data.HkTlm.Payload.Inputs;
	char *outputs = FIR2_APP_Data.HkTlm.Payload.Outputs;
	*inputs++ = '[';
	*outputs++ = '[';
	if (FIR2_APP_Data.InOut_Count > 0) {
		for (int i = 0; i < FIR2_APP_Data.InOut_Count; i++) {
			inputs = inputs + snprintf(inputs, 12, "%d, ", FIR2_APP_Data.Inputs[i]);
			outputs = outputs + snprintf(outputs, 12, "%d, ", FIR2_APP_Data.Outputs[i]);
		}
		*--inputs = '\0';
		*--inputs = ']';
		*--outputs = '\0';
		*--outputs = ']';
	} else {
		*inputs++ = ']';
		*outputs++ = ']';
		*inputs++ = '\0';
		*outputs++ = '\0';
	}
	FIR2_APP_Data.HkTlm.Payload.HasPL = FIR2_APP_Data.HasPL;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(FIR2_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (int i = 0; i < FIR2_APP_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(FIR2_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;

} /* End of FIR2_APP_ReportHousekeeping() */





int32 FIR2_APP_Noop(const FIR2_APP_NoopCmd_t *Msg)
{

    FIR2_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(FIR2_APP_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR2: NOOP command %s, %d",
                      FIR2_APP_VERSION, FIR2_APP_Data.CmdCounter);

    return CFE_SUCCESS;

}

int32 FIR2_APP_Reset(const FIR2_APP_ResetCmd_t *Msg)
{

    FIR2_APP_Data.CmdCounter = 0;
    FIR2_APP_Data.ErrCounter = 0;
	FIR2_APP_Data.InOut_Count = 0;

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.Reset_Pkt.CmdHeader), PL_CONTROL_APP_RESET_CC);
	FIR2_APP_Data.Reset_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.Reset_Pkt.Payload.reset_offset = 2;
	FIR2_APP_Data.Reset_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.Reset_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.Reset_Pkt.CmdHeader), true);

    CFE_EVS_SendEvent(FIR2_APP_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR2: RESET command");

    return CFE_SUCCESS;

}

int32 FIR2_APP_FullFIR1 (FIR2_APP_FullFIR1_t *Msg)
{

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_FULL_PROGRAM_CC);
	strcpy(FIR2_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir1.bin");
	FIR2_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
	FIR2_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
	FIR2_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
	FIR2_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), true);
	FIR2_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR2_APP_FullFIR0 (FIR2_APP_FullFIR0_t *Msg)
{

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_FULL_PROGRAM_CC);
	strcpy(FIR2_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir0.bin");
	FIR2_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
	FIR2_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
	FIR2_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
	FIR2_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), true);
	FIR2_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR2_APP_PartialFIR1 (FIR2_APP_PartialFIR1_t *Msg)
{

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_PARTIAL_PROGRAM_CC);
	strcpy(FIR2_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir1p.bin");
	FIR2_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
	FIR2_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
	FIR2_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
	FIR2_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), true);
	FIR2_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR2_APP_PartialFIR0 (FIR2_APP_PartialFIR0_t *Msg)
{

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_PARTIAL_PROGRAM_CC);
	strcpy(FIR2_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir0p.bin");
	FIR2_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
	FIR2_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
	FIR2_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
	FIR2_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.BinFile_Pkt.CmdHeader), true);
	FIR2_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR2_APP_Input (FIR2_APP_Input_t *Msg)
{

	FIR2_APP_Input_Payload_t *Payload = &(Msg->Payload);
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.Input_Pkt.CmdHeader), PL_CONTROL_APP_INPUT_CC);
	FIR2_APP_Data.Input_Pkt.Payload.number = Payload->number;
	FIR2_APP_Data.Input_Pkt.Payload.base_addr = 0x43C00000;
	FIR2_APP_Data.Input_Pkt.Payload.input_offset = 3;
	FIR2_APP_Data.Input_Pkt.Payload.start_offset = 1;
	FIR2_APP_Data.Input_Pkt.Payload.done_offset = 5;
	FIR2_APP_Data.Input_Pkt.Payload.output_offset = 4;
	FIR2_APP_Data.Input_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.Input_Pkt.Payload.reply_cmdid = FIR2_APP_OUTPUT_CC;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.Input_Pkt.CmdHeader), true);

	// Make space
	for (int i = FIR2_APP_Data.InOut_Count; i > 0; i--) {
		FIR2_APP_Data.Inputs[i] = FIR2_APP_Data.Inputs[i-1];
	}
	// Increase count
	if (FIR2_APP_Data.InOut_Count < FIR2_APP_INOUT_BUFFER_LEN-1) {
		FIR2_APP_Data.InOut_Count = FIR2_APP_Data.InOut_Count + 1;
	}
	FIR2_APP_Data.Inputs[0] = Payload->number;

	//CFE_EVS_SendEvent(FIR2_APP_INPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
	//	"FIR2: Input = %d", Payload->number);
	//CFE_ES_WriteToSysLog("FIR2 App WriteToSysLog: Input: %d", Payload->number);

    return CFE_SUCCESS;

}

int32 FIR2_APP_Output (FIR2_APP_Output_t *Msg)
{

	SAMPLE_APP_Output_Pkt_Payload_t *Payload = &(Msg->Payload);
	
	// Make space
	for (int i = FIR2_APP_Data.InOut_Count; i > 0; i--) {
		FIR2_APP_Data.Outputs[i] = FIR2_APP_Data.Outputs[i-1];
	}
	FIR2_APP_Data.Outputs[0] = Payload->Output;
	
	//CFE_EVS_SendEvent(FIR2_APP_INPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
	//	"FIR2: Output = %d, Done = %d", Payload->Output, Payload->Done);
	//CFE_ES_WriteToSysLog("FIR2 App WriteToSysLog: Done: %d, Output: %d", Payload->Done, Payload->Output);
    return CFE_SUCCESS;

} 

int32 FIR2_APP_Delay (FIR2_APP_NoopCmd_t *Msg)
{

	//CFE_ES_WriteToSysLog("FIR2 App: sizeof(cpuaddr) = %ld", sizeof(cpuaddr));
	OS_TaskDelay(5000);
	CFE_EVS_SendEvent(FIR2_APP_OUTPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
		"FIR2 App: Finish OS_TaskDelay for 5 seconds.");
	//CFE_ES_WriteToSysLog("FIR2 App: Finish OS_TaskDelay for 5 seconds.");
    return CFE_SUCCESS;

} 

int32 FIR2_APP_Release (FIR2_APP_NoopCmd_t *Msg)
{

	CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR2_APP_Data.Release_Pkt.CmdHeader), PL_CONTROL_APP_RELEASE_CC);
	FIR2_APP_Data.Release_Pkt.Payload.reply_msgid = FIR2_APP_CMD_MID;
	FIR2_APP_Data.Release_Pkt.Payload.reply_cmdid = FIR2_APP_PL_REPLY_CC;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR2_APP_Data.Release_Pkt.CmdHeader), true);
	FIR2_APP_Data.HasPL = 0;
	FIR2_APP_Data.InOut_Count = 0;

    return CFE_SUCCESS;

} 

int32 FIR2_APP_PL_Reply (FIR2_APP_Reply_t *Msg)
{

	SAMPLE_APP_Reply_Payload_t *Payload = &(Msg->Payload);

	FIR2_APP_Data.HasPL = Payload->Reply;

    return CFE_SUCCESS;

} 



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* FIR2_APP_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool FIR2_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
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

        CFE_EVS_SendEvent(FIR2_APP_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "FIR2 App: Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        FIR2_APP_Data.ErrCounter++;
    }

    return (result);

} /* End of FIR2_APP_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* FIR2_APP_TblValidationFunc -- Verify contents of First Table      */
/* buffer contents                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 FIR2_APP_TblValidationFunc(void *TblData)
{
    int32               ReturnCode = CFE_SUCCESS;
    FIR2_APP_Table_t *TblDataPtr = (FIR2_APP_Table_t *)TblData;

    /*
    ** FIR2 Table Validation
    */
    if (TblDataPtr->Int1 > FIR2_APP_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = FIR2_APP_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;

} /* End of FIR2_APP_TBLValidationFunc() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* FIR2_APP_GetCrc -- Output CRC                                     */
/*                                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FIR2_APP_GetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR2 App: Error Getting Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("FIR2 App: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }

    return;

} /* End of FIR2_APP_GetCrc */
