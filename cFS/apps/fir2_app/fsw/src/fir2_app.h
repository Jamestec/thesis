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
 * Main header file for the FIR2 application
 */

#ifndef FIR2_APP_Hs
#define FIR2_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "fir2_app_perfids.h"
#include "fir2_app_msgids.h"
#include "fir2_app_msg.h"
#include "sample_app_msgids.h"
#include "sample_app_msg.h"

/***********************************************************************/
#define FIR2_APP_PIPE_DEPTH 32 /* Depth of the Command Pipe for Application */

#define FIR2_APP_INOUT_BUFFER_LEN 16

#define FIR2_APP_NUMBER_OF_TABLES 1 /* Number of Table(s) */

/* Define filenames of default data images for tables */
#define FIR2_APP_TABLE_FILE "/cf/FIR_app_tbl.tbl"

#define FIR2_APP_TABLE_OUT_OF_RANGE_ERR_CODE -1

#define FIR2_APP_TBL_ELEMENT_1_MAX 10
/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/
typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CmdCounter;
    uint8 ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    FIR2_APP_HkTlm_t HkTlm;

    // CMD Binfile Packet
    SAMPLE_APP_BinFile_t BinFile_Pkt;
    
    // Reset Packet
    SAMPLE_APP_Reset_t Reset_Pkt;
    
    // Input packet
    SAMPLE_APP_Input_t Input_Pkt;
    
    // Release Packet
    SAMPLE_APP_Release_t Release_Pkt;

    // Input and Output list for telem
    int32 InOut_Count;
    int32 Inputs[FIR2_APP_INOUT_BUFFER_LEN];
    int32 Outputs[FIR2_APP_INOUT_BUFFER_LEN];

     // Has PL
    int32 HasPL;

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

    CFE_TBL_Handle_t TblHandles[FIR2_APP_NUMBER_OF_TABLES];

} FIR2_APP_Data_t;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (FIR2_APP_Main), these
**       functions are not called from any other source module.
*/
void  FIR2_APP_Main(void);
int32 FIR2_APP_Init(void);
void  FIR2_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr);
void  FIR2_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr);
int32 FIR2_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg);
int32 FIR2_APP_Reset(const FIR2_APP_ResetCmd_t *Msg);
int32 FIR2_APP_FullFIR1 (FIR2_APP_FullFIR1_t *Msg);
int32 FIR2_APP_FullFIR0 (FIR2_APP_FullFIR0_t *Msg);
int32 FIR2_APP_PartialFIR1 (FIR2_APP_PartialFIR1_t *Msg);
int32 FIR2_APP_PartialFIR0 (FIR2_APP_PartialFIR0_t *Msg);
int32 FIR2_APP_Input (FIR2_APP_Input_t *Msg);
int32 FIR2_APP_Output (FIR2_APP_Output_t *Msg);
int32 FIR2_APP_Delay (FIR2_APP_NoopCmd_t *Msg);
int32 FIR2_APP_Release (FIR2_APP_NoopCmd_t *Msg);
int32 FIR2_APP_PL_Reply (FIR2_APP_Reply_t *Msg);
int32 FIR2_APP_Noop(const FIR2_APP_NoopCmd_t *Msg);
void  FIR2_APP_GetCrc(const char *TableName);

int32 FIR2_APP_TblValidationFunc(void *TblData);

bool FIR2_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);

#endif /* FIR2_APP_H */
