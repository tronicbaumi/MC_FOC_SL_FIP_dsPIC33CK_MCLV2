/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
 * $LastChangedDate:: 2021-03-16 17:27:31 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: Calculation of AC and DC component.                           */
/* USERCODE-END:Description                                                                                           */
#include "ACDC_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(ACDC_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTACDC_FiP16->In)
#define PHI				(*pTACDC_FiP16->phi)

/* Outputs */
#define OUT_AC 			(pTACDC_FiP16->AC)
#define OUT_DC 			(pTACDC_FiP16->DC)

/* Variables */
#define PHI_OLD			(pTACDC_FiP16->phi_old)
#define CNT		    	(pTACDC_FiP16->cnt)
#define SUM		    	(pTACDC_FiP16->sum)

/* Constants */
#define MORE_THAN_PI    ((int32)0xC000)     /* 3/2 * pi */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void ACDC_FiP16_Update(ACDC_FIP16 *pTACDC_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp;

	/* check for counter limit */
	if (CNT != UINT16_MAX)
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
	if ((ABS_I32((int32)PHI - (int32)PHI_OLD)) > MORE_THAN_PI)
	{
		/* calculate DC part */
		temp = SUM / CNT;
		LIMIT(temp, INT16_MAX);
		OUT_DC = (int16)temp;

		/* reset counter and sum */
		SUM = 0;
		CNT = 0;
	}

	/* calculate AC part */
	temp = (int32)IN - (int32)OUT_DC;
	LIMIT(temp, INT16_MAX);
	OUT_AC = (int16)temp;

	/* save angle value for next cycle */
	PHI_OLD = PHI;


/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void ACDC_FiP16_Init(ACDC_FIP16 *pTACDC_FiP16)
{
    pTACDC_FiP16->ID = ACDC_FIP16_ID;
    pTACDC_FiP16->AC = 0;
    pTACDC_FiP16->DC = 0;
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
#if !defined(ACDC_FIP16_ISLINKED)
void* ACDC_FiP16_GetAddress(const ACDC_FIP16* block, uint16 elementId)
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
