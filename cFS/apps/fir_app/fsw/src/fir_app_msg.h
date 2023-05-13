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
 * Define FIR App  Messages and info
 */

#ifndef FIR_APP_MSG_H
#define FIR_APP_MSG_H

#include "sample_app_msg.h"

/*
** FIR App command codes
*/
#define FIR_APP_NOOP_CC 					0
#define FIR_APP_RESET_CC					1
#define FIR_APP_FULLFIR1_CC				2
#define FIR_APP_FULLFIR0_CC				3
#define FIR_APP_PARTIALFIR1_CC			4
#define FIR_APP_PARTIALFIR0_CC			5
#define FIR_APP_INPUT_CC						6
#define FIR_APP_OUTPUT_CC					7
#define FIR_APP_DELAY_CC					8
#define FIR_APP_RELEASE_CC				9
#define FIR_APP_PL_REPLY_CC				10

/*************************************************************************/

/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHeader; /**< \brief Command header */
} FIR_APP_NoArgsCmd_t;

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef FIR_APP_NoArgsCmd_t FIR_APP_NoopCmd_t;
typedef FIR_APP_NoArgsCmd_t FIR_APP_ResetCmd_t;
typedef FIR_APP_NoArgsCmd_t FIR_APP_FullFIR1_t;
typedef FIR_APP_NoArgsCmd_t FIR_APP_FullFIR0_t;
typedef FIR_APP_NoArgsCmd_t FIR_APP_PartialFIR1_t;
typedef FIR_APP_NoArgsCmd_t FIR_APP_PartialFIR0_t;

typedef SAMPLE_APP_Output_Pkt_t FIR_APP_Output_t;
typedef SAMPLE_APP_Reply_t FIR_APP_Reply_t;

/*************************************************************************/
/*
** Type definition (FIR App housekeeping)
*/

typedef struct
{
    uint8 CommandErrorCounter;
    uint8 CommandCounter;
	int32 HasPL;
    char Inputs[200];
	char Outputs[200];
} FIR_APP_HkTlm_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t  TelemetryHeader; /**< \brief Telemetry header */
    FIR_APP_HkTlm_Payload_t Payload;         /**< \brief Telemetry payload */
} FIR_APP_HkTlm_t;

/*************************************************************************/
/*
** Type definition (FIR App Program PL)
*/

typedef struct
{
    char binfile[128];
} FIR_APP_BinFile_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    FIR_APP_BinFile_Payload_t Payload;   /**< \brief Command payload */
} FIR_APP_BinFile_t;

typedef struct
{
    int32 number;
} FIR_APP_Input_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    FIR_APP_Input_Payload_t Payload;   /**< \brief Command payload */
} FIR_APP_Input_t;

#endif /* FIR_APP_MSG_H */
