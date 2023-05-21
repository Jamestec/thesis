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
 * @file
 *
 * Main header file for the SAMPLE application
 */

#ifndef SAMPLE_APP_H
#define SAMPLE_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "sample_app_perfids.h"
#include "sample_app_msgids.h"
#include "sample_app_msg.h"

/***********************************************************************/
#define SAMPLE_APP_PIPE_DEPTH 32 /* Depth of the Command Pipe for Application */

#define SAMPLE_APP_PL_QUEUE_LEN 4

#define SAMPLE_APP_INPUT_BUFFER 16

#define SAMPLE_APP_NUMBER_OF_TABLES 1 /* Number of Table(s) */

/* Define filenames of default data images for tables */
#define SAMPLE_APP_TABLE_FILE "/cf/sample_app_tbl.tbl"

#define SAMPLE_APP_TABLE_OUT_OF_RANGE_ERR_CODE -1

#define SAMPLE_APP_TBL_ELEMENT_1_MAX 10
/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/
typedef struct
{
    char binfile[128];
    cpuaddr base_addr;
    int32 input_offset;
    int32 start_offset;
    int32 done_offset;
    int32 output_offset;
    int32 reply_msgid;
    int32 reply_cmdid;
    int32 input_queued;
    int32 inputs[SAMPLE_APP_INPUT_BUFFER];
} SAMPLE_APP_PL_DETAILS_t;

typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CmdCounter;
    uint8 ErrCounter;
    
    // PL information
    char binfile[128];
    cpuaddr base_addr;
    int32 input_offset;
    int32 start_offset;
    int32 done_offset;
    int32 output_offset;
    int32 reply_msgid;
    int32 reply_cmdid;

    // PL Output packet
    SAMPLE_APP_Output_Pkt_t Output_Pkt;
    
    // Reply packet
    SAMPLE_APP_Reply_t Reply_Pkt;
    
    // Counter test *start
    int *g_start;
    cpusize newSize;
    
    // Make Busy paket
    SAMPLE_APP_Output_Pkt_t Busy_Pkt;

    /*
    ** Housekeeping telemetry packet...
    */
    SAMPLE_APP_HkTlm_t HkTlm;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;

    /*
    ** Initialization data (not reported in housekeeping)...
    */
    char   PipeName[CFE_MISSION_MAX_API_LEN];
    uint16 PipeDepth;

    CFE_TBL_Handle_t TblHandles[SAMPLE_APP_NUMBER_OF_TABLES];

} SAMPLE_APP_Data_t;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (SAMPLE_APP_Main), these
**       functions are not called from any other source module.
*/
void  SAMPLE_APP_Main(void);
int32 SAMPLE_APP_Init(void);
void  SAMPLE_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr);
void  SAMPLE_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr);
int32 SAMPLE_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg);
int32 SAMPLE_APP_ResetCounters(const SAMPLE_APP_ResetCountersCmd_t *Msg);
int32 SAMPLE_APP_Process(const SAMPLE_APP_ProcessCmd_t *Msg);
int32 SAMPLE_APP_Noop(const SAMPLE_APP_NoopCmd_t *Msg);
int32 SAMPLE_APP_Full_Program (SAMPLE_APP_BinFile_t *Msg);
int32 SAMPLE_APP_Partial_Program (SAMPLE_APP_BinFile_t *Msg);
int32 SAMPLE_APP_Reset (SAMPLE_APP_Reset_t *Msg);
int32 SAMPLE_APP_Input (SAMPLE_APP_Input_t *Msg);
int32 SAMPLE_APP_Output (SAMPLE_APP_Output_t *Msg);
int32 SAMPLE_APP_Release (SAMPLE_APP_Release_t *Msg);
int32 SAMPLE_APP_Query (SAMPLE_APP_Query_t *Msg);
int32 SAMPLE_APP_Counter_Test (SAMPLE_APP_Output_Pkt_t *Msg);
int32 Counter_Test_Output (void);
int32 SAMPLE_APP_Make_Busy (SAMPLE_APP_Output_Pkt_t *Msg);
void  SAMPLE_APP_GetCrc(const char *TableName);

int32 SAMPLE_APP_TblValidationFunc(void *TblData);

bool SAMPLE_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);

#endif /* SAMPLE_APP_H */
