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
 * $LastChangedRevision: 2077 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: One dimensional look-up table with selectable number of entries */
/* USERCODE-END:Description                                                                                           */
#include "LookupTable1D_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(LookupTable1D_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN_X        (*pTLookupTable1D_Float64->x)

/* Outputs */
#define OUT         (pTLookupTable1D_Float64->Out)

/* Parameters */
#define TABLE_DATA   (pTLookupTable1D_Float64->Table)

#define DIM_X        (pTLookupTable1D_Float64->dimX)
#define GAIN_X       (pTLookupTable1D_Float64->gainX)
#define OFFSET_X     (pTLookupTable1D_Float64->offsetX)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void LookupTable1D_Float64_Update(LOOKUPTABLE1D_FLOAT64 *pTLookupTable1D_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float64 tmp;
    uint16 idxx;
    float64 fact, factx, deltax;
    float64 inx;
    
    /** - scale input */
    inx = (IN_X - OFFSET_X) * GAIN_X;

    /** - check boundaries */
    if (inx < 0)
    {
        /* input below lower boundary -> cutoff */
        tmp = TABLE_DATA[0];       /* f(0) */
    }
    else if ((uint16)inx >= DIM_X) /* uint16 cast is needed to get floor value of input */
    {
        /* input above higher boundary -> cutoff */
        tmp = TABLE_DATA[DIM_X];   /* f(end) */
    }
    else
    {
        /* input within boundaries -> interpolation */
        /** - calculate table index */
        idxx = (uint16)inx;            /*  x */
        
        /** - calculate fractual part */
        deltax = inx - idxx;            /* dx */
        
        /** - calculate value at lattice points */
        fact  = TABLE_DATA[idxx];       /* f(x) */
        factx = TABLE_DATA[idxx + 1];   /* f(x+1) */

        /** - linear interpolation */
        tmp = (factx - fact) * deltax;  /* dx*(f(x+1) - f(x)) */
        tmp = fact + tmp;               /* f(x) + dx*(f(x+1) - f(x)) */
    }

    OUT = tmp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void LookupTable1D_Float64_Init(LOOKUPTABLE1D_FLOAT64 *pTLookupTable1D_Float64)
{
    pTLookupTable1D_Float64->ID = LOOKUPTABLE1D_FLOAT64_ID;
    pTLookupTable1D_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable1D_Float64_Load(const LOOKUPTABLE1D_FLOAT64 *pTLookupTable1D_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)14 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTLookupTable1D_Float64->dimX & 0x00FF);
        data[1] = (uint8)((pTLookupTable1D_Float64->dimX >> 8) & 0x00FF);
        data[2] = (uint8)((*(uint32*)&(pTLookupTable1D_Float64->gainX)) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTLookupTable1D_Float64->gainX) >> 8) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTLookupTable1D_Float64->gainX) >> 16) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTLookupTable1D_Float64->gainX) >> 24) & 0x000000FF);
        data[6] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX)) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 8) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 16) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 24) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 32) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 40) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 48) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTLookupTable1D_Float64->offsetX) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)14;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable1D_Float64_Save(LOOKUPTABLE1D_FLOAT64 *pTLookupTable1D_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;
    uint64 tmp64;

    if (dataLength != (uint16)14)
    {
        error = (uint8)1;
    }
    else
    {
        pTLookupTable1D_Float64->dimX = ((uint16)data[0] + \
            ((uint16)data[1] << 8));
        tmp32 = (uint32)data[2] + \
            ((uint32)data[3] << 8) + ((uint32)data[4] << 16) + \
            ((uint32)data[5] << 24);
        pTLookupTable1D_Float64->gainX = (float32)(*(float32*)&tmp32);
        tmp64 = (uint64)data[6] + \
            ((uint64)data[7] << 8) + ((uint64)data[8] << 16) + \
            ((uint64)data[9] << 24) + ((uint64)data[10] << 32) + \
            ((uint64)data[11] << 40) + ((uint64)data[12] << 48) + \
            ((uint64)data[13] << 56);
        pTLookupTable1D_Float64->offsetX = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(LOOKUPTABLE1D_FLOAT64_ISLINKED)
void* LookupTable1D_Float64_GetAddress(const LOOKUPTABLE1D_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->x;
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
