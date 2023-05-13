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
 * Define SPEEDTEST App Events IDs
 */

#ifndef SPEEDTEST_APP_EVENTS_H
#define SPEEDTEST_APP_EVENTS_H

#define SPEEDTEST_APP_RESERVED_EID          	0
#define SPEEDTEST_APP_STARTUP_INF_EID       	1
#define SPEEDTEST_APP_COMMAND_ERR_EID       	2
#define SPEEDTEST_APP_COMMANDNOP_INF_EID    	3
#define SPEEDTEST_APP_COMMANDRST_INF_EID    	4
#define SPEEDTEST_APP_INVALID_MSGID_ERR_EID 	5
#define SPEEDTEST_APP_LEN_ERR_EID           	6
#define SPEEDTEST_APP_PIPE_ERR_EID          	7
#define SPEEDTEST_APP_RESET_INF_EID         	8
#define SPEEDTEST_APP_NOSB_PSPL_INF_EID     	8
#define SPEEDTEST_APP_NOSB_PLPS_INF_EID     	9
#define SPEEDTEST_APP_SELFSB_PSPL_INF_EID   	10
#define SPEEDTEST_APP_SELFSB_PSPL_R_INF_EID 	11
#define SPEEDTEST_APP_SELFSB_PLPS_INF_EID   	12
#define SPEEDTEST_APP_SELFSB_PLPS_R_INF_EID 	13
#define SPEEDTEST_APP_CONTROLSB_PSPL_INF_EID 	14
#define SPEEDTEST_APP_CONTROLSB_PLPS_INF_EID 	15

#endif /* SPEEDTEST_APP_EVENTS_H */
