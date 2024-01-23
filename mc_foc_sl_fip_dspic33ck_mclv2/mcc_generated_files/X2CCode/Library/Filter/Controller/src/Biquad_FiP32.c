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
#include "Biquad_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Biquad_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBiquad_FiP32->In)		    /* Q31 */

/* Outputs */
#define OUT			(pTBiquad_FiP32->Out)		    /* Q31 */

/* Parameter */
#define A1          (pTBiquad_FiP32->a1)            /* Qa1 */
#define A2          (pTBiquad_FiP32->a2)            /* Qa2 */
#define B0          (pTBiquad_FiP32->b0)            /* Qb0 */
#define B1          (pTBiquad_FiP32->b1)            /* Qb1 */
#define B2          (pTBiquad_FiP32->b2)            /* Qb2 */
#define SFRA1       (pTBiquad_FiP32->sfra1)         /* a1 */
#define SFRA2       (pTBiquad_FiP32->sfra2)         /* a2 */
#define SFRB0       (pTBiquad_FiP32->sfrb0)         /* b0 */
#define SFRB1       (pTBiquad_FiP32->sfrb1)         /* b1 */
#define SFRB2       (pTBiquad_FiP32->sfrb2)         /* b2 */

/* Variables */
#define IN_OLD		(pTBiquad_FiP32->in_old)	    /* Q31 */
#define IN_VERYOLD	(pTBiquad_FiP32->in_veryold)	/* Q31 */
#define OUT_OLD		(pTBiquad_FiP32->out_old)	    /* Q31 */
#define OUT_VERYOLD (pTBiquad_FiP32->out_veryold)   /* Q31 */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Biquad_FiP32_Update(BIQUAD_FIP32 *pTBiquad_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int64 temp;

    temp  =  ((int64)B2 * (int64)IN_VERYOLD)  >> SFRB2;     /* y(k) = b2.u(k-2) */
    temp += (((int64)B1 * (int64)IN_OLD)      >> SFRB1);    /* y(k) = b2.u(k-2) + b1.u(k-1) */
    temp += (((int64)B0 * (int64)IN)          >> SFRB0);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) */

    temp -= (((int64)A2 * (int64)OUT_VERYOLD) >> SFRA2);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) */
    temp -= (((int64)A1 * (int64)OUT_OLD)     >> SFRA1);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) - a1.y(k-1) */

	/* check for overflow */
    LIMIT(temp, INT32_MAX);

	/* assign output and set values for next update call */
    OUT         = (int32)temp;
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = OUT;
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Biquad_FiP32_Init(BIQUAD_FIP32 *pTBiquad_FiP32)
{
    pTBiquad_FiP32->ID = BIQUAD_FIP32_ID;
    pTBiquad_FiP32->Out = 0;
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
uint8 Biquad_FiP32_Load(const BIQUAD_FIP32 *pTBiquad_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)25 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTBiquad_FiP32->b0 & 0x000000FF);
        data[1] = (uint8)((pTBiquad_FiP32->b0 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTBiquad_FiP32->b0 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTBiquad_FiP32->b0 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTBiquad_FiP32->b1 & 0x000000FF);
        data[5] = (uint8)((pTBiquad_FiP32->b1 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTBiquad_FiP32->b1 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTBiquad_FiP32->b1 >> 24) & 0x000000FF);
        data[8] = (uint8)(pTBiquad_FiP32->b2 & 0x000000FF);
        data[9] = (uint8)((pTBiquad_FiP32->b2 >> 8) & 0x000000FF);
        data[10] = (uint8)((pTBiquad_FiP32->b2 >> 16) & 0x000000FF);
        data[11] = (uint8)((pTBiquad_FiP32->b2 >> 24) & 0x000000FF);
        data[12] = (uint8)(pTBiquad_FiP32->a1 & 0x000000FF);
        data[13] = (uint8)((pTBiquad_FiP32->a1 >> 8) & 0x000000FF);
        data[14] = (uint8)((pTBiquad_FiP32->a1 >> 16) & 0x000000FF);
        data[15] = (uint8)((pTBiquad_FiP32->a1 >> 24) & 0x000000FF);
        data[16] = (uint8)(pTBiquad_FiP32->a2 & 0x000000FF);
        data[17] = (uint8)((pTBiquad_FiP32->a2 >> 8) & 0x000000FF);
        data[18] = (uint8)((pTBiquad_FiP32->a2 >> 16) & 0x000000FF);
        data[19] = (uint8)((pTBiquad_FiP32->a2 >> 24) & 0x000000FF);
        data[20] = (uint8)pTBiquad_FiP32->sfrb0;
        data[21] = (uint8)pTBiquad_FiP32->sfrb1;
        data[22] = (uint8)pTBiquad_FiP32->sfrb2;
        data[23] = (uint8)pTBiquad_FiP32->sfra1;
        data[24] = (uint8)pTBiquad_FiP32->sfra2;
        *dataLength = (uint16)25;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Biquad_FiP32_Save(BIQUAD_FIP32 *pTBiquad_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)25)
    {
        error = (uint8)1;
    }
    else
    {
        pTBiquad_FiP32->b0 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTBiquad_FiP32->b1 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTBiquad_FiP32->b2 = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTBiquad_FiP32->a1 = UINT32_TO_INT32((uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24));
        pTBiquad_FiP32->a2 = UINT32_TO_INT32((uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24));
        pTBiquad_FiP32->sfrb0 = UINT8_TO_INT8((uint8)data[20]);
        pTBiquad_FiP32->sfrb1 = UINT8_TO_INT8((uint8)data[21]);
        pTBiquad_FiP32->sfrb2 = UINT8_TO_INT8((uint8)data[22]);
        pTBiquad_FiP32->sfra1 = UINT8_TO_INT8((uint8)data[23]);
        pTBiquad_FiP32->sfra2 = UINT8_TO_INT8((uint8)data[24]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BIQUAD_FIP32_ISLINKED)
void* Biquad_FiP32_GetAddress(const BIQUAD_FIP32* block, uint16 elementId)
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
