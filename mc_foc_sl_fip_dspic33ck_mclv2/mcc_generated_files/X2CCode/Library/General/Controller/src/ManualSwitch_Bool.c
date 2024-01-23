/*
 * Copyright (c) 2017, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 * $LastChangedDate:: 2022-05-03 15:06:23 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Toggling between the 2 inputs                        **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "ManualSwitch_Bool.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(ManualSwitch_Bool_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1			(*pTManualSwitch_Bool->In1)
#define IN2 		(*pTManualSwitch_Bool->In2)

/* Outputs */
#define OUT 		(pTManualSwitch_Bool->Out)

/* Parameters */
#define TOGGLE		(pTManualSwitch_Bool->Toggle)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void ManualSwitch_Bool_Update(MANUALSWITCH_BOOL *pTManualSwitch_Bool)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    /* if Toggle==0: Out = In1
     * if Toggle==1: Out = In2
     * else:         Out is arbitrary!
     * => Conversion function MUST either set Toggle to 1 or 0!
     */
    OUT = **(&pTManualSwitch_Bool->In1 + (TOGGLE & 0x01));

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void ManualSwitch_Bool_Init(MANUALSWITCH_BOOL *pTManualSwitch_Bool)
{
    pTManualSwitch_Bool->ID = MANUALSWITCH_BOOL_ID;
    pTManualSwitch_Bool->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 ManualSwitch_Bool_Load(const MANUALSWITCH_BOOL *pTManualSwitch_Bool, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)1 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTManualSwitch_Bool->Toggle;
        *dataLength = (uint16)1;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 ManualSwitch_Bool_Save(MANUALSWITCH_BOOL *pTManualSwitch_Bool, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)1)
    {
        error = (uint8)1;
    }
    else
    {
        pTManualSwitch_Bool->Toggle = ((uint8)data[0]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(MANUALSWITCH_BOOL_ISLINKED)
void* ManualSwitch_Bool_GetAddress(const MANUALSWITCH_BOOL* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->In2;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
