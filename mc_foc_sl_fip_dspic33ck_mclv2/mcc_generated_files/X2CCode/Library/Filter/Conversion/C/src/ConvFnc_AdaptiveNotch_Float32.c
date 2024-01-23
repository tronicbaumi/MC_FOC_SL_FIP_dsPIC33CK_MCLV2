/*
 * ===== CONFIDENTIAL =====
 * The content of this file is confidential according to the X2C Licence Terms and Conditions.
 *  
 * Copyright (c) 2019, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2112 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_AdaptiveNotch_Float32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    float32 a_fact;
    float32 b_fact;
    float32 c_fact;
    float32 n_thresh;
} ADAPTIVENOTCH_FLOAT32_IMPL_PARAM;

/** method enumeration */
typedef enum {
    METHOD_MATCHED_ZMTRANSFORM = 0
} tmethod;

/** Private prototypes */
static uint8 convertM2I(const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, ADAPTIVENOTCH_FLOAT32_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, ADAPTIVENOTCH_FLOAT32_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    /* get mask parameter values */
    float_CoT n_thresh = maskParam->n_thresh;   /* speed threshold */
    float_CoT p = maskParam->p;                 /* number of pole pairs */
    float_CoT Q = maskParam->Q;                 /* Q-factor */

    /* validation */
    if (p < 1) {
        error += 1; /* Number of pole pairs must not be smaller than one! */
    }
    if (n_thresh <= 0) {
        error += 2; /* Speed threshold must be greater than zero! */
    }
    if (Q < 0.5) {
        error += 4; /* Q-factor must not be smaller than 0.5! (to prevent complex multiplication factors) */
    }

    /* calculate multiplication factors for filter coefficients */
    if (error == 0)
    {    
        float_CoT a_fact = ((((-2 * (float_CoT)PI_R64) / 60) * p) / 2 / Q) * ts;
        float_CoT b_fact = ((((-2 * (float_CoT)PI_R64) / 60) * p) / 2 / Q) * ts * sqrt((4 * Q * Q) - 1);
        float_CoT c_fact = ((2 * (float_CoT)PI_R64) / 60) * p * ts;

        /* set implementation parameter values */
        impParam->n_thresh = n_thresh;
        impParam->a_fact = a_fact;
        impParam->b_fact = b_fact;
        impParam->c_fact = c_fact;
    }
/* USERCODE-END:Conversion                                                                                            */
    return (error);
}

/**
 * @brief Load block mask parameter data.
 *
 * @param[in] maskParam Mask parameter data structure
 * @param[out] data Data
 * @param[out] dataLen Data length
 * @param[in] maxSize Maximum Service data length
 *
 * @return Error: zero on success, not zero in case of load- or conversion error
 */
uint8 AdaptiveNotch_Float32_LoadMP(const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)41 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->Q)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->Q) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->Q) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->Q) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->Q) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->Q) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->Q) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->Q) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->n_thresh)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->n_thresh) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->n_max)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->n_max) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->n_max) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->n_max) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->n_max) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->n_max) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->n_max) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->n_max) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->p)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->p) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->p) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->p) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->p) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->p) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->p) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->p) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)(maskParam->method);
        *dataLen = (uint16)41;
    }
    return (error);
}

/**
 * @brief Save block mask parameter data.
 *
 * @param[in] block Pointer to block structure
 * @param[out] maskParam Mask parameter data structure
 * @param[in] data Data
 * @param dataLen Length of mask parameter data stream
 *
 * @return Error: zero on success, not zero in case of save- or conversion error
 */
uint8 AdaptiveNotch_Float32_SaveMP(ADAPTIVENOTCH_FLOAT32 *block, ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)41)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        AdaptiveNotch_Float32_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->Q = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->n_thresh = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->n_max = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        maskParam->p = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);
        maskParam->method = data[40];

        error = AdaptiveNotch_Float32_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            AdaptiveNotch_Float32_RestoreMP(maskParam);
        }

    }
    return (error);
}

/**
 * @brief Initializes Implementation parameters from Mask parameters.
 *
 * @param[out] block Block
 * @param[in] maskParam Mask parameters
 *
 * @return Error: zero on success, not zero in case of initialization error
 */
uint8 AdaptiveNotch_Float32_InitMP(ADAPTIVENOTCH_FLOAT32 *block, const ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    ADAPTIVENOTCH_FLOAT32_IMPL_PARAM *implParam = (ADAPTIVENOTCH_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint32*)&(implParam->a_fact)) & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint32*)&(implParam->a_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint32*)&(implParam->a_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint32*)&(implParam->a_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint32*)&(implParam->b_fact)) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint32*)&(implParam->b_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint32*)&(implParam->b_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint32*)&(implParam->b_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint32*)&(implParam->c_fact)) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint32*)&(implParam->c_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint32*)&(implParam->c_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint32*)&(implParam->c_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint32*)&(implParam->n_thresh)) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 24) & 0x000000FF);

    /** - Execute save function of block */
    error = AdaptiveNotch_Float32_Save(block, SaveFncDataBuffer, 16);

    return (error);
}

/**
 * @brief Converts Mask parameters into Implementation parameters and executes Block Save function.
 *
 * @param[out] block Block Implementation
 * @param[in] maskParam Mask Parameters
 *
 * @return 0 if successful, greater than 0 if conversion failed
 */
uint8 AdaptiveNotch_Float32_ConvertMP(ADAPTIVENOTCH_FLOAT32 *block, ADAPTIVENOTCH_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    ADAPTIVENOTCH_FLOAT32_IMPL_PARAM *implParam = (ADAPTIVENOTCH_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint32*)&(implParam->a_fact)) & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint32*)&(implParam->a_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint32*)&(implParam->a_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint32*)&(implParam->a_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint32*)&(implParam->b_fact)) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint32*)&(implParam->b_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint32*)&(implParam->b_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint32*)&(implParam->b_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint32*)&(implParam->c_fact)) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint32*)&(implParam->c_fact) >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint32*)&(implParam->c_fact) >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint32*)&(implParam->c_fact) >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint32*)&(implParam->n_thresh)) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint32*)&(implParam->n_thresh) >> 24) & 0x000000FF);

    /** - Execute save function of block */
    error = AdaptiveNotch_Float32_Save(block, SaveFncDataBuffer, 16);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void AdaptiveNotch_Float32_BackupMP(ADAPTIVENOTCH_FLOAT32_MASK_PARAM* maskParam)
{
    memcpy(MaskParamBuffer, maskParam, sizeof(*maskParam));
}

/**
 * @brief Restores Mask parameters from global Mask parameter backup array.
 *
 * @param[out] maskParam Mask parameters
 *
 * @return Nothing
 */
void AdaptiveNotch_Float32_RestoreMP(ADAPTIVENOTCH_FLOAT32_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
