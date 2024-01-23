/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 2841 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:
 *  Arcsine calculation
 */
/* USERCODE-END:Description                                                                                           */
#include "Asin_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Asin_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Inputs */
#define IN      (*pTAsin_FiP16->In)

/* Outputs */
#define OUT     (pTAsin_FiP16->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Asin_FiP16_Update(ASIN_FIP16 *pTAsin_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int16 out;
    uint16 in;

    if (IN >= 0)
    {
        /* Positive input */
        in = (uint16)IN;                    /* Cast to unsigned integer */
        in = in << 1;                       /* Scale from 0..1 to 0..2 */
#if defined(ACOS_FIP16_ID)
        LOOKUP16(Acos_Table16, in, out);    /* Calculate output with scaled input */
#else
        LOOKUP16(Asin_Table16, in, out);    /* Calculate output with scaled input */
#endif
        OUT = out;                          /* Assign output */
    }
    else
    {
        /* Negative input */
        uint16 in;

        /* Invert & cast input signal and consider special case IN = -1 */
        if (IN == (int16)0x8000)
        {
            in = (uint16)0x7FFF;
        }
        else
        {
            in = (uint16)-IN;
        }

        in = in << 1;                       /* Scale from 0..1 to 0..2 */
#if defined(ACOS_FIP16_ID)
        LOOKUP16(Acos_Table16, in, out);    /* Calculate output with scaled & inverted input */
        OUT = (int16)0x7FFF - out;          /* Shift & mirror output signal */
#else
        LOOKUP16(Asin_Table16, in, out);    /* Calculate output with scaled & inverted input */
        OUT = -out;                         /* Mirror output signal */
#endif
    }

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Asin_FiP16_Init(ASIN_FIP16 *pTAsin_FiP16)
{
    pTAsin_FiP16->ID = ASIN_FIP16_ID;
    pTAsin_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** No Load function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** No Save function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ASIN_FIP16_ISLINKED)
void* Asin_FiP16_GetAddress(const ASIN_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
