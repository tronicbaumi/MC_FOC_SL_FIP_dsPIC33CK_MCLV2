/**
 * @file
 * @brief Load, save and conversion function for mask parameter.
 * 
 * Loading of mask parameter from target, saving of mask parameter on target and conversion of mask parameter to implementation parameter.
 */
/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
#ifndef CONVFNC_FUNDFREQ_FIP16_H
#define CONVFNC_FUNDFREQ_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"
#include "FundFreq_FiP16.h"

/** Mask parameter data structure */
typedef struct {
    float64 ts_fact;
} FUNDFREQ_FIP16_MASK_PARAM;

/* public prototypes */
uint8 FundFreq_FiP16_LoadMP(const FUNDFREQ_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize);
uint8 FundFreq_FiP16_SaveMP(FUNDFREQ_FIP16 *block, FUNDFREQ_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen);

#ifdef __cplusplus
}
#endif

#endif
