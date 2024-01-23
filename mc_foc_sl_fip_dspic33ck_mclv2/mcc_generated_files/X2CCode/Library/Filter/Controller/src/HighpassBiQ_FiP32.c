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
#include "HighpassBiQ_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(HighpassBiQ_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

/* Links                                                                                                              */
#define BIQUAD_FIP32_ID HIGHPASSBIQ_FIP32_ID
#define BIQUAD_FIP32 HIGHPASSBIQ_FIP32
#define Biquad_FiP32_Update HighpassBiQ_FiP32_Update
#define Biquad_FiP32_Init HighpassBiQ_FiP32_Init
#define Biquad_FiP32_Load HighpassBiQ_FiP32_Load
#define Biquad_FiP32_Save HighpassBiQ_FiP32_Save
#define BIQUAD_FIP32_ISLINKED
#include "Biquad_FiP32.c"

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(HIGHPASSBIQ_FIP32_ISLINKED)
void* HighpassBiQ_FiP32_GetAddress(const HIGHPASSBIQ_FIP32* block, uint16 elementId)
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
