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
 * Define SpeedTest App  Messages and info
 */

#ifndef SPEEDTEST_APP_MSG_H
#define SPEEDTEST_APP_MSG_H

#include "sample_app_msg.h"

/*
** SpeedTest App command codes
*/
#define SPEEDTEST_APP_NOOP_CC 				0
#define SPEEDTEST_APP_RESET_CC				1
#define SPEEDTEST_APP_NOSB_PSPL_CC			2
#define SPEEDTEST_APP_NOSB_PLPS_CC			3
#define SPEEDTEST_APP_SELFSB_PSPL_CC		4
#define SPEEDTEST_APP_SELFSB_PSPL_R_CC		5
#define SPEEDTEST_APP_SELFSB_PLPS_CC		6
#define SPEEDTEST_APP_SELFSB_PLPS_R_CC		7
#define SPEEDTEST_APP_CONTROLSN_PSPL_CC		8
#define SPEEDTEST_APP_CONTROLPSPL_CC		9

/*************************************************************************/

/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHeader; /**< \brief Command header */
} SPEEDTEST_APP_NoArgsCmd_t;

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_NoopCmd_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_ResetCmd_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_NoSB_PSPL_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_NoSB_PLPS_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_SelfSB_PSPL_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_SelfSB_PLPS_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_ControlSB_PSPL_t;
typedef SPEEDTEST_APP_NoArgsCmd_t SPEEDTEST_APP_ControlSB_PLPS_t;

typedef SAMPLE_APP_Output_Pkt_t SPEEDTEST_APP_Output_t;
typedef SAMPLE_APP_Reply_t SPEEDTEST_APP_Reply_t;

/*************************************************************************/
/*
** Type definition (SPEEDTEST App housekeeping)
*/

typedef struct
{
    uint8 CommandErrorCounter;
    uint8 CommandCounter;
    char Inputs[200];
	char Outputs[200];
} SPEEDTEST_APP_HkTlm_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t  TelemetryHeader; /**< \brief Telemetry header */
    SPEEDTEST_APP_HkTlm_Payload_t Payload;         /**< \brief Telemetry payload */
} SPEEDTEST_APP_HkTlm_t;

/*************************************************************************/
/*
** Type definition (SpeedTest App Program PL)
*/

typedef struct
{
    char binfile[128];
} SPEEDTEST_APP_BinFile_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SPEEDTEST_APP_BinFile_Payload_t Payload;   /**< \brief Command payload */
} SPEEDTEST_APP_BinFile_t;

typedef struct
{
    int32 number;
} SPEEDTEST_APP_Input_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SPEEDTEST_APP_Input_Payload_t Payload;   /**< \brief Command payload */
} SPEEDTEST_APP_Input_t;

#endif /* SPEEDTEST_APP_MSG_H */
