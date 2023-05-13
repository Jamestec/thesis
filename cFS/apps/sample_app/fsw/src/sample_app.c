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
 *   This file contains the source code for the Sample App.
 */

/*
** Include Files:
*/
#include "sample_app_events.h"
#include "sample_app_version.h"
#include "sample_app.h"
#include "sample_app_table.h"

/* The sample_lib module provides the SAMPLE_LIB_Function() prototype */
#include <string.h>
#include "sample_lib.h"

#include "fpgam_lib.h"
#include "mmio_lib.h"

/*
** global data
*/
SAMPLE_APP_Data_t SAMPLE_APP_Data;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/* SAMPLE_APP_Main() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SAMPLE_APP_Main(void)
{
    int32            status;
    CFE_SB_Buffer_t *SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = SAMPLE_APP_Init();
    if (status != CFE_SUCCESS)
    {
        SAMPLE_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** SAMPLE Runloop
    */
    while (CFE_ES_RunLoop(&SAMPLE_APP_Data.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, SAMPLE_APP_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            SAMPLE_APP_ProcessCommandPacket(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(SAMPLE_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "PL_CONTROL APP: SB Pipe Read Error, App Will Exit");

            SAMPLE_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

    CFE_ES_ExitApp(SAMPLE_APP_Data.RunStatus);

} /* End of SAMPLE_APP_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SAMPLE_APP_Init() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 SAMPLE_APP_Init(void)
{
    int32 status;

    SAMPLE_APP_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    SAMPLE_APP_Data.CmdCounter = 0;
    SAMPLE_APP_Data.ErrCounter = 0;
	
	// Init PL Info
	SAMPLE_APP_Data.binfile[0] = '\0';
	SAMPLE_APP_Data.base_addr = 0;
	SAMPLE_APP_Data.input_offset = -1;
	SAMPLE_APP_Data.start_offset = -1;
	SAMPLE_APP_Data.done_offset = -1;
	SAMPLE_APP_Data.output_offset = -1;
	SAMPLE_APP_Data.reply_msgid = -1;
	SAMPLE_APP_Data.reply_cmdid = -1;

    /*
    ** Initialize app configuration data
    */
    SAMPLE_APP_Data.PipeDepth = SAMPLE_APP_PIPE_DEPTH;

    strncpy(SAMPLE_APP_Data.PipeName, "SAMPLE_APP_CMD_PIPE", sizeof(SAMPLE_APP_Data.PipeName));
    SAMPLE_APP_Data.PipeName[sizeof(SAMPLE_APP_Data.PipeName) - 1] = 0;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_HK_TLM_MID),
                 sizeof(SAMPLE_APP_Data.HkTlm));

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&SAMPLE_APP_Data.CommandPipe, SAMPLE_APP_Data.PipeDepth, SAMPLE_APP_Data.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_SEND_HK_MID), SAMPLE_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID), SAMPLE_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    /*
    ** Register Table(s)
    */
    status = CFE_TBL_Register(&SAMPLE_APP_Data.TblHandles[0], "SampleAppTable", sizeof(SAMPLE_APP_Table_t),
                              CFE_TBL_OPT_DEFAULT, SAMPLE_APP_TblValidationFunc);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error Registering Table, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }
    else
    {
        status = CFE_TBL_Load(SAMPLE_APP_Data.TblHandles[0], CFE_TBL_SRC_FILE, SAMPLE_APP_TABLE_FILE);
    }

    CFE_EVS_SendEvent(SAMPLE_APP_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "PL_CONTROL App Initialized.%s",
                      SAMPLE_APP_VERSION_STRING);

    return (CFE_SUCCESS);

} /* End of SAMPLE_APP_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_ProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the SAMPLE    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case SAMPLE_APP_CMD_MID:
            SAMPLE_APP_ProcessGroundCommand(SBBufPtr);
            break;

        case SAMPLE_APP_SEND_HK_MID:
            SAMPLE_APP_ReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(SAMPLE_APP_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "PL_CONTROL: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End SAMPLE_APP_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_APP_ProcessGroundCommand() -- SAMPLE ground commands                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SAMPLE_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    /*
    ** Process "known" SAMPLE app ground commands
    */
    switch (CommandCode)
    {
        case PL_CONTROL_APP_NOOP_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_NoopCmd_t)))
            {
                SAMPLE_APP_Noop((SAMPLE_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case PL_CONTROL_APP_RESET_COUNTERS_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_ResetCountersCmd_t)))
            {
                SAMPLE_APP_ResetCounters((SAMPLE_APP_ResetCountersCmd_t *)SBBufPtr);
            }
            break;

        case PL_CONTROL_APP_PROCESS_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_ProcessCmd_t)))
            {
                SAMPLE_APP_Process((SAMPLE_APP_ProcessCmd_t *)SBBufPtr);
            }
            break;

		case PL_CONTROL_APP_FULL_PROGRAM_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_BinFile_t)))
            {
                SAMPLE_APP_Full_Program((SAMPLE_APP_BinFile_t *)SBBufPtr);
            }

            break;

		case PL_CONTROL_APP_PARTIAL_PROGRAM_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_BinFile_t)))
            {
                SAMPLE_APP_Partial_Program((SAMPLE_APP_BinFile_t *)SBBufPtr);
            }
			break;
		
		case PL_CONTROL_APP_RESET_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Reset_t)))
            {
                SAMPLE_APP_Reset((SAMPLE_APP_Reset_t *)SBBufPtr);
            }
			break;

		case PL_CONTROL_APP_INPUT_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Input_t)))
            {
                SAMPLE_APP_Input((SAMPLE_APP_Input_t *)SBBufPtr);
            }
			break;

		case PL_CONTROL_APP_OUTPUT_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Output_t)))
            {
                SAMPLE_APP_Output((SAMPLE_APP_Output_t *)SBBufPtr);
            }
            break;

		case PL_CONTROL_APP_RELEASE_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Release_t)))
            {
                SAMPLE_APP_Release((SAMPLE_APP_Release_t *)SBBufPtr);
            }
            break;

		case PL_CONTROL_APP_QUERY_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Query_t)))
            {
                SAMPLE_APP_Query((SAMPLE_APP_Query_t *)SBBufPtr);
            }
            break;

		case PL_CONTROL_APP_COUNTER_TEST_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Output_Pkt_t)))
            {
                SAMPLE_APP_Counter_Test((SAMPLE_APP_Output_Pkt_t *)SBBufPtr);
            }
            break;

		case PL_CONTROL_APP_MAKE_BUSY_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_Output_Pkt_t)))
            {
                SAMPLE_APP_Make_Busy((SAMPLE_APP_Output_Pkt_t *)SBBufPtr);
            }
            break;


        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(SAMPLE_APP_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                              "PL_CONTROL: Invalid ground command code: CC = %d", CommandCode);
            break;
    }

    return;

} /* End of SAMPLE_APP_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_ReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg)
{
    int i;

    /*
    ** Get command execution counters...
    */
    SAMPLE_APP_Data.HkTlm.Payload.CommandErrorCounter = SAMPLE_APP_Data.ErrCounter;
    SAMPLE_APP_Data.HkTlm.Payload.CommandCounter      = SAMPLE_APP_Data.CmdCounter;
	
	// Add PL info
	for (int i = 0; i < 128; i++) {
		SAMPLE_APP_Data.HkTlm.Payload.binfile[i] = '\0';
	}
	strcpy(SAMPLE_APP_Data.HkTlm.Payload.binfile, SAMPLE_APP_Data.binfile);
	SAMPLE_APP_Data.HkTlm.Payload.base_addr = SAMPLE_APP_Data.base_addr;
	SAMPLE_APP_Data.HkTlm.Payload.input_offset = SAMPLE_APP_Data.input_offset;
	SAMPLE_APP_Data.HkTlm.Payload.start_offset = SAMPLE_APP_Data.start_offset;
	SAMPLE_APP_Data.HkTlm.Payload.done_offset = SAMPLE_APP_Data.done_offset;
	SAMPLE_APP_Data.HkTlm.Payload.output_offset = SAMPLE_APP_Data.output_offset;
	SAMPLE_APP_Data.HkTlm.Payload.reply_msgid = SAMPLE_APP_Data.reply_msgid;
	SAMPLE_APP_Data.HkTlm.Payload.reply_cmdid = SAMPLE_APP_Data.reply_cmdid;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(SAMPLE_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (i = 0; i < SAMPLE_APP_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(SAMPLE_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_APP_Noop -- SAMPLE NOOP commands                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 SAMPLE_APP_Noop(const SAMPLE_APP_NoopCmd_t *Msg)
{

    SAMPLE_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(SAMPLE_APP_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "SAMPLE: NOOP command %s, %d",
                      SAMPLE_APP_VERSION, SAMPLE_APP_Data.CmdCounter);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_Noop */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_ResetCounters(const SAMPLE_APP_ResetCountersCmd_t *Msg)
{

    SAMPLE_APP_Data.CmdCounter = 0;
    SAMPLE_APP_Data.ErrCounter = 0;

    CFE_EVS_SendEvent(SAMPLE_APP_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "SAMPLE: RESET command");

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_Process                                                     */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Process(const SAMPLE_APP_ProcessCmd_t *Msg)
{
    int32               status;
    SAMPLE_APP_Table_t *TblPtr;
    const char *        TableName = "SAMPLE_APP.SampleAppTable";

    /* Sample Use of Table */

    status = CFE_TBL_GetAddress((void *)&TblPtr, SAMPLE_APP_Data.TblHandles[0]);

    if (status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Fail to get table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    CFE_ES_WriteToSysLog("PL_Control App: Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

    SAMPLE_APP_GetCrc(TableName);

    status = CFE_TBL_ReleaseAddress(SAMPLE_APP_Data.TblHandles[0]);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Fail to release table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    /* Invoke a function provided by SAMPLE_APP_LIB */
    SAMPLE_LIB_Function();

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_ProcessCC */



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_FULL_PROGRAM                    */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Full program the PL                                                */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Full_Program (SAMPLE_APP_BinFile_t *Msg)
{

	SAMPLE_APP_BinFile_Payload_t *Payload = &(Msg->Payload);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: PL is in use by %d", SAMPLE_APP_Data.reply_msgid);
		// Init reply packet
		CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), CFE_SB_ValueToMsgId(Payload->reply_msgid),
					 sizeof(SAMPLE_APP_Data.Reply_Pkt));
		CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), Payload->reply_cmdid);
		SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 0;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), true);
		return CFE_SUCCESS;
	}
	
	strcpy(SAMPLE_APP_Data.binfile, Payload->binfile);
	SAMPLE_APP_Data.base_addr = Payload->base_addr;
	SAMPLE_APP_Data.input_offset = Payload->input_offset;
	SAMPLE_APP_Data.start_offset = Payload->start_offset;
	SAMPLE_APP_Data.done_offset = Payload->done_offset;
	SAMPLE_APP_Data.output_offset = Payload->output_offset;
	SAMPLE_APP_Data.output_offset = Payload->output_offset;
	SAMPLE_APP_Data.reply_msgid = Payload->reply_msgid;
	SAMPLE_APP_Data.reply_cmdid = Payload->reply_cmdid;
	CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: Programming full bitstream %s", SAMPLE_APP_Data.binfile);
	/*
	CFE_ES_WriteToSysLog("base_addr=%X, input=%d, start=%d, done=%d, output=%d",
		SAMPLE_APP_Data.base_addr, SAMPLE_APP_Data.input_offset , SAMPLE_APP_Data.start_offset, SAMPLE_APP_Data.done_offset, SAMPLE_APP_Data.output_offset);
	*/
	program_pl(Payload->binfile, 0);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_FULL_PROGRAM_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_PARTIAL_PROGRAM              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Partially program the PL                                                */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Partial_Program (SAMPLE_APP_BinFile_t *Msg)
{

	SAMPLE_APP_BinFile_Payload_t *Payload = &(Msg->Payload);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: PL is in use by %d", SAMPLE_APP_Data.reply_msgid);
		// Init reply packet
		CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), CFE_SB_ValueToMsgId(Payload->reply_msgid),
					 sizeof(SAMPLE_APP_Data.Reply_Pkt));
		CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), Payload->reply_cmdid);
		SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 0;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), true);
		return CFE_SUCCESS;
	}

	CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: Programming partial bitstream %s", Payload->binfile);
	program_pl(Payload->binfile, 1);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_PARTIAL_PROGRAM_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_RESET              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Assert reset signal and deassert                                                */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Reset (SAMPLE_APP_Reset_t *Msg)
{

	SAMPLE_APP_Reset_Payload_t *Payload = &(Msg->Payload);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: PL is in use by %d", SAMPLE_APP_Data.reply_msgid);
		// Init reply packet
		CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), CFE_SB_ValueToMsgId(Payload->reply_msgid),
					 sizeof(SAMPLE_APP_Data.Reply_Pkt));
		CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), Payload->reply_cmdid);
		SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 0;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), true);
		return CFE_SUCCESS;
	}

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, Payload->base_addr, (cpusize)32);
	int *reset = mapping;
	reset = reset + Payload->reset_offset;
	*reset = 0;
	*reset = 1;
	OS_TaskDelay(1);
	*reset = 0;
	CFE_EVS_SendEvent(SAMPLE_APP_RESET_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: Reset");
	//CFE_ES_WriteToSysLog("Sample App WriteToSysLog: Reset: %d", Payload->reset_offset);
	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_RESET_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_INPUT_CC              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Set a value in memory                                               */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Input (SAMPLE_APP_Input_t *Msg)
{

	SAMPLE_APP_Input_Payload_t *Payload = &(Msg->Payload);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: PL is in use by %d", SAMPLE_APP_Data.reply_msgid);
		return CFE_SUCCESS;
	}

	SAMPLE_APP_Data.reply_msgid = Payload->reply_msgid;
	SAMPLE_APP_Data.reply_cmdid = Payload->reply_cmdid;
	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, Payload->base_addr, (cpusize)32);
	int *start = mapping;
	int *input = mapping;
	start = start + Payload->start_offset;
	input = input + Payload->input_offset;
	*start = 0;
	*input = Payload->number;
	//OS_TaskDelay(1);
	*start = 1;
	CFE_EVS_SendEvent(SAMPLE_APP_INPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: Input %d", Payload->number);
	//CFE_ES_WriteToSysLog("Sample App WriteToSysLog: Input: %d", Payload->number);
	mmio_lib_DeleteMapping(mapping, newSize);
	
	SAMPLE_APP_Output(NULL);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_INPUT_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_OUTPUT              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Read a value in memory                                               */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Output (SAMPLE_APP_Output_t *Msg)
{

	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, SAMPLE_APP_Data.base_addr, (cpusize)32);
	int *done = mapping;
	int *output = mapping;
	done = done + SAMPLE_APP_Data.done_offset;
	output = output + SAMPLE_APP_Data.output_offset;
	int count = 0;
	while (*done == 0) {
		//OS_TaskDelay(10);
		count = count + 1;
		if (count > 100) {
			break;
		}
	}
	
	CFE_EVS_SendEvent(SAMPLE_APP_OUTPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: output = %d, done = %d", *output, *done);
	//CFE_ES_WriteToSysLog("Sample App WriteToSysLog: Done: %d, Output: %d, count=%d", *done, *output, count);
	
	// Init Output packet
	CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Output_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_Data.reply_msgid),
                 sizeof(SAMPLE_APP_Data.Output_Pkt));
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Output_Pkt.CmdHeader), SAMPLE_APP_Data.reply_cmdid);
	SAMPLE_APP_Data.Output_Pkt.Payload.Done = *done;
	SAMPLE_APP_Data.Output_Pkt.Payload.Output = *output;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Output_Pkt.CmdHeader), true);

	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_OUTPUT_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_Release              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Release PL control                                               */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Release (SAMPLE_APP_Release_t *Msg)
{

	SAMPLE_APP_Release_Payload_t *Payload = &(Msg->Payload);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		CFE_EVS_SendEvent(SAMPLE_APP_FULL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: PL is in use by %d", SAMPLE_APP_Data.reply_msgid);
		// Init reply packet
		CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), CFE_SB_ValueToMsgId(Payload->reply_msgid),
					 sizeof(SAMPLE_APP_Data.Reply_Pkt));
		CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), Payload->reply_cmdid);
		SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 0;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), true);
		return CFE_SUCCESS;
	}

	SAMPLE_APP_Data.reply_msgid = -1;

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_RELEASE_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_Query              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Reply whether you have PL control                                               */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Query (SAMPLE_APP_Query_t *Msg)
{

	SAMPLE_APP_Query_Payload_t *Payload = &(Msg->Payload);

	// Init reply packet
	CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), CFE_SB_ValueToMsgId(Payload->reply_msgid),
				 sizeof(SAMPLE_APP_Data.Reply_Pkt));
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), Payload->reply_cmdid);

	// Check if PL is in use/correct app
	if (SAMPLE_APP_Data.reply_msgid != -1
		&& SAMPLE_APP_Data.reply_msgid != Payload->reply_msgid)
	{
		SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 0;
	}

	SAMPLE_APP_Data.Reply_Pkt.Payload.Reply = 1;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Reply_Pkt.CmdHeader), true);

	/*
	// Test software bus pt.2
	*SAMPLE_APP_Data.g_start = 0;
	int *mapped = SAMPLE_APP_Data.g_start  - 1;
	int *count_out = mapped + 3;
	int *done = mapped + 4;
	CFE_ES_WriteToSysLog("Message Bus Counter 1: count=%d", *count_out);
	CFE_ES_WriteToSysLog("Message Bus Counter 2: count=%d, done=%d", *count_out, *done);
	*mapped = 1;
	*mapped = 0;
	void *mapping = mapped;
	mmio_lib_DeleteMapping(mapping, SAMPLE_APP_Data.newSize);
	*/

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_QUERY_CC */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_Counter_Test              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Test C instruction to PL clock cycles                          */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Counter_Test (SAMPLE_APP_Output_Pkt_t *Msg)
{

	SAMPLE_APP_Output_Pkt_Payload_t *Payload = &(Msg->Payload);

	CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: Programming bitstream count1.bin");
	char bin[] = "/home/ubuntu/bitstreams/count1.bin";
	program_pl(bin, 0);
	
	/*
	// Test between instructions
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
	for (int i = 10; i < 30; i++) {
		*mapped = 1;
		*mapped = 0;
		*input = i;
		*start = 1;
		c_o = *count_out;
		nums[i-10] = c_o;
		*start = 0;
	}
	for (int i = 0; i < 25; i++) {
		CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
			"Count_Test: i = %d, counter = %d\n", i+10, nums[i]);
	}
	mmio_lib_DeleteMapping(mapping, newSize);*/
	
	/*
	// Test between function calls (input and output calls).
	for (int i = Payload->Done; i < Payload->Output; i++) {
		void *mapping;
		cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
		int *mapped = mapping;
		int *start = mapping;
		int *input = mapping;
		*mapped = 1;
		*mapped = 0;
		start = start + 1;
		input = input + 2;
		*start = 0;
		*input = i;
		//OS_TaskDelay(1);
		*start = 1;
		CFE_EVS_SendEvent(SAMPLE_APP_INPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
			"PL_CONTROL: Input %d", i);
		//CFE_ES_WriteToSysLog("Sample App WriteToSysLog: Input: %d", i);
		mmio_lib_DeleteMapping(mapping, newSize);
		Counter_Test_Output();
	}*/

	// Test software bus pt.1
	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int *mapped = mapping;
	int *start = mapped + 1;
	SAMPLE_APP_Data.g_start = start;
	SAMPLE_APP_Data.newSize = newSize;
	int *input = mapped + 2;
	//int *count_out = mapped + 3;
	//int *done = mapped + 4;
	*mapped = 1;
	*mapped = 0;
	*input = Payload->Output;
	CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
					 sizeof(SAMPLE_APP_Data.Busy_Pkt));
	CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), PL_CONTROL_APP_QUERY_CC);
	*SAMPLE_APP_Data.g_start = 1;
	CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), true);

    return CFE_SUCCESS;

}

