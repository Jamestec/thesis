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
 * Auto-Generated stub implementations for functions defined in cfe_tbl_core_internal header
 */

#include "cfe_tbl_core_internal.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_TBL_CleanUpApp()
 * ----------------------------------------------------
 */
int32 CFE_TBL_CleanUpApp(CFE_ES_AppId_t AppId)
{
    UT_GenStub_SetupReturnBuffer(CFE_TBL_CleanUpApp, int32);

    UT_GenStub_AddParam(CFE_TBL_CleanUpApp, CFE_ES_AppId_t, AppId);

    UT_GenStub_Execute(CFE_TBL_CleanUpApp, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_TBL_CleanUpApp, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_TBL_EarlyInit()
 * ----------------------------------------------------
 */
int32 CFE_TBL_EarlyInit(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_TBL_EarlyInit, int32);

    UT_GenStub_Execute(CFE_TBL_EarlyInit, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_TBL_EarlyInit, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_TBL_TaskMain()
 * ----------------------------------------------------
 */
void CFE_TBL_TaskMain(void)
{

    UT_GenStub_Execute(CFE_TBL_TaskMain, Basic, NULL);
}
