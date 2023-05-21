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
 *   This file contains the source code for the FIR App.
 */

/*
** Include Files:
*/
#include "fir_app_events.h"
#include "fir_app_version.h"
#include "fir_app.h"
#include "fir_app_table.h"

#include <string.h>

#include "fpgam_lib.h"
#include "mmio_lib.h"

/*
** global data
*/
FIR_APP_Data_t FIR_APP_Data;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* FIR_APP_Main() -- Application entry point and main process loop           */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FIR_APP_Main(void)
{
    int32            status;
    CFE_SB_Buffer_t *SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(FIR_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = FIR_APP_Init();
    if (status != CFE_SUCCESS)
    {
        FIR_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** FIR Runloop
    */
    while (CFE_ES_RunLoop(&FIR_APP_Data.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(FIR_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, FIR_APP_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(FIR_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            FIR_APP_ProcessCommandPacket(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(FIR_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR APP: SB Pipe Read Error, App Will Exit");

            FIR_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(FIR_APP_PERF_ID);

    CFE_ES_ExitApp(FIR_APP_Data.RunStatus);

} /* End of FIR_APP_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/* FIR_APP_Init() --  initialization                                         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 FIR_APP_Init(void)
{
    int32 status;

    FIR_APP_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    FIR_APP_Data.CmdCounter = 0;
    FIR_APP_Data.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    FIR_APP_Data.PipeDepth = FIR_APP_PIPE_DEPTH;

    strncpy(FIR_APP_Data.PipeName, "FIR_APP_CMD_PIPE", sizeof(FIR_APP_Data.PipeName));
    FIR_APP_Data.PipeName[sizeof(FIR_APP_Data.PipeName) - 1] = 0;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(CFE_MSG_PTR(FIR_APP_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(FIR_APP_HK_TLM_MID),
                 sizeof(FIR_APP_Data.HkTlm));

    // Init CMD BinFile packet
    CFE_MSG_Init(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR_APP_Data.BinFile_Pkt));
    
    // Init Reset packet
    CFE_MSG_Init(CFE_MSG_PTR(FIR_APP_Data.Reset_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR_APP_Data.Reset_Pkt));
    
    // Init Input packet
    CFE_MSG_Init(CFE_MSG_PTR(FIR_APP_Data.Input_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR_APP_Data.Input_Pkt));

    // Init Release packet
    CFE_MSG_Init(CFE_MSG_PTR(FIR_APP_Data.Release_Pkt.CmdHeader), CFE_SB_ValueToMsgId(SAMPLE_APP_CMD_MID),
                 sizeof(FIR_APP_Data.Release_Pkt));

    // Init input output telem counter
    FIR_APP_Data.InOut_Count = 0;

    // Init HasPL
    FIR_APP_Data.HasPL = 0;

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&FIR_APP_Data.CommandPipe, FIR_APP_Data.PipeDepth, FIR_APP_Data.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(FIR_APP_SEND_HK_MID), FIR_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(FIR_APP_CMD_MID), FIR_APP_Data.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    /*
    ** Register Table(s)
    */
    status = CFE_TBL_Register(&FIR_APP_Data.TblHandles[0], "FIRAppTable", sizeof(FIR_APP_Table_t),
                              CFE_TBL_OPT_DEFAULT, FIR_APP_TblValidationFunc);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error Registering Table, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }
    else
    {
        status = CFE_TBL_Load(FIR_APP_Data.TblHandles[0], CFE_TBL_SRC_FILE, FIR_APP_TABLE_FILE);
    }

    CFE_EVS_SendEvent(FIR_APP_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR App Initialized.%s",
                      FIR_APP_VERSION_STRING);

    return (CFE_SUCCESS);

} /* End of FIR_APP_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Name:  FIR_APP_ProcessCommandPacket                                      */
/*                                                                           */
/*  Purpose:                                                                 */
/*     This routine will process any packet that is received on the FIR      */
/*     command pipe.                                                         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FIR_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case FIR_APP_CMD_MID:
            FIR_APP_ProcessGroundCommand(SBBufPtr);
            break;

        case FIR_APP_SEND_HK_MID:
            FIR_APP_ReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(FIR_APP_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR App: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End FIR_APP_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/* FIR_APP_ProcessGroundCommand() -- FIR ground commands                     */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FIR_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    /*
    ** Process "known" FIR app ground commands
    */
    switch (CommandCode)
    {
        case FIR_APP_NOOP_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_NoopCmd_t)))
            {
                FIR_APP_Noop((FIR_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case FIR_APP_RESET_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_ResetCmd_t)))
            {
                FIR_APP_Reset((FIR_APP_ResetCmd_t *)SBBufPtr);
            }
            break;

        case FIR_APP_FULLFIR1_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_FullFIR1_t)))
            {
                FIR_APP_FullFIR1((FIR_APP_FullFIR1_t *)SBBufPtr);
            }
            break;

        case FIR_APP_FULLFIR0_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_FullFIR0_t)))
            {
                FIR_APP_FullFIR0((FIR_APP_FullFIR0_t *)SBBufPtr);
            }
            break;

        case FIR_APP_PARTIALFIR1_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_PartialFIR1_t)))
            {
                FIR_APP_PartialFIR1((FIR_APP_PartialFIR1_t *)SBBufPtr);
            }
            break;

        case FIR_APP_PARTIALFIR0_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_PartialFIR0_t)))
            {
                FIR_APP_PartialFIR0((FIR_APP_PartialFIR0_t *)SBBufPtr);
            }
            break;

        case FIR_APP_INPUT_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_Input_t)))
            {
                FIR_APP_Input((FIR_APP_Input_t *)SBBufPtr);
            }
            break;

        case FIR_APP_OUTPUT_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_Output_t)))
            {
                FIR_APP_Output((FIR_APP_Output_t *)SBBufPtr);
            }
            break;

        case FIR_APP_DELAY_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_NoopCmd_t)))
            {
                FIR_APP_Delay((FIR_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case FIR_APP_RELEASE_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_NoopCmd_t)))
            {
                FIR_APP_Release((FIR_APP_NoopCmd_t *)SBBufPtr);
            }
            break;

        case FIR_APP_PL_REPLY_CC:
            if (FIR_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(FIR_APP_Reply_t)))
            {
                FIR_APP_PL_Reply((FIR_APP_Reply_t *)SBBufPtr);
            }
            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(FIR_APP_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                              "FIR App: Invalid ground command code: CC = %d", CommandCode);
            break;
    }

    return;

} /* End of FIR_APP_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Name:  FIR_APP_ReportHousekeeping                                          */
/*                                                                             */
/*  Purpose:                                                                   */
/*         This function is triggered in response to a task telemetry request  */
/*         from the housekeeping task. This function will gather the Apps      */
/*         telemetry, packetize it and send it to the housekeeping task via    */
/*         the software bus                                                    */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 FIR_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg)
{

    /*
    ** Get command execution counters...
    */
    FIR_APP_Data.HkTlm.Payload.CommandErrorCounter = FIR_APP_Data.ErrCounter;
    FIR_APP_Data.HkTlm.Payload.CommandCounter      = FIR_APP_Data.CmdCounter;
    for (int i = 0; i < 200; i++) {
        FIR_APP_Data.HkTlm.Payload.Inputs[i] = '\0';
        FIR_APP_Data.HkTlm.Payload.Outputs[i] = '\0';
    }
    char *inputs = FIR_APP_Data.HkTlm.Payload.Inputs;
    char *outputs = FIR_APP_Data.HkTlm.Payload.Outputs;
    *inputs++ = '[';
    *outputs++ = '[';
    if (FIR_APP_Data.InOut_Count > 0) {
        for (int i = 0; i < FIR_APP_Data.InOut_Count; i++) {
            inputs = inputs + snprintf(inputs, 12, "%d, ", FIR_APP_Data.Inputs[i]);
            outputs = outputs + snprintf(outputs, 12, "%d, ", FIR_APP_Data.Outputs[i]);
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
    FIR_APP_Data.HkTlm.Payload.HasPL = FIR_APP_Data.HasPL;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(FIR_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (int i = 0; i < FIR_APP_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(FIR_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;

} /* End of FIR_APP_ReportHousekeeping() */





int32 FIR_APP_Noop(const FIR_APP_NoopCmd_t *Msg)
{

    FIR_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(FIR_APP_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR: NOOP command %s, %d",
                      FIR_APP_VERSION, FIR_APP_Data.CmdCounter);

    return CFE_SUCCESS;

}

int32 FIR_APP_Reset(const FIR_APP_ResetCmd_t *Msg)
{

    FIR_APP_Data.CmdCounter = 0;
    FIR_APP_Data.ErrCounter = 0;
    FIR_APP_Data.InOut_Count = 0;

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.Reset_Pkt.CmdHeader), PL_CONTROL_APP_RESET_CC);
    FIR_APP_Data.Reset_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.Reset_Pkt.Payload.reset_offset = 2;
    FIR_APP_Data.Reset_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.Reset_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.Reset_Pkt.CmdHeader), true);

    CFE_EVS_SendEvent(FIR_APP_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "FIR: RESET command");

    return CFE_SUCCESS;

}

int32 FIR_APP_FullFIR1 (FIR_APP_FullFIR1_t *Msg)
{

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_FULL_PROGRAM_CC);
    strcpy(FIR_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir1.bin");
    FIR_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
    FIR_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
    FIR_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
    FIR_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), true);
    FIR_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR_APP_FullFIR0 (FIR_APP_FullFIR0_t *Msg)
{

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_FULL_PROGRAM_CC);
    strcpy(FIR_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir0.bin");
    FIR_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
    FIR_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
    FIR_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
    FIR_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), true);
    FIR_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR_APP_PartialFIR1 (FIR_APP_PartialFIR1_t *Msg)
{

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_PARTIAL_PROGRAM_CC);
    strcpy(FIR_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir1p.bin");
    FIR_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
    FIR_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
    FIR_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
    FIR_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), true);
    FIR_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR_APP_PartialFIR0 (FIR_APP_PartialFIR0_t *Msg)
{

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), PL_CONTROL_APP_PARTIAL_PROGRAM_CC);
    strcpy(FIR_APP_Data.BinFile_Pkt.Payload.binfile, "/home/ubuntu/bitstreams/fir0p.bin");
    FIR_APP_Data.BinFile_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.BinFile_Pkt.Payload.input_offset = 3;
    FIR_APP_Data.BinFile_Pkt.Payload.start_offset = 1;
    FIR_APP_Data.BinFile_Pkt.Payload.done_offset = 5;
    FIR_APP_Data.BinFile_Pkt.Payload.output_offset = 4;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.BinFile_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.BinFile_Pkt.CmdHeader), true);
    FIR_APP_Data.HasPL = 1;

    return CFE_SUCCESS;

}

