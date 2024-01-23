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
#include "MinMaxPeriodic_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(MinMaxPeriodic_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTMinMaxPeriodic_Float32->In)
#define PHI			(*pTMinMaxPeriodic_Float32->phi)

/* Outputs */
#define MIN 		(pTMinMaxPeriodic_Float32->min)
#define MAX 		(pTMinMaxPeriodic_Float32->max)

/* Variables */
#define MIN_ACT		(pTMinMaxPeriodic_Float32->min_act)
#define MAX_ACT		(pTMinMaxPeriodic_Float32->max_act)
#define PHI_OLD		(pTMinMaxPeriodic_Float32->phi_old)

/* Constants */
#define REAL32_MAX	((float32)3.40282347e+38)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void MinMaxPeriodic_Float32_Update(MINMAXPERIODIC_FLOAT32 *pTMinMaxPeriodic_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 diff;

	/* check for new period */
	diff = PHI - PHI_OLD;
	if (getAbsValR32(diff) > PI_R32)
	{
		/* update outputs */
		MIN = MIN_ACT;
		MAX = MAX_ACT;

		/* reset current minimum and maximum */
		MIN_ACT = REAL32_MAX;
		MAX_ACT = -REAL32_MAX;
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
void MinMaxPeriodic_Float32_Init(MINMAXPERIODIC_FLOAT32 *pTMinMaxPeriodic_Float32)
{
    pTMinMaxPeriodic_Float32->ID = MINMAXPERIODIC_FLOAT32_ID;
    pTMinMaxPeriodic_Float32->max = 0;
    pTMinMaxPeriodic_Float32->min = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
	/* reset variables */
	MIN_ACT = REAL32_MAX;
	MAX_ACT = -REAL32_MAX;
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
#if !defined(MINMAXPERIODIC_FLOAT32_ISLINKED)
void* MinMaxPeriodic_Float32_GetAddress(const MINMAXPERIODIC_FLOAT32* block, uint16 elementId)
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
