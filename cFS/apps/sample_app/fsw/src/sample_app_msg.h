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
 * Define SAMPLE App  Messages and info
 */

#ifndef SAMPLE_APP_MSG_H
#define SAMPLE_APP_MSG_H

/*
** SAMPLE App command codes
*/
#define PL_CONTROL_APP_NOOP_CC            0
#define PL_CONTROL_APP_RESET_COUNTERS_CC  1
#define PL_CONTROL_APP_PROCESS_CC         2
#define PL_CONTROL_APP_FULL_PROGRAM_CC    3
#define PL_CONTROL_APP_PARTIAL_PROGRAM_CC 4
#define PL_CONTROL_APP_RESET_CC           5
#define PL_CONTROL_APP_INPUT_CC           6
#define PL_CONTROL_APP_OUTPUT_CC          7
#define PL_CONTROL_APP_RELEASE_CC         8
#define PL_CONTROL_APP_QUERY_CC           9
#define PL_CONTROL_APP_COUNTER_TEST_CC    10
#define PL_CONTROL_APP_MAKE_BUSY_CC       11

/*************************************************************************/

/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    CFE_MSG_CommandHeader_t CmdHeader; /**< \brief Command header */
} SAMPLE_APP_NoArgsCmd_t;

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef SAMPLE_APP_NoArgsCmd_t SAMPLE_APP_NoopCmd_t;
typedef SAMPLE_APP_NoArgsCmd_t SAMPLE_APP_ResetCountersCmd_t;
typedef SAMPLE_APP_NoArgsCmd_t SAMPLE_APP_ProcessCmd_t;
typedef SAMPLE_APP_NoArgsCmd_t SAMPLE_APP_Output_t;

/*************************************************************************/
/*
** Type definition (SAMPLE App housekeeping)
*/

typedef struct
{
    uint8 CommandErrorCounter;
    uint8 CommandCounter;
    char binfile[128];
    cpuaddr base_addr;
    int32 input_offset;
    int32 start_offset;
    int32 done_offset;
    int32 output_offset;
    int32 reply_msgid;
    int32 reply_cmdid;
} SAMPLE_APP_HkTlm_Payload_t;

typedef struct
{
    CFE_MSG_TelemetryHeader_t  TelemetryHeader; /**< \brief Telemetry header */
    SAMPLE_APP_HkTlm_Payload_t Payload;         /**< \brief Telemetry payload */
} SAMPLE_APP_HkTlm_t;

/*************************************************************************/
/*
** Type definition (SAMPLE App Program PL)
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
} SAMPLE_APP_BinFile_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_BinFile_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_BinFile_t;

typedef struct
{
    cpuaddr base_addr;
    int32 reset_offset;
    int32 reply_msgid;
    int32 reply_cmdid;
} SAMPLE_APP_Reset_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Reset_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Reset_t;

typedef struct
{
    int32 number;
    cpuaddr base_addr;
    int32 input_offset;
    int32 start_offset;
    int32 done_offset;
    int32 output_offset;
    int32 reply_msgid;
    int32 reply_cmdid;
} SAMPLE_APP_Input_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Input_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Input_t;

typedef struct
{
    int32 Done;
    int32 Output;
} SAMPLE_APP_Output_Pkt_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Output_Pkt_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Output_Pkt_t;

typedef struct
{
    int32 reply_msgid;
    int32 reply_cmdid;
} SAMPLE_APP_Release_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Release_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Release_t;

typedef struct
{
    int32 reply_msgid;
    int32 reply_cmdid;
} SAMPLE_APP_Query_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Query_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Query_t;

typedef struct
{
    int32 Reply;
} SAMPLE_APP_Reply_Payload_t;

typedef struct
{
    CFE_MSG_CommandHeader_t       CmdHeader; /**< \brief Command header */
    SAMPLE_APP_Reply_Payload_t Payload;   /**< \brief Command payload */
} SAMPLE_APP_Reply_t;

#endif /* SAMPLE_APP_MSG_H */
