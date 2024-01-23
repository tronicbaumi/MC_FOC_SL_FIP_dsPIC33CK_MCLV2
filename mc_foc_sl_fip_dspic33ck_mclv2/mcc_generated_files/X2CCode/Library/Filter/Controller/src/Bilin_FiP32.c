/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
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
#include "Bilin_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Bilin_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBilin_FiP32->In)		/* Q31 */

/* Outputs */
#define OUT			(pTBilin_FiP32->Out)		/* Q31 */

/* Parameter */
#define	A1 			(pTBilin_FiP32->a1)		    /* Qa1 */
#define	B0			(pTBilin_FiP32->b0)		    /* Qb0 */
#define	B1			(pTBilin_FiP32->b1)		    /* Qb1 */
#define SFRA1		(pTBilin_FiP32->sfra1)		/* a1 */
#define SFRB0		(pTBilin_FiP32->sfrb0)		/* b0 */
#define SFRB1       (pTBilin_FiP32->sfrb1)      /* b1 */

/* Variables */
#define IN_OLD		(pTBilin_FiP32->in_old)	    /* Q31 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Bilin_FiP32_Update(BILIN_FIP32 *pTBilin_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 temp;

    /* do the filtering */
	temp  =  ((int64)B1 * (int64)IN_OLD) >> SFRB1;	/* y = b1.u(k-1) */
	temp += (((int64)B0 * (int64)IN)     >> SFRB0); /* y = b1.u(k-1) + b0.u(k) */

	temp -= (((int64)A1 * (int64)OUT)    >> SFRA1); /* y = b0.u(k-1) + b1.u(k) - a0.y(k-1) */

	/* check for overflow */
    LIMIT(temp, INT32_MAX);

	/* save values for next update call and assign output */
	IN_OLD = IN;
	OUT    = (int32)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Bilin_FiP32_Init(BILIN_FIP32 *pTBilin_FiP32)
{
    pTBilin_FiP32->ID = BILIN_FIP32_ID;
    pTBilin_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* reset old input value */
    IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_FiP32_Load(const BILIN_FIP32 *pTBilin_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)15 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTBilin_FiP32->b0 & 0x000000FF);
        data[1] = (uint8)((pTBilin_FiP32->b0 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTBilin_FiP32->b0 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTBilin_FiP32->b0 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTBilin_FiP32->b1 & 0x000000FF);
        data[5] = (uint8)((pTBilin_FiP32->b1 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTBilin_FiP32->b1 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTBilin_FiP32->b1 >> 24) & 0x000000FF);
        data[8] = (uint8)(pTBilin_FiP32->a1 & 0x000000FF);
        data[9] = (uint8)((pTBilin_FiP32->a1 >> 8) & 0x000000FF);
        data[10] = (uint8)((pTBilin_FiP32->a1 >> 16) & 0x000000FF);
        data[11] = (uint8)((pTBilin_FiP32->a1 >> 24) & 0x000000FF);
        data[12] = (uint8)pTBilin_FiP32->sfrb0;
        data[13] = (uint8)pTBilin_FiP32->sfrb1;
        data[14] = (uint8)pTBilin_FiP32->sfra1;
        *dataLength = (uint16)15;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_FiP32_Save(BILIN_FIP32 *pTBilin_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)15)
    {
        error = (uint8)1;
    }
    else
    {
        pTBilin_FiP32->b0 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTBilin_FiP32->b1 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTBilin_FiP32->a1 = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTBilin_FiP32->sfrb0 = UINT8_TO_INT8((uint8)data[12]);
        pTBilin_FiP32->sfrb1 = UINT8_TO_INT8((uint8)data[13]);
        pTBilin_FiP32->sfra1 = UINT8_TO_INT8((uint8)data[14]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BILIN_FIP32_ISLINKED)
void* Bilin_FiP32_GetAddress(const BILIN_FIP32* block, uint16 elementId)
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
