/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
 * $LastChangedDate:: 2021-03-16 17:27:31 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:	Second order filter function                        
 * Calculation:										 
 *	       			 b0.z^2 + b1.z + b2							   		 
 * 				y = -------------------- u						   		 
 *          		  z^2 + a1.z + a2				
 *					-> y(k) = u(k).b0 + u(k-1).b1 + u(k-2).b2 - y(k-1).a1 - y(k-2).a2																			 
 */
/* USERCODE-END:Description                                                                                           */
#include "Biquad_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Biquad_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBiquad_Float64->In)

/* Outputs */
#define OUT			(pTBiquad_Float64->Out)

/* Parameter */
#define	A1 			(pTBiquad_Float64->a1)
#define	A2 			(pTBiquad_Float64->a2)
#define	B0			(pTBiquad_Float64->b0)
#define	B1			(pTBiquad_Float64->b1)
#define	B2 			(pTBiquad_Float64->b2)

/* Variables */
#define IN_OLD		(pTBiquad_Float64->in_old)
#define IN_VERYOLD	(pTBiquad_Float64->in_veryold)
#define OUT_OLD		(pTBiquad_Float64->out_old)
#define OUT_VERYOLD (pTBiquad_Float64->out_veryold)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Biquad_Float64_Update(BIQUAD_FLOAT64 *pTBiquad_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float64 temp;

	temp  =  B2 * IN_VERYOLD;	/* y(k) = b2.u(k-2) */
	temp += (B1 * IN_OLD);	    /* y(k) = b2.u(k-2) + b1.u(k-1) */
	temp += (B0 * IN);	        /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) */

	temp -= (A2 * OUT_VERYOLD);	/* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) */
	temp -= (A1 * OUT_OLD);		/* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) - a1.y(k-1) */

	/* assign output and set values for next update call */
    OUT         = temp;
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = OUT;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Biquad_Float64_Init(BIQUAD_FLOAT64 *pTBiquad_Float64)
{
    pTBiquad_Float64->ID = BIQUAD_FLOAT64_ID;
    pTBiquad_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* reset old values */
    IN_OLD      = 0;
    IN_VERYOLD  = 0;
    OUT_OLD     = 0;
    OUT_VERYOLD = 0;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Biquad_Float64_Load(const BIQUAD_FLOAT64 *pTBiquad_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)40 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTBiquad_Float64->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTBiquad_Float64->b1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTBiquad_Float64->b2) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTBiquad_Float64->a1) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(pTBiquad_Float64->a2) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)40;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Biquad_Float64_Save(BIQUAD_FLOAT64 *pTBiquad_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)40)
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
        pTBiquad_Float64->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTBiquad_Float64->b1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTBiquad_Float64->b2 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTBiquad_Float64->a1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        pTBiquad_Float64->a2 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BIQUAD_FLOAT64_ISLINKED)
void* Biquad_Float64_GetAddress(const BIQUAD_FLOAT64* block, uint16 elementId)
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
