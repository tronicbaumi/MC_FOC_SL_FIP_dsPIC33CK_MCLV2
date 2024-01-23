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
/* Description: Calculation of fundamental wave.                              */
/* USERCODE-END:Description                                                                                           */
#include "FundFreq_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(FundFreq_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>
#include "Sin_Data.h"

/* Inputs */
#define IN 				(*pTFundFreq_Float64->In)
#define PHI				(*pTFundFreq_Float64->phi)

/* Outputs */
#define OUT				(pTFundFreq_Float64->Out)

/* Variables */
#define PHI_OLD			(pTFundFreq_Float64->phi_old)
#define CNT		    	(pTFundFreq_Float64->cnt)
#define SUM_A	    	(pTFundFreq_Float64->sum_a)
#define SUM_B	    	(pTFundFreq_Float64->sum_b)
#define A1	    		(pTFundFreq_Float64->a)
#define B1	    		(pTFundFreq_Float64->b)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void FundFreq_Float64_Update(FUNDFREQ_FLOAT64 *pTFundFreq_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp, sine, cosine;

	sine   = sin(PHI);
	cosine = cos(PHI);

    /* check for start of new period (jump from -pi to +pi or vice versa) */
    if ((ABS_R64(PHI - PHI_OLD)) > PI_R64)
    {
        /* calculate coefficients */
        A1 = (SUM_A / (float64)CNT) * 2.0;
        B1 = (SUM_B / (float64)CNT) * 2.0;

        /* reset counter and sum */
        CNT = 0;
        SUM_A = 0;
        SUM_B = 0;
    }

	/* check for counter limit */
	if (CNT != UINT64_MAX)
	{
		/* counter value hasn't reached its maximum value:
		 * it's save to compute sum and to increase counter
		 */
		SUM_A += (IN * cosine);
		SUM_B += (IN * sine);
		CNT++;
	}
	else
	{
		/* counter value has reached its maximum value:
		 * reset sum to prevent false output on next jump of phi
		 */
		SUM_A = 0;
		SUM_B = 0;
	}

	/* calculate first harmonic */
	temp  =  A1 * cosine;
	temp += (B1 * sine);
	OUT   = temp;

	/* save angle value for next cycle */
	PHI_OLD = PHI;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void FundFreq_Float64_Init(FUNDFREQ_FLOAT64 *pTFundFreq_Float64)
{
    pTFundFreq_Float64->ID = FUNDFREQ_FLOAT64_ID;
    pTFundFreq_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     PHI_OLD = 0;
     CNT = 0;
     SUM_A = 0;
     SUM_B = 0;
     A1 = 0;
     B1 = 0;

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
#if !defined(FUNDFREQ_FLOAT64_ISLINKED)
void* FundFreq_Float64_GetAddress(const FUNDFREQ_FLOAT64* block, uint16 elementId)
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
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
