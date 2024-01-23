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
#include "Bilin_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Bilin_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBilin_Float32->In)

/* Outputs */
#define OUT			(pTBilin_Float32->Out)

/* Parameter */
#define	A1 			(pTBilin_Float32->a1)
#define	B0			(pTBilin_Float32->b0)
#define	B1			(pTBilin_Float32->b1)

/* Variables */
#define IN_OLD		(pTBilin_Float32->in_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Bilin_Float32_Update(BILIN_FLOAT32 *pTBilin_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 temp;

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
void Bilin_Float32_Init(BILIN_FLOAT32 *pTBilin_Float32)
{
    pTBilin_Float32->ID = BILIN_FLOAT32_ID;
    pTBilin_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* reset old input value */
    IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_Float32_Load(const BILIN_FLOAT32 *pTBilin_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTBilin_Float32->b0)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTBilin_Float32->b0) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTBilin_Float32->b0) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTBilin_Float32->b0) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTBilin_Float32->b1)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTBilin_Float32->b1) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTBilin_Float32->b1) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTBilin_Float32->b1) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTBilin_Float32->a1)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTBilin_Float32->a1) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTBilin_Float32->a1) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTBilin_Float32->a1) >> 24) & 0x000000FF);
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_Float32_Save(BILIN_FLOAT32 *pTBilin_Float32, const uint8 data[], uint16 dataLength)
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
        pTBilin_Float32->b0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTBilin_Float32->b1 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTBilin_Float32->a1 = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BILIN_FLOAT32_ISLINKED)
void* Bilin_Float32_GetAddress(const BILIN_FLOAT32* block, uint16 elementId)
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