int32 Counter_Test_Output ()
{
	void *mapping;
	cpusize newSize = mmio_lib_NewMapping(&mapping, 0x43C00000, (cpusize)32);
	int *done = mapping;
	int *output = mapping;
	done = done + 4;
	output = output + 3;
	int count = 0;
	while (*done == 0) {
		//OS_TaskDelay(10);
		count = count + 1;
		if (count > 100) {
			break;
		}
	}
	
	CFE_EVS_SendEvent(SAMPLE_APP_OUTPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
		"PL_CONTROL: output = %d, done = %d", *output, *done);
	CFE_ES_WriteToSysLog("Sample App WriteToSysLog: Done: %d, Output: %d, count=%d", *done, *output, count);

	mmio_lib_DeleteMapping(mapping, newSize);

    return CFE_SUCCESS;

} 
/* End of SAMPLE_APP_COUNTER_TEST_CC*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_APP_Make_Busy              */
/*                                                                                        */
/*  Purpose:                                                                        */
/*         Send messages to itself to make CPU busy                         */
/*                                                                                        */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 SAMPLE_APP_Make_Busy (SAMPLE_APP_Output_Pkt_t *Msg)
{

	SAMPLE_APP_Output_Pkt_Payload_t *Payload = &(Msg->Payload);

	CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Busy count: %d\n", Payload->Output);

	for (int i = 0; i < Payload->Output; i++) {
		int x = 0;
		while (x < 1000) {
			x++;
		}
	}
	
	CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Busy Done\n");

	// Init busy packet
	/*
	if (Payload->Output > 0) {
		CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
					 sizeof(SAMPLE_APP_Data.Busy_Pkt));
		CFE_MSG_SetFcnCode(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), PL_CONTROL_APP_MAKE_BUSY_CC);
		SAMPLE_APP_Data.Busy_Pkt.Payload.Done = Payload->Done;
		SAMPLE_APP_Data.Busy_Pkt.Payload.Output = Payload->Output - 1;
		CFE_SB_TransmitMsg(CFE_MSG_PTR(SAMPLE_APP_Data.Busy_Pkt.CmdHeader), true);
	} else {
		CFE_EVS_SendEvent(SAMPLE_APP_PARTIAL_PROGRAM_INF_EID, CFE_EVS_EventType_INFORMATION,
		"Busy Done: %d\n", Payload->Output);
	}
	*/

    return CFE_SUCCESS;

} /* End of SAMPLE_APP_MAKE_BUSY_CC*/



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_APP_VerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool SAMPLE_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
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

        CFE_EVS_SendEvent(SAMPLE_APP_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "PL_CONTROL: Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        SAMPLE_APP_Data.ErrCounter++;
    }

	if (ActualLength > ExpectedLength) {
		result = true;
	}

    return (result);

} /* End of SAMPLE_APP_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SAMPLE_APP_TblValidationFunc -- Verify contents of First Table      */
/* buffer contents                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SAMPLE_APP_TblValidationFunc(void *TblData)
{
    int32               ReturnCode = CFE_SUCCESS;
    SAMPLE_APP_Table_t *TblDataPtr = (SAMPLE_APP_Table_t *)TblData;

    /*
    ** Sample Table Validation
    */
    if (TblDataPtr->Int1 > SAMPLE_APP_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = SAMPLE_APP_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;

} /* End of SAMPLE_APP_TBLValidationFunc() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SAMPLE_APP_GetCrc -- Output CRC                                     */
/*                                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SAMPLE_APP_GetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("PL_Control App: Error Getting Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("PL_Control App: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }

    return;

} /* End of SAMPLE_APP_GetCrc */