int32 FIR_APP_Input (FIR_APP_Input_t *Msg)
{

    FIR_APP_Input_Payload_t *Payload = &(Msg->Payload);
    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.Input_Pkt.CmdHeader), PL_CONTROL_APP_INPUT_CC);
    FIR_APP_Data.Input_Pkt.Payload.number = Payload->number;
    FIR_APP_Data.Input_Pkt.Payload.base_addr = 0x43C00000;
    FIR_APP_Data.Input_Pkt.Payload.input_offset = 3;
    FIR_APP_Data.Input_Pkt.Payload.start_offset = 1;
    FIR_APP_Data.Input_Pkt.Payload.done_offset = 5;
    FIR_APP_Data.Input_Pkt.Payload.output_offset = 4;
    FIR_APP_Data.Input_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.Input_Pkt.Payload.reply_cmdid = FIR_APP_OUTPUT_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.Input_Pkt.CmdHeader), true);

    // Make space
    for (int i = FIR_APP_Data.InOut_Count; i > 0; i--) {
        FIR_APP_Data.Inputs[i] = FIR_APP_Data.Inputs[i-1];
    }
    // Increase count
    if (FIR_APP_Data.InOut_Count < FIR_APP_INOUT_BUFFER_LEN-1) {
        FIR_APP_Data.InOut_Count = FIR_APP_Data.InOut_Count + 1;
    }
    FIR_APP_Data.Inputs[0] = Payload->number;

    return CFE_SUCCESS;

}

