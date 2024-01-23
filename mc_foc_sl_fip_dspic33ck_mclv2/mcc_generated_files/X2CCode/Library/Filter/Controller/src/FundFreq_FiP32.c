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
#include "FundFreq_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(FundFreq_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Inputs */
#define IN 				(*pTFundFreq_FiP32->In)
#define PHI				(*pTFundFreq_FiP32->phi)

/* Outputs */
#define OUT				(pTFundFreq_FiP32->Out)

/* Variables */
#define PHI_OLD			(pTFundFreq_FiP32->phi_old)
#define CNT		    	(pTFundFreq_FiP32->cnt)
#define SUM_A	    	(pTFundFreq_FiP32->sum_a)
#define SUM_B	    	(pTFundFreq_FiP32->sum_b)
#define A1	    		(pTFundFreq_FiP32->a)
#define B1	    		(pTFundFreq_FiP32->b)

/* Constants */
#define HALFPI			0x40000000				/* pi/2	[Q31] */
#define MORE_THAN_PI    ((int64)0xC0000000)     /* 3/2 * pi [Q31] */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void FundFreq_FiP32_Update(FUNDFREQ_FIP32 *pTFundFreq_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 temp;
	int32 sine, cosine;

	LOOKUP32(Sin_Table32, PHI, sine);
	LOOKUP32(Sin_Table32, (HALFPI-PHI), cosine);		/* cos(u) = sin(pi/2 - u) */

    /* check for start of new period (jump from -pi to +pi or vice versa) */
    if ((ABS_I64((int64)PHI - (int64)PHI_OLD)) > MORE_THAN_PI)
    {
        /* calculate coefficients */
        A1 = (SUM_A / CNT) << 1;
        LIMIT(A1, INT32_MAX);
        B1 = (SUM_B / CNT) << 1;
        LIMIT(B1, INT32_MAX);

        /* reset counter and sum */
        CNT = 0;
        SUM_A = 0;
        SUM_B = 0;
    }

	/* check for counter limit */
	if (CNT != UINT32_MAX)
	{
		/* counter value hasn't reached its maximum value:
		 * it's save to compute sum and to increase counter
		 */
		SUM_A += (((int64)IN * (int64)cosine) >> 31);
		SUM_B += (((int64)IN * (int64)sine) >> 31);
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
	temp  =  (int64)A1 * (int64)cosine;
	temp += ((int64)B1 * (int64)sine);
	temp = temp >> 31;
	LIMIT(temp, INT32_MAX);
	OUT = (int32)temp;

	/* save angle value for next cycle */
	PHI_OLD = PHI;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void FundFreq_FiP32_Init(FUNDFREQ_FIP32 *pTFundFreq_FiP32)
{
    pTFundFreq_FiP32->ID = FUNDFREQ_FIP32_ID;
    pTFundFreq_FiP32->Out = 0;
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
#if !defined(FUNDFREQ_FIP32_ISLINKED)
void* FundFreq_FiP32_GetAddress(const FUNDFREQ_FIP32* block, uint16 elementId)
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
