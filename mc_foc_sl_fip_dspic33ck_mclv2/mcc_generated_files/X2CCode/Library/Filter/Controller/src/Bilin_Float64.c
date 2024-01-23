/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2118 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:	First order filter function                        
 * Calculation:										 
 *	       			 b0.z + b1							   		 
 * 				y = ----------- u						   		 
 *          		  z + a1				
 *					-> y(k) = u(k).b0 + u(k-1).b1 - y(k-1).a1																			 
 */
/* USERCODE-END:Description                                                                                           */
#include "Bilin_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Bilin_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBilin_Float64->In)

/* Outputs */
#define OUT			(pTBilin_Float64->Out)

/* Parameter */
#define	A1 			(pTBilin_Float64->a1)
#define	B0			(pTBilin_Float64->b0)
#define	B1			(pTBilin_Float64->b1)

/* Variables */
#define IN_OLD		(pTBilin_Float64->in_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Bilin_Float64_Update(BILIN_FLOAT64 *pTBilin_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp;

    /* do the filtering */
	temp  = B1 * IN_OLD;	/* y = b1.u(k-1) */
	temp += (B0 * IN);		/* y = b1.u(k-1) + b0.u(k) */
	temp -= (A1 * OUT);		/* y = b1.u(k-1) + b0.u(k) - a1.y(k-1) */

	/* save values for next update call and assign output */
	IN_OLD = IN;
	OUT    = temp;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Bilin_Float64_Init(BILIN_FLOAT64 *pTBilin_Float64)
{
    pTBilin_Float64->ID = BILIN_FLOAT64_ID;
    pTBilin_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* reset old input value */
    IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_Float64_Load(const BILIN_FLOAT64 *pTBilin_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)24 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTBilin_Float64->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTBilin_Float64->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTBilin_Float64->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTBilin_Float64->b1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTBilin_Float64->a1)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTBilin_Float64->a1) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)24;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_Float64_Save(BILIN_FLOAT64 *pTBilin_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)24)
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
        pTBilin_Float64->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTBilin_Float64->b1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTBilin_Float64->a1 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BILIN_FLOAT64_ISLINKED)
void* Bilin_Float64_GetAddress(const BILIN_FLOAT64* block, uint16 elementId)
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
