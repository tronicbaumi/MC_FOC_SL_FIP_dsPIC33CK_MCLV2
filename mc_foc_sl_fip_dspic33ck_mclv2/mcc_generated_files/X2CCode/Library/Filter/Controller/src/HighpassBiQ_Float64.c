/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2159 $
 * $LastChangedDate:: 2021-03-22 17:32:11 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "HighpassBiQ_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HighpassBiQ_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

/* Links                                                                                                              */
#define BIQUAD_FLOAT64_ID HIGHPASSBIQ_FLOAT64_ID
#define BIQUAD_FLOAT64 HIGHPASSBIQ_FLOAT64
#define Biquad_Float64_Update HighpassBiQ_Float64_Update
#define Biquad_Float64_Init HighpassBiQ_Float64_Init
#define Biquad_Float64_Load HighpassBiQ_Float64_Load
#define Biquad_Float64_Save HighpassBiQ_Float64_Save
#define BIQUAD_FLOAT64_ISLINKED
#include "Biquad_Float64.c"

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HIGHPASSBIQ_FLOAT64_ISLINKED)
void* HighpassBiQ_Float64_GetAddress(const HIGHPASSBIQ_FLOAT64* block, uint16 elementId)
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
