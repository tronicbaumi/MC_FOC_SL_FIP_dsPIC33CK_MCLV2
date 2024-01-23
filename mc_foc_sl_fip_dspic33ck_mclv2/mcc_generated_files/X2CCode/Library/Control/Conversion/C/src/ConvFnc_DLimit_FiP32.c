/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 2800 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_DLimit_FiP32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int32 b0d;
    int32 b1d;
    int32 a0d;
    int8 sfrd;
} DLIMIT_FIP32_IMPL_PARAM;

/** Private prototypes */
static uint8 convertM2I(const DLIMIT_FIP32_MASK_PARAM *maskParam, DLIMIT_FIP32_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const DLIMIT_FIP32_MASK_PARAM *maskParam, DLIMIT_FIP32_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    float_CoT mp_Kd;
    float_CoT mp_fc, wc;
    float_CoT b0d, b1d, a0d;

    /* get mask parameter values */
    mp_Kd = (float_CoT)(maskParam->Kd);
    mp_fc = (float_CoT)(maskParam->fc);

    /* validate controller parameters */
    if (mp_fc < 0)
    {
            mp_fc = -mp_fc;
    }

    /* calculate temporary variables */
    wc = 2 * (float_CoT)PI_R64 * mp_fc;

    /* Zero order hold (zoh):
     * G(s) = Kd*s/(s/w+1)-> G(z) = Kd*w*(z-1)/(z-exp(-w*T))
     */
    b0d = -mp_Kd * wc;
    b1d = mp_Kd * wc;
    #if defined(USE_FLOAT64_CONV_FNC)
        #if defined(__XC16__)
            a0d = -expl(-wc * ts);
        #else
            a0d = -exp(-wc * ts);
        #endif
    #else
        a0d = -expf(-wc * ts);
    #endif

    impParam->sfrd = getQFormat(b0d, 32);
    impParam->b0d = getQx32Value(b0d, (impParam->sfrd));
    impParam->b1d = getQx32Value(b1d, (impParam->sfrd));
    impParam->a0d = getQx32Value(a0d, 31);

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
uint8 DLimit_FiP32_LoadMP(const DLIMIT_FIP32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)24 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->Kd)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->Kd) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->Kd) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->Kd) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->Kd) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->Kd) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->Kd) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->Kd) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->fc)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->fc) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->fc) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->fc) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->fc) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->fc) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->fc) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->fc) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)24;
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
uint8 DLimit_FiP32_SaveMP(DLIMIT_FIP32 *block, DLIMIT_FIP32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)24)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        DLimit_FiP32_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->Kd = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        maskParam->fc = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = DLimit_FiP32_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            DLimit_FiP32_RestoreMP(maskParam);
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
uint8 DLimit_FiP32_InitMP(DLIMIT_FIP32 *block, const DLIMIT_FIP32_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    DLIMIT_FIP32_IMPL_PARAM *implParam = (DLIMIT_FIP32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0d & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0d >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0d >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0d >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1d & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1d >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1d >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1d >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->a0d & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->a0d >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->a0d >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->a0d >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)implParam->sfrd;

    /** - Execute save function of block */
    error = DLimit_FiP32_Save(block, SaveFncDataBuffer, 13);

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
uint8 DLimit_FiP32_ConvertMP(DLIMIT_FIP32 *block, DLIMIT_FIP32_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    DLIMIT_FIP32_IMPL_PARAM *implParam = (DLIMIT_FIP32_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->b0d & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->b0d >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->b0d >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->b0d >> 24) & 0x000000FF);
    SaveFncDataBuffer[4] = (uint8)(implParam->b1d & 0x000000FF);
    SaveFncDataBuffer[5] = (uint8)((implParam->b1d >> 8) & 0x000000FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->b1d >> 16) & 0x000000FF);
    SaveFncDataBuffer[7] = (uint8)((implParam->b1d >> 24) & 0x000000FF);
    SaveFncDataBuffer[8] = (uint8)(implParam->a0d & 0x000000FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->a0d >> 8) & 0x000000FF);
    SaveFncDataBuffer[10] = (uint8)((implParam->a0d >> 16) & 0x000000FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->a0d >> 24) & 0x000000FF);
    SaveFncDataBuffer[12] = (uint8)implParam->sfrd;

    /** - Execute save function of block */
    error = DLimit_FiP32_Save(block, SaveFncDataBuffer, 13);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void DLimit_FiP32_BackupMP(DLIMIT_FIP32_MASK_PARAM* maskParam)
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
void DLimit_FiP32_RestoreMP(DLIMIT_FIP32_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
