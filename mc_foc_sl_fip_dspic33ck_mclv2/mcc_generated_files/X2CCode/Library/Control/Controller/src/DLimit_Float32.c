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
/*     Description:  D Controller with
 *                          - Enable Input
 *                          - Initial Condition Input
 *                          - Output Limitation
 *                      Calculation ZOH:
 *                                      z - 1
 *                      y = (Kd*wc --------------- )*u
 *                                 z - exp(-wc*Ts)
 *
 *                      -> y(k) = y(k-1) + b1d.u(k) + b0d.u(k-1) - a0d.yd(k-1)
 */
/* USERCODE-END:Description                                                                                           */
#include "DLimit_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(DLimit_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN              (*pTDLimit_Float32->In)
#define INIT            (*pTDLimit_Float32->D0)
#define ENABLE          (*pTDLimit_Float32->Enable)
#ifndef LIMIT_UP
    #define LIMIT_UP    (*pTDLimit_Float32->max)
    #define LIMIT_DOWN  (*pTDLimit_Float32->min)
#endif

/* Outputs */
#define OUT             (pTDLimit_Float32->Out)

/* Parameter */
#define B0D             (pTDLimit_Float32->b0d)
#define B1D             (pTDLimit_Float32->b1d)
#define A0D             (pTDLimit_Float32->a0d)

/* Variables */
#define IN_OLD          (pTDLimit_Float32->in_old)
#define ENABLE_OLD      (pTDLimit_Float32->enable_old)
#define D_OLD           (OUT)                           /* Old output is also old derivative value */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void DLimit_Float32_Update(DLIMIT_FLOAT32 *pTDLimit_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float32 y;

    if (ENABLE) /* Block enabled */
    {
        if (!ENABLE_OLD)    /* Rising edge of enable signal occurred */
        {
            /* Initialize derivational part */
            D_OLD = INIT;
        }

        /* Derivative term */
        y  =  B0D * IN_OLD;
        y += (B1D * IN);
        y -= (A0D * D_OLD);

        /* Output limitation*/
        if (y > LIMIT_UP)           /* Output is beyond upper limit */
        {
            /* output limitation to upper boundary */
            y = LIMIT_UP;
        }
        else if (y < LIMIT_DOWN)    /* Output is beyond lower limit */
        {
            /* Output limitation to lower boundary */
            y = LIMIT_DOWN;
        }
        /* else: no output limitation */

        /* Assign output */
        OUT = y;
        /* D_OLD = OUT; // To save RAM, the block's Out variable is used for D_OLD. Therefore, this line is obsolete */
    }
    else                /* Block disabled */
    {
        OUT = 0;    /* Reset output */
    }

    /* Save relevant data for next call */
    IN_OLD = IN;
    ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void DLimit_Float32_Init(DLIMIT_FLOAT32 *pTDLimit_Float32)
{
    pTDLimit_Float32->ID = DLIMIT_FLOAT32_ID;
    pTDLimit_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* Preset old values */
    IN_OLD = 0;
    ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 DLimit_Float32_Load(const DLIMIT_FLOAT32 *pTDLimit_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTDLimit_Float32->b0d)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTDLimit_Float32->b0d) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTDLimit_Float32->b0d) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTDLimit_Float32->b0d) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTDLimit_Float32->b1d)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTDLimit_Float32->b1d) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTDLimit_Float32->b1d) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTDLimit_Float32->b1d) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTDLimit_Float32->a0d)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTDLimit_Float32->a0d) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTDLimit_Float32->a0d) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTDLimit_Float32->a0d) >> 24) & 0x000000FF);
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 DLimit_Float32_Save(DLIMIT_FLOAT32 *pTDLimit_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTDLimit_Float32->b0d = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTDLimit_Float32->b1d = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTDLimit_Float32->a0d = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(DLIMIT_FLOAT32_ISLINKED)
void* DLimit_Float32_GetAddress(const DLIMIT_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->D0;
            break;
        case 3:
            addr = (void*)block->max;
            break;
        case 4:
            addr = (void*)block->min;
            break;
        case 5:
            addr = (void*)block->Enable;
            break;
        case 6:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