int32 FIR_APP_Output (FIR_APP_Output_t *Msg)
{

    SAMPLE_APP_Output_Pkt_Payload_t *Payload = &(Msg->Payload);
    
    // Make space
    for (int i = FIR_APP_Data.InOut_Count; i > 0; i--) {
        FIR_APP_Data.Outputs[i] = FIR_APP_Data.Outputs[i-1];
    }
    FIR_APP_Data.Outputs[0] = Payload->Output;

    return CFE_SUCCESS;

} 

int32 FIR_APP_Delay (FIR_APP_NoopCmd_t *Msg)
{

    OS_TaskDelay(5000);
    CFE_EVS_SendEvent(FIR_APP_OUTPUT_INF_EID, CFE_EVS_EventType_INFORMATION,
        "FIR App: Finish OS_TaskDelay for 5 seconds.");
    return CFE_SUCCESS;

} 

int32 FIR_APP_Release (FIR_APP_NoopCmd_t *Msg)
{

    CFE_MSG_SetFcnCode(CFE_MSG_PTR(FIR_APP_Data.Release_Pkt.CmdHeader), PL_CONTROL_APP_RELEASE_CC);
    FIR_APP_Data.Release_Pkt.Payload.reply_msgid = FIR_APP_CMD_MID;
    FIR_APP_Data.Release_Pkt.Payload.reply_cmdid = FIR_APP_PL_REPLY_CC;
    CFE_SB_TransmitMsg(CFE_MSG_PTR(FIR_APP_Data.Release_Pkt.CmdHeader), true);
    FIR_APP_Data.HasPL = 0;
    FIR_APP_Data.InOut_Count = 0;

    return CFE_SUCCESS;

} 

int32 FIR_APP_PL_Reply (FIR_APP_Reply_t *Msg)
{

    SAMPLE_APP_Reply_Payload_t *Payload = &(Msg->Payload);

    FIR_APP_Data.HasPL = Payload->Reply;

    return CFE_SUCCESS;

} 



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/* FIR_APP_VerifyCmdLength() -- Verify command packet length                 */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool FIR_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
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

        CFE_EVS_SendEvent(FIR_APP_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "FIR App: Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        FIR_APP_Data.ErrCounter++;
    }

    return (result);

} /* End of FIR_APP_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* FIR_APP_TblValidationFunc -- Verify contents of First Table     */
/* buffer contents                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 FIR_APP_TblValidationFunc(void *TblData)
{
    int32               ReturnCode = CFE_SUCCESS;
    FIR_APP_Table_t *TblDataPtr = (FIR_APP_Table_t *)TblData;

    /*
    ** FIR Table Validation
    */
    if (TblDataPtr->Int1 > FIR_APP_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = FIR_APP_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;

} /* End of FIR_APP_TBLValidationFunc() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* FIR_APP_GetCrc -- Output CRC                                    */
/*                                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void FIR_APP_GetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("FIR App: Error Getting Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("FIR App: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }

    return;

} /* End of FIR_APP_GetCrc */
