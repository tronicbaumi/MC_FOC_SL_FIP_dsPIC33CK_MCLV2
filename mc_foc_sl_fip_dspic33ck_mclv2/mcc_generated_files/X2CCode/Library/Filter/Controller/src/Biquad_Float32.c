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
#include "Biquad_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Biquad_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBiquad_Float32->In)

/* Outputs */
#define OUT			(pTBiquad_Float32->Out)

/* Parameter */
#define	A1 			(pTBiquad_Float32->a1)
#define	A2 			(pTBiquad_Float32->a2)
#define	B0			(pTBiquad_Float32->b0)
#define	B1			(pTBiquad_Float32->b1)
#define	B2 			(pTBiquad_Float32->b2)

/* Variables */
#define IN_OLD		(pTBiquad_Float32->in_old)
#define IN_VERYOLD	(pTBiquad_Float32->in_veryold)
#define OUT_OLD		(pTBiquad_Float32->out_old)
#define OUT_VERYOLD (pTBiquad_Float32->out_veryold)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Biquad_Float32_Update(BIQUAD_FLOAT32 *pTBiquad_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float32 temp;

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
void Biquad_Float32_Init(BIQUAD_FLOAT32 *pTBiquad_Float32)
{
    pTBiquad_Float32->ID = BIQUAD_FLOAT32_ID;
    pTBiquad_Float32->Out = 0;
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
uint8 Biquad_Float32_Load(const BIQUAD_FLOAT32 *pTBiquad_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)20 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTBiquad_Float32->b0)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTBiquad_Float32->b0) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTBiquad_Float32->b0) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTBiquad_Float32->b0) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTBiquad_Float32->b1)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTBiquad_Float32->b1) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTBiquad_Float32->b1) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTBiquad_Float32->b1) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTBiquad_Float32->b2)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTBiquad_Float32->b2) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTBiquad_Float32->b2) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTBiquad_Float32->b2) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTBiquad_Float32->a1)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTBiquad_Float32->a1) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTBiquad_Float32->a1) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTBiquad_Float32->a1) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTBiquad_Float32->a2)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTBiquad_Float32->a2) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTBiquad_Float32->a2) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTBiquad_Float32->a2) >> 24) & 0x000000FF);
        *dataLength = (uint16)20;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Biquad_Float32_Save(BIQUAD_FLOAT32 *pTBiquad_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)20)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTBiquad_Float32->b0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTBiquad_Float32->b1 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTBiquad_Float32->b2 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTBiquad_Float32->a1 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTBiquad_Float32->a2 = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BIQUAD_FLOAT32_ISLINKED)
void* Biquad_Float32_GetAddress(const BIQUAD_FLOAT32* block, uint16 elementId)
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
