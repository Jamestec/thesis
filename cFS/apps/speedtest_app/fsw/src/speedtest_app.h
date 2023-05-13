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
 * Main header file for the SPEEDTEST application
 */

#ifndef SPEEDTEST_APP_H
#define SPEEDTEST_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "speedtest_app_perfids.h"
#include "speedtest_app_msgids.h"
#include "speedtest_app_msg.h"
#include "sample_app_msgids.h"
#include "sample_app_msg.h"

/***********************************************************************/
#define SPEEDTEST_APP_PIPE_DEPTH 32 /* Depth of the Command Pipe for Application */

#define SPEEDTEST_APP_INOUT_BUFFER_LEN 10
#define TIME_S 5
#define TIME_CLK TIME_S*100000000

#define SPEEDTEST_APP_NUMBER_OF_TABLES 1 /* Number of Table(s) */

/* Define filenames of default data images for tables */
#define SPEEDTEST_APP_TABLE_FILE "/cf/FIR_app_tbl.tbl"

#define SPEEDTEST_APP_TABLE_OUT_OF_RANGE_ERR_CODE -1

#define SPEEDTEST_APP_TBL_ELEMENT_1_MAX 10

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
    SPEEDTEST_APP_HkTlm_t HkTlm;

	// No arguments packet
	SPEEDTEST_APP_NoopCmd_t NoArgs_Pkt;

	// CMD Binfile Packet
	SAMPLE_APP_BinFile_t BinFile_Pkt;
	
	// Input packet
	SPEEDTEST_APP_Input_t Input_Pkt;

	// PSPL, PLPS speeds for telem
	int32 In_Count;
	int32 Out_Count;
	double Inputs[SPEEDTEST_APP_INOUT_BUFFER_LEN];
	double Outputs[SPEEDTEST_APP_INOUT_BUFFER_LEN];

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

    CFE_TBL_Handle_t TblHandles[SPEEDTEST_APP_NUMBER_OF_TABLES];

} SPEEDTEST_APP_Data_t;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (SPEEDTEST_APP_Main), these
**       functions are not called from any other source module.
*/
void  SPEEDTEST_APP_Main(void);
int32 SPEEDTEST_APP_Init(void);
void  SPEEDTEST_APP_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr);
void  SPEEDTEST_APP_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr);
int32 SPEEDTEST_APP_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg);

int32 SPEEDTEST_APP_Noop(const SPEEDTEST_APP_NoopCmd_t *Msg);
int32 SPEEDTEST_APP_Reset(const SPEEDTEST_APP_ResetCmd_t *Msg);
int32 SPEEDTEST_APP_NoSB_PSPL(SPEEDTEST_APP_NoSB_PSPL_t *Msg);
int32 SPEEDTEST_APP_NoSB_PLPS(SPEEDTEST_APP_NoSB_PLPS_t *Msg);
int32 SPEEDTEST_APP_SelfSB_PSPL(SPEEDTEST_APP_SelfSB_PSPL_t *Msg);
int32 SPEEDTEST_APP_SelfSB_PSPL_R(SPEEDTEST_APP_Input_t *Msg);
int32 SPEEDTEST_APP_SelfSB_PLPS(SPEEDTEST_APP_SelfSB_PLPS_t *Msg);
int32 SPEEDTEST_APP_SelfSB_PLPS_R(SPEEDTEST_APP_Input_t *Msg);
int32 SPEEDTEST_APP_ControlSB_PSPL(SPEEDTEST_APP_ControlSB_PSPL_t *Msg);
int32 SPEEDTEST_APP_ControlSB_PLPS(SPEEDTEST_APP_ControlSB_PLPS_t *Msg);

bool SPEEDTEST_APP_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);
int32 SPEEDTEST_APP_TblValidationFunc(void *TblData);
void  SPEEDTEST_APP_GetCrc(const char *TableName);

#endif /* SPEEDTEST_APP_H */
