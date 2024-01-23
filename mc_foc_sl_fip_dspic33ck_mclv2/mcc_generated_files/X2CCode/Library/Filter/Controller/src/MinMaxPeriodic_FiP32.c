/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2153 $
 * $LastChangedDate:: 2021-03-16 17:27:31 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "MinMaxPeriodic_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(MinMaxPeriodic_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTMinMaxPeriodic_FiP32->In)
#define PHI			(*pTMinMaxPeriodic_FiP32->phi)

/* Outputs */
#define MIN 		(pTMinMaxPeriodic_FiP32->min)
#define MAX 		(pTMinMaxPeriodic_FiP32->max)

/* Variables */
#define MIN_ACT		(pTMinMaxPeriodic_FiP32->min_act)
#define MAX_ACT		(pTMinMaxPeriodic_FiP32->max_act)
#define PHI_OLD		(pTMinMaxPeriodic_FiP32->phi_old)

/* Constants */
#define MORE_THAN_PI    ((int64)0xC0000000)     /* 3/2 * pi */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP32_Update(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 diff;

	/* check for new period */
	diff = (int64)PHI - (int64)PHI_OLD;
	if (getAbsValI64(diff) > MORE_THAN_PI)
	{
		/* update outputs */
		MIN = MIN_ACT;
		MAX = MAX_ACT;

		/* reset current minimum and maximum */
		MIN_ACT = INT32_MAX;
		MAX_ACT = -INT32_MAX;
	}
	else
	{
		/* check for new minimum */
		if (IN < MIN_ACT)
		{
			MIN_ACT = IN;
		}

		/* check for new maximum */
		if (IN > MAX_ACT)
		{
			MAX_ACT = IN;
		}
	}

	/* save angle for next cycle */
	PHI_OLD = PHI;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP32_Init(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32)
{
    pTMinMaxPeriodic_FiP32->ID = MINMAXPERIODIC_FIP32_ID;
    pTMinMaxPeriodic_FiP32->max = 0;
    pTMinMaxPeriodic_FiP32->min = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset variables */
	MIN_ACT = INT32_MAX;
	MAX_ACT = -INT32_MAX;
    PHI_OLD = 0;

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
#if !defined(MINMAXPERIODIC_FIP32_ISLINKED)
void* MinMaxPeriodic_FiP32_GetAddress(const MINMAXPERIODIC_FIP32* block, uint16 elementId)
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
            addr = (void*)&block->max;
            break;
        case 4:
            addr = (void*)&block->min;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
