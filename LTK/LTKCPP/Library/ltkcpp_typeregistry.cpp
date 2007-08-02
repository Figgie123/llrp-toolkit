
/*
 ***************************************************************************
 *  Copyright 2007 Impinj, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ***************************************************************************
 */


#include "ltkcpp_platform.h"
#include "ltkcpp_base.h"


namespace LLRP
{

CTypeRegistry::CTypeRegistry (void)
{
    memset(m_apStdMessageTypeDescriptors, 0,
        sizeof m_apStdMessageTypeDescriptors);

    memset(m_apStdParameterTypeDescriptors, 0,
        sizeof m_apStdParameterTypeDescriptors);
}

CTypeRegistry::~CTypeRegistry (void)
{
}

EResultCode
CTypeRegistry::enroll (
  const CTypeDescriptor *       pTypeDescriptor)
{
    if(0 == pTypeDescriptor->m_VendorID)
    {
        if(1023u < pTypeDescriptor->m_TypeNum)
        {
            return RC_EnrollBadTypeNumber;
        }

        /*
         * Standard message or parameter
         */
        if(pTypeDescriptor->m_bIsMessage)
        {
            m_apStdMessageTypeDescriptors[pTypeDescriptor->m_TypeNum] =
                pTypeDescriptor;
        }
        else
        {
            m_apStdParameterTypeDescriptors[pTypeDescriptor->m_TypeNum] =
                pTypeDescriptor;
        }
    }
    else
    {
        /* TODO: Custom messages and parameter */
        return RC_Botch;
    }

    return RC_OK;
}

const CTypeDescriptor *
CTypeRegistry::lookupMessage (
  unsigned int                  MessageTypeNum) const
{
    if(1023u < MessageTypeNum)
    {
        return NULL;
    }

    return m_apStdMessageTypeDescriptors[MessageTypeNum];
}

const CTypeDescriptor *
CTypeRegistry::lookupParameter (
  unsigned int                  ParameterTypeNum) const
{
    if(1023u < ParameterTypeNum)
    {
        /* throw exception? */
        return NULL;
    }

    return m_apStdParameterTypeDescriptors[ParameterTypeNum];
}

const CTypeDescriptor *
CTypeRegistry::lookupCustomMessage (
  unsigned int                  VendorID,
  unsigned int                  MessageSubTypeNum) const
{
    /* TODO: custom messages */
    return NULL;
}

const CTypeDescriptor *
CTypeRegistry::lookupCustomParameter (
  unsigned int                  VendorID,
  unsigned int                  ParameterSubTypeNum) const
{
    /* TODO: custom parameters */
    return NULL;
}


}; /* namespace LLRP */
