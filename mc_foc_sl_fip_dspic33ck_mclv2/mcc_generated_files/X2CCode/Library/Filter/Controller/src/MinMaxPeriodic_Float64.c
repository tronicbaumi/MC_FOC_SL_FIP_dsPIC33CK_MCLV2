/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1897 $
 * $LastChangedDate:: 2020-04-29 17:57:28 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "MinMaxPeriodic_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(MinMaxPeriodic_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTMinMaxPeriodic_Float64->In)
#define PHI			(*pTMinMaxPeriodic_Float64->phi)

/* Outputs */
#define MIN 		(pTMinMaxPeriodic_Float64->min)
#define MAX 		(pTMinMaxPeriodic_Float64->max)

/* Variables */
#define MIN_ACT		(pTMinMaxPeriodic_Float64->min_act)
#define MAX_ACT		(pTMinMaxPeriodic_Float64->max_act)
#define PHI_OLD		(pTMinMaxPeriodic_Float64->phi_old)

/* Constants */
#if defined(__C2000__) || defined(__GENERIC_TI_C28X__)
	/* C28xx series does not support double value range! */
	#define REAL64_MAX	((float64)3.40282347e+38)
#else
	#define REAL64_MAX	((float64)1.79769313486231571e+308)
#endif

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void MinMaxPeriodic_Float64_Update(MINMAXPERIODIC_FLOAT64 *pTMinMaxPeriodic_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 diff;

	/* check for new period */
	diff = PHI - PHI_OLD;
	if (getAbsValR64(diff) > PI_R64)
	{
		/* update outputs */
		MIN = MIN_ACT;
		MAX = MAX_ACT;

		/* reset current minimum and maximum */
		MIN_ACT = REAL64_MAX;
		MAX_ACT = -REAL64_MAX;
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
void MinMaxPeriodic_Float64_Init(MINMAXPERIODIC_FLOAT64 *pTMinMaxPeriodic_Float64)
{
    pTMinMaxPeriodic_Float64->ID = MINMAXPERIODIC_FLOAT64_ID;
    pTMinMaxPeriodic_Float64->max = 0;
    pTMinMaxPeriodic_Float64->min = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	/* reset variables */
 	MIN_ACT = REAL64_MAX;
 	MAX_ACT = -REAL64_MAX;
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
#if !defined(MINMAXPERIODIC_FLOAT64_ISLINKED)
void* MinMaxPeriodic_Float64_GetAddress(const MINMAXPERIODIC_FLOAT64* block, uint16 elementId)
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
