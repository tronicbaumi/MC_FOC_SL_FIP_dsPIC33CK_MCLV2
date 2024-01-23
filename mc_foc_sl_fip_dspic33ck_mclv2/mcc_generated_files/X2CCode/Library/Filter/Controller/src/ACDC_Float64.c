/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1897 $
 * $LastChangedDate:: 2020-04-29 17:57:28 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: Calculation of AC and DC component.                           */
/* USERCODE-END:Description                                                                                           */
#include "ACDC_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(ACDC_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTACDC_Float64->In)
#define PHI				(*pTACDC_Float64->phi)

/* Outputs */
#define OUT_AC 			(pTACDC_Float64->AC)
#define OUT_DC 			(pTACDC_Float64->DC)

/* Variables */
#define PHI_OLD			(pTACDC_Float64->phi_old)
#define CNT		    	(pTACDC_Float64->cnt)
#define SUM		    	(pTACDC_Float64->sum)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void ACDC_Float64_Update(ACDC_FLOAT64 *pTACDC_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	/* check for counter limit */
	if (CNT != UINT64_MAX)
	{
		/* counter value hasn't reached its maximum value:
		 * it's save to compute sum and to increase counter
		 */
		SUM += IN;
		CNT++;
	}
	else
	{
		/* counter value has reached its maximum value:
		 * reset sum to prevent false output on next jump of phi
		 */
		SUM = 0;
	}

	/* check for start of new period (jump from -pi to +pi or vice versa) */
	if ((ABS_R64(PHI - PHI_OLD)) > PI_R64)
	{
		/* calculate DC part */
		OUT_DC = SUM / (float64)CNT;

		/* reset counter and sum */
		SUM = 0;
		CNT = 0;
	}

	/* calculate AC part */
	OUT_AC = IN - OUT_DC;

	/* save angle value for next cycle */
	PHI_OLD = PHI;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void ACDC_Float64_Init(ACDC_FLOAT64 *pTACDC_Float64)
{
    pTACDC_Float64->ID = ACDC_FLOAT64_ID;
    pTACDC_Float64->AC = 0;
    pTACDC_Float64->DC = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     PHI_OLD = 0;
     CNT = 0;
     SUM = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** No Load function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** No Save function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ACDC_FLOAT64_ISLINKED)
void* ACDC_Float64_GetAddress(const ACDC_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->phi;
            break;
        case 3:
            addr = (void*)&block->AC;
            break;
        case 4:
            addr = (void*)&block->DC;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
