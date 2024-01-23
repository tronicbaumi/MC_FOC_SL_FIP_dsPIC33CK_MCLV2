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
#include "Bilin_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Bilin_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBilin_FiP16->In)		/* Q15 */

/* Outputs */
#define OUT			(pTBilin_FiP16->Out)		/* Q15 */

/* Parameter */
#define	A1 			(pTBilin_FiP16->a1)		    /* Qa1 */
#define	B0			(pTBilin_FiP16->b0)		    /* Qb0 */
#define	B1			(pTBilin_FiP16->b1)		    /* Qb1 */
#define SFRA1		(pTBilin_FiP16->sfra1)		/* a1 */
#define SFRB0		(pTBilin_FiP16->sfrb0)		/* b0 */
#define SFRB1       (pTBilin_FiP16->sfrb1)      /* b1 */

/* Variables */
#define IN_OLD		(pTBilin_FiP16->in_old)	    /* Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Bilin_FiP16_Update(BILIN_FIP16 *pTBilin_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp;

    /* do the filtering */
	temp  =  ((int32)B1 * (int32)IN_OLD) >> SFRB1;	/* y = b1.u(k-1) */
	temp += (((int32)B0 * (int32)IN)     >> SFRB0); /* y = b1.u(k-1) + b0.u(k) */

	temp -= (((int32)A1 * (int32)OUT)    >> SFRA1); /* y = b0.u(k-1) + b1.u(k) - a0.y(k-1) */

	/* check for overflow */
    LIMIT(temp, INT16_MAX);

	/* save values for next update call and assign output */
	IN_OLD = IN;
	OUT    = (int16)temp;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Bilin_FiP16_Init(BILIN_FIP16 *pTBilin_FiP16)
{
    pTBilin_FiP16->ID = BILIN_FIP16_ID;
    pTBilin_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* reset old input value */
    IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_FiP16_Load(const BILIN_FIP16 *pTBilin_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)9 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTBilin_FiP16->b0 & 0x00FF);
        data[1] = (uint8)((pTBilin_FiP16->b0 >> 8) & 0x00FF);
        data[2] = (uint8)(pTBilin_FiP16->b1 & 0x00FF);
        data[3] = (uint8)((pTBilin_FiP16->b1 >> 8) & 0x00FF);
        data[4] = (uint8)(pTBilin_FiP16->a1 & 0x00FF);
        data[5] = (uint8)((pTBilin_FiP16->a1 >> 8) & 0x00FF);
        data[6] = (uint8)pTBilin_FiP16->sfrb0;
        data[7] = (uint8)pTBilin_FiP16->sfrb1;
        data[8] = (uint8)pTBilin_FiP16->sfra1;
        *dataLength = (uint16)9;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Bilin_FiP16_Save(BILIN_FIP16 *pTBilin_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)9)
    {
        error = (uint8)1;
    }
    else
    {
        pTBilin_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTBilin_FiP16->b1 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTBilin_FiP16->a1 = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTBilin_FiP16->sfrb0 = UINT8_TO_INT8((uint8)data[6]);
        pTBilin_FiP16->sfrb1 = UINT8_TO_INT8((uint8)data[7]);
        pTBilin_FiP16->sfra1 = UINT8_TO_INT8((uint8)data[8]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BILIN_FIP16_ISLINKED)
void* Bilin_FiP16_GetAddress(const BILIN_FIP16* block, uint16 elementId)
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
