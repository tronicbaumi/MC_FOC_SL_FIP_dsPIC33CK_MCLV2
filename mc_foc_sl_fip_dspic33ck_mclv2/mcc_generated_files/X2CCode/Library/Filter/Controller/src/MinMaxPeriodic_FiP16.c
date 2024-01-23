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
#include "MinMaxPeriodic_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(MinMaxPeriodic_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTMinMaxPeriodic_FiP16->In)
#define PHI			(*pTMinMaxPeriodic_FiP16->phi)

/* Outputs */
#define MIN 		(pTMinMaxPeriodic_FiP16->min)
#define MAX 		(pTMinMaxPeriodic_FiP16->max)

/* Variables */
#define MIN_ACT		(pTMinMaxPeriodic_FiP16->min_act)
#define MAX_ACT		(pTMinMaxPeriodic_FiP16->max_act)
#define PHI_OLD		(pTMinMaxPeriodic_FiP16->phi_old)

/* Constants */
#define MORE_THAN_PI    ((int32)0xC000)     /* 3/2 * pi */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP16_Update(MINMAXPERIODIC_FIP16 *pTMinMaxPeriodic_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 diff;

	/* check for new period */
	diff = (int32)PHI - (int32)PHI_OLD;
	if (getAbsValI32(diff) > MORE_THAN_PI)
	{
		/* update outputs */
		MIN = MIN_ACT;
		MAX = MAX_ACT;

		/* reset current minimum and maximum */
		MIN_ACT = INT16_MAX;
		MAX_ACT = -INT16_MAX;
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
void MinMaxPeriodic_FiP16_Init(MINMAXPERIODIC_FIP16 *pTMinMaxPeriodic_FiP16)
{
    pTMinMaxPeriodic_FiP16->ID = MINMAXPERIODIC_FIP16_ID;
    pTMinMaxPeriodic_FiP16->max = 0;
    pTMinMaxPeriodic_FiP16->min = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset variables */
	MIN_ACT = INT16_MAX;
	MAX_ACT = -INT16_MAX;
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
#if !defined(MINMAXPERIODIC_FIP16_ISLINKED)
void* MinMaxPeriodic_FiP16_GetAddress(const MINMAXPERIODIC_FIP16* block, uint16 elementId)
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
