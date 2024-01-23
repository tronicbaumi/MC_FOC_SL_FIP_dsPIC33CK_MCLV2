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
#include "BandpassBiQ_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(BandpassBiQ_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

/* Links                                                                                                              */
#define BIQUAD_FLOAT32_ID BANDPASSBIQ_FLOAT32_ID
#define BIQUAD_FLOAT32 BANDPASSBIQ_FLOAT32
#define Biquad_Float32_Update BandpassBiQ_Float32_Update
#define Biquad_Float32_Init BandpassBiQ_Float32_Init
#define Biquad_Float32_Load BandpassBiQ_Float32_Load
#define Biquad_Float32_Save BandpassBiQ_Float32_Save
#define BIQUAD_FLOAT32_ISLINKED
#include "Biquad_Float32.c"

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BANDPASSBIQ_FLOAT32_ISLINKED)
void* BandpassBiQ_Float32_GetAddress(const BANDPASSBIQ_FLOAT32* block, uint16 elementId)
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
