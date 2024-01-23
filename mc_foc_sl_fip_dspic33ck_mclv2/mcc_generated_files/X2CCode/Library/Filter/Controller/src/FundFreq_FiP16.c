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
#include "FundFreq_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(FundFreq_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Inputs */
#define IN 				(*pTFundFreq_FiP16->In)
#define PHI				(*pTFundFreq_FiP16->phi)

/* Outputs */
#define OUT				(pTFundFreq_FiP16->Out)

/* Variables */
#define PHI_OLD			(pTFundFreq_FiP16->phi_old)
#define CNT		    	(pTFundFreq_FiP16->cnt)
#define SUM_A	    	(pTFundFreq_FiP16->sum_a)
#define SUM_B	    	(pTFundFreq_FiP16->sum_b)
#define A1	    		(pTFundFreq_FiP16->a)
#define B1	    		(pTFundFreq_FiP16->b)

/* Constants */
#define HALFPI			0x4000				/* pi/2 [Q15] */
#define MORE_THAN_PI    ((int32)0xC000)     /* 3/2 * pi [Q15] */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void FundFreq_FiP16_Update(FUNDFREQ_FIP16 *pTFundFreq_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp;
	int16 sine, cosine;

	LOOKUP16(Sin_Table16, PHI, sine);
	LOOKUP16(Sin_Table16, (HALFPI-PHI), cosine);		/* cos(u) = sin(pi/2 - u) */

    /* check for start of new period (jump from -pi to +pi or vice versa) */
    if ((ABS_I32((int32)PHI - (int32)PHI_OLD)) > MORE_THAN_PI)
    {
        /* calculate coefficients */
        A1 = (SUM_A / CNT) << 1;
        LIMIT(A1, INT16_MAX);
        B1 = (SUM_B / CNT) << 1;
        LIMIT(B1, INT16_MAX);

        /* reset counter and sum */
        CNT = 0;
        SUM_A = 0;
        SUM_B = 0;
    }

	/* check for counter limit */
	if (CNT != UINT16_MAX)
	{
		/* counter value hasn't reached its maximum value:
		 * it's save to compute sum and to increase counter
		 */
		SUM_A += (((int32)IN * (int32)cosine) >> 15);
		SUM_B += (((int32)IN * (int32)sine) >> 15);
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
	temp  =  (int32)A1 * (int32)cosine;
	temp += ((int32)B1 * (int32)sine);
	temp = temp >> 15;
	LIMIT(temp, INT16_MAX);
	OUT = (int16)temp;

	/* save angle value for next cycle */
	PHI_OLD = PHI;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void FundFreq_FiP16_Init(FUNDFREQ_FIP16 *pTFundFreq_FiP16)
{
    pTFundFreq_FiP16->ID = FUNDFREQ_FIP16_ID;
    pTFundFreq_FiP16->Out = 0;
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
#if !defined(FUNDFREQ_FIP16_ISLINKED)
void* FundFreq_FiP16_GetAddress(const FUNDFREQ_FIP16* block, uint16 elementId)
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
