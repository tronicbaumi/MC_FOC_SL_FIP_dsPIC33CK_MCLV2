/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * Copyright (c) 2017, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1975 $
 * $LastChangedDate:: 2020-07-20 16:25:13 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONVFNC_MANUALSWITCH_BOOL_H
#define CONVFNC_MANUALSWITCH_BOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "ManualSwitch_Bool.h"

/** Mask parameter data structure */
typedef struct {
    float64 Toggle;
} MANUALSWITCH_BOOL_MASK_PARAM;

/* public prototypes */
uint8 ManualSwitch_Bool_LoadMP(const MANUALSWITCH_BOOL_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 ManualSwitch_Bool_SaveMP(MANUALSWITCH_BOOL *block, MANUALSWITCH_BOOL_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);
uint8 ManualSwitch_Bool_InitMP(MANUALSWITCH_BOOL *block, const MANUALSWITCH_BOOL_MASK_PARAM *maskParam);
uint8 ManualSwitch_Bool_ConvertMP(MANUALSWITCH_BOOL *block, MANUALSWITCH_BOOL_MASK_PARAM *maskParam);
void ManualSwitch_Bool_BackupMP(MANUALSWITCH_BOOL_MASK_PARAM *maskParam);
void ManualSwitch_Bool_RestoreMP(MANUALSWITCH_BOOL_MASK_PARAM *maskParam);

#ifdef __cplusplus
}
#endif

#endif
