/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 2800 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:    P Controller with
 *                         - Enable Input
 *                         - Output Limitation
 *                     Calculation ZOH:
 *
 *                         y = Kp * u
 *
 *                     -> y(k) = b1.u(k)
 */
/* USERCODE-END:Description                                                                                           */
#include "PLimit_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PLimit_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN              (*pTPLimit_Float64->In)
#define ENABLE          (*pTPLimit_Float64->Enable)
#ifndef LIMIT_UP
    #define LIMIT_UP    (*pTPLimit_Float64->max)
    #define LIMIT_DOWN  (*pTPLimit_Float64->min)
#endif

/* Outputs */
#define OUT             (pTPLimit_Float64->Out)

/* Parameter */
#define B1              (pTPLimit_Float64->b1)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PLimit_Float64_Update(PLIMIT_FLOAT64 *pTPLimit_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float64 y;

    if (ENABLE) /* Block enabled */
    {
        /* Proportional term */
        y = B1 * IN;

        /* Output limitation */
        if (y > LIMIT_UP)           /* output is beyond upper limit */
        {
            /* output limitation to upper boundary */
            y = LIMIT_UP;
        }
        else if (y < LIMIT_DOWN)    /* output is beyond lower limit */
        {
            /* output limitation to lower boundary */
            y = LIMIT_DOWN;
        }
        /* else: output is within limits */

        /* Assign output */
        OUT = y;
    }
    else                /* Block disabled */
    {
        OUT = 0;    /* reset output */
    }

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void PLimit_Float64_Init(PLIMIT_FLOAT64 *pTPLimit_Float64)
{
    pTPLimit_Float64->ID = PLIMIT_FLOAT64_ID;
    pTPLimit_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PLimit_Float64_Load(const PLIMIT_FLOAT64 *pTPLimit_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTPLimit_Float64->b1) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PLimit_Float64_Save(PLIMIT_FLOAT64 *pTPLimit_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        pTPLimit_Float64->b1 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PLIMIT_FLOAT64_ISLINKED)
void* PLimit_Float64_GetAddress(const PLIMIT_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->max;
            break;
        case 3:
            addr = (void*)block->min;
            break;
        case 4:
            addr = (void*)block->Enable;
            break;
        case 5:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
