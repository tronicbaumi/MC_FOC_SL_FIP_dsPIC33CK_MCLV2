/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
#include "ConvFnc_Biquad_Float32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    float32 b0;
    float32 b1;
    float32 b2;
    float32 a1;
    float32 a2;
} BIQUAD_FLOAT32_IMPL_PARAM;

/** Private prototypes */
static uint8 convertM2I(const BIQUAD_FLOAT32_MASK_PARAM *maskParam, BIQUAD_FLOAT32_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const BIQUAD_FLOAT32_MASK_PARAM *maskParam, BIQUAD_FLOAT32_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    float_CoT b0, b1, b2, a0, a1, a2;

    /* get coefficient a0 for normalization purposes */
    a0 = maskParam->a0;
    if (a0 == 0)
    {
        error = 1;
    }
    else
    {
        /* get mask parameter values and normalize them */
        b0 = (maskParam->b0) / a0;
        b1 = (maskParam->b1) / a0;
        b2 = (maskParam->b2) / a0;
        a1 = (maskParam->a1) / a0;
        a2 = (maskParam->a2) / a0;

        /* set implementation parameter values */
        impParam->b0 = b0;
        impParam->b1 = b1;
        impParam->b2 = b2;
        impParam->a1 = a1;
        impParam->a2 = a2;
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
uint8 Biquad_Float32_LoadMP(const BIQUAD_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)56 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->b1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->b2)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->b2) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->b2) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->b2) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->b2) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->b2) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->b2) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->b2) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->a0)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->a0) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->a0) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->a0) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->a0) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->a0) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->a0) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->a0) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->a1)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(maskParam->a1) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(maskParam->a1) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(maskParam->a1) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(maskParam->a1) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(maskParam->a1) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(maskParam->a1) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(maskParam->a1) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(maskParam->a2)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(maskParam->a2) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(maskParam->a2) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(maskParam->a2) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(maskParam->a2) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(maskParam->a2) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(maskParam->a2) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(maskParam->a2) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)56;
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
uint8 Biquad_Float32_SaveMP(BIQUAD_FLOAT32 *block, BIQUAD_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)56)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        Biquad_Float32_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->b1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->b2 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        maskParam->a0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        maskParam->a1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        maskParam->a2 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = Biquad_Float32_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            Biquad_Float32_RestoreMP(maskParam);
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
uint8 Biquad_Float32_InitMP(BIQUAD_FLOAT32 *block, const BIQUAD_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    BIQUAD_FLOAT32_IMPL_PARAM *implParam = (BIQUAD_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint32*)&(implParam->b0)) & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint32*)&(implParam->b0) >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint32*)&(implParam->b0) >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint32*)&(implParam->b0) >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint32*)&(implParam->b1)) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint32*)&(implParam->b1) >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint32*)&(implParam->b1) >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint32*)&(implParam->b1) >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint32*)&(implParam->b2)) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint32*)&(implParam->b2) >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint32*)&(implParam->b2) >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint32*)&(implParam->b2) >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint32*)&(implParam->a1)) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint32*)&(implParam->a1) >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint32*)&(implParam->a1) >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint32*)&(implParam->a1) >> 24) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)((*(uint32*)&(implParam->a2)) & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)((*(uint32*)&(implParam->a2) >> 8) & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((*(uint32*)&(implParam->a2) >> 16) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((*(uint32*)&(implParam->a2) >> 24) & 0x000000FF);

    /** - Execute save function of block */
    error = Biquad_Float32_Save(block, SaveFncDataBuffer, 20);

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
uint8 Biquad_Float32_ConvertMP(BIQUAD_FLOAT32 *block, BIQUAD_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    BIQUAD_FLOAT32_IMPL_PARAM *implParam = (BIQUAD_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)((*(uint32*)&(implParam->b0)) & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((*(uint32*)&(implParam->b0) >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((*(uint32*)&(implParam->b0) >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((*(uint32*)&(implParam->b0) >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)((*(uint32*)&(implParam->b1)) & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((*(uint32*)&(implParam->b1) >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((*(uint32*)&(implParam->b1) >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((*(uint32*)&(implParam->b1) >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)((*(uint32*)&(implParam->b2)) & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((*(uint32*)&(implParam->b2) >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((*(uint32*)&(implParam->b2) >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((*(uint32*)&(implParam->b2) >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)((*(uint32*)&(implParam->a1)) & 0x000000FF);
    SaveFncDataBuffer[13] = (uint8)((*(uint32*)&(implParam->a1) >> 8) & 0x000000FF);
    SaveFncDataBuffer[14] = (uint8)((*(uint32*)&(implParam->a1) >> 16) & 0x000000FF);
    SaveFncDataBuffer[15] = (uint8)((*(uint32*)&(implParam->a1) >> 24) & 0x000000FF);
    SaveFncDataBuffer[16] = (uint8)((*(uint32*)&(implParam->a2)) & 0x000000FF);
    SaveFncDataBuffer[17] = (uint8)((*(uint32*)&(implParam->a2) >> 8) & 0x000000FF);
    SaveFncDataBuffer[18] = (uint8)((*(uint32*)&(implParam->a2) >> 16) & 0x000000FF);
    SaveFncDataBuffer[19] = (uint8)((*(uint32*)&(implParam->a2) >> 24) & 0x000000FF);

    /** - Execute save function of block */
    error = Biquad_Float32_Save(block, SaveFncDataBuffer, 20);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void Biquad_Float32_BackupMP(BIQUAD_FLOAT32_MASK_PARAM* maskParam)
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
void Biquad_Float32_RestoreMP(BIQUAD_FLOAT32_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
