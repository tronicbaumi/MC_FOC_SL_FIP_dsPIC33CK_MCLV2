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
#include "BandpassBiQ_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(BandpassBiQ_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

/* Links                                                                                                              */
#define BIQUAD_FIP16_ID BANDPASSBIQ_FIP16_ID
#define BIQUAD_FIP16 BANDPASSBIQ_FIP16
#define Biquad_FiP16_Update BandpassBiQ_FiP16_Update
#define Biquad_FiP16_Init BandpassBiQ_FiP16_Init
#define Biquad_FiP16_Load BandpassBiQ_FiP16_Load
#define Biquad_FiP16_Save BandpassBiQ_FiP16_Save
#define BIQUAD_FIP16_ISLINKED
#include "Biquad_FiP16.c"

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(BANDPASSBIQ_FIP16_ISLINKED)
void* BandpassBiQ_FiP16_GetAddress(const BANDPASSBIQ_FIP16* block, uint16 elementId)
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
