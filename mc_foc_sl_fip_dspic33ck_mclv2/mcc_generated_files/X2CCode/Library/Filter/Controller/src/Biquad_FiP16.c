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
#include "Biquad_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Biquad_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTBiquad_FiP16->In)		    /* Q15 */

/* Outputs */
#define OUT			(pTBiquad_FiP16->Out)		    /* Q15 */

/* Parameter */
#define	A1 			(pTBiquad_FiP16->a1)		    /* Qa1 */
#define	A2 			(pTBiquad_FiP16->a2)		    /* Qa2 */
#define	B0			(pTBiquad_FiP16->b0)		    /* Qb0 */
#define	B1			(pTBiquad_FiP16->b1)		    /* Qb1 */
#define	B2 			(pTBiquad_FiP16->b2)		    /* Qb2 */
#define SFRA1		(pTBiquad_FiP16->sfra1)		    /* a1 */
#define SFRA2       (pTBiquad_FiP16->sfra2)         /* a2 */
#define SFRB0		(pTBiquad_FiP16->sfrb0)		    /* b0 */
#define SFRB1       (pTBiquad_FiP16->sfrb1)         /* b1 */
#define SFRB2       (pTBiquad_FiP16->sfrb2)         /* b2 */

/* Variables */
#define IN_OLD		(pTBiquad_FiP16->in_old)	    /* Q15 */
#define IN_VERYOLD	(pTBiquad_FiP16->in_veryold)	/* Q15 */
#define OUT_OLD		(pTBiquad_FiP16->out_old)	    /* Q15 */
#define OUT_VERYOLD (pTBiquad_FiP16->out_veryold)   /* Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Biquad_FiP16_Update(BIQUAD_FIP16 *pTBiquad_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp;

	temp  =  ((int32)B2 * (int32)IN_VERYOLD)  >> SFRB2;	    /* y(k) = b2.u(k-2) */
	temp += (((int32)B1 * (int32)IN_OLD)      >> SFRB1);	/* y(k) = b2.u(k-2) + b1.u(k-1) */
	temp += (((int32)B0 * (int32)IN)          >> SFRB0);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) */

	temp -= (((int32)A2 * (int32)OUT_VERYOLD) >> SFRA2);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) */
	temp -= (((int32)A1 * (int32)OUT_OLD)     >> SFRA1);    /* y(k) = b2.u(k-2) + b1.u(k-1) + b0.u(k) - a2.y(k-2) - a1.y(k-1) */

	/* check for overflow */
	LIMIT(temp, INT16_MAX);

	/* assign output and set values for next update call */
    OUT         = (int16)temp;
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = OUT;
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Biquad_FiP16_Init(BIQUAD_FIP16 *pTBiquad_FiP16)
{
    pTBiquad_FiP16->ID = BIQUAD_FIP16_ID;
    pTBiquad_FiP16->Out = 0;
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
uint8 Biquad_FiP16_Load(const BIQUAD_FIP16 *pTBiquad_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)15 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTBiquad_FiP16->b0 & 0x00FF);
        data[1] = (uint8)((pTBiquad_FiP16->b0 >> 8) & 0x00FF);
        data[2] = (uint8)(pTBiquad_FiP16->b1 & 0x00FF);
        data[3] = (uint8)((pTBiquad_FiP16->b1 >> 8) & 0x00FF);
        data[4] = (uint8)(pTBiquad_FiP16->b2 & 0x00FF);
        data[5] = (uint8)((pTBiquad_FiP16->b2 >> 8) & 0x00FF);
        data[6] = (uint8)(pTBiquad_FiP16->a1 & 0x00FF);
        data[7] = (uint8)((pTBiquad_FiP16->a1 >> 8) & 0x00FF);
        data[8] = (uint8)(pTBiquad_FiP16->a2 & 0x00FF);
        data[9] = (uint8)((pTBiquad_FiP16->a2 >> 8) & 0x00FF);
        data[10] = (uint8)pTBiquad_FiP16->sfrb0;
        data[11] = (uint8)pTBiquad_FiP16->sfrb1;
        data[12] = (uint8)pTBiquad_FiP16->sfrb2;
        data[13] = (uint8)pTBiquad_FiP16->sfra1;
        data[14] = (uint8)pTBiquad_FiP16->sfra2;
        *dataLength = (uint16)15;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Biquad_FiP16_Save(BIQUAD_FIP16 *pTBiquad_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)15)
    {
        error = (uint8)1;
    }
    else
    {
        pTBiquad_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTBiquad_FiP16->b1 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTBiquad_FiP16->b2 = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTBiquad_FiP16->a1 = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTBiquad_FiP16->a2 = UINT16_TO_INT16((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTBiquad_FiP16->sfrb0 = UINT8_TO_INT8((uint8)data[10]);
        pTBiquad_FiP16->sfrb1 = UINT8_TO_INT8((uint8)data[11]);
        pTBiquad_FiP16->sfrb2 = UINT8_TO_INT8((uint8)data[12]);
        pTBiquad_FiP16->sfra1 = UINT8_TO_INT8((uint8)data[13]);
        pTBiquad_FiP16->sfra2 = UINT8_TO_INT8((uint8)data[14]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BIQUAD_FIP16_ISLINKED)
void* Biquad_FiP16_GetAddress(const BIQUAD_FIP16* block, uint16 elementId)
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
