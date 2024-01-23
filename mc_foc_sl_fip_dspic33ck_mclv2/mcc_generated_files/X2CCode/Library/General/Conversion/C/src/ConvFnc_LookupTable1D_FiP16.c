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
 * $LastChangedRevision: 2077 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "ConvFnc_LookupTable1D_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int8 sfrX;
    uint16 maskX;
    uint16 idxOffsetX;
    int16 gainX;
    int8 gainXsfr;
    int16 offsetX;
    int16 minX;
    int16 maxX;
} LOOKUPTABLE1D_FIP16_IMPL_PARAM;

/** DimX enumeration */
typedef enum {
    DIMX_17 = 0,
    DIMX_33 = 1,
    DIMX_65 = 2,
    DIMX_129 = 3,
    DIMX_257 = 4,
    DIMX_513 = 5,
    DIMX_1025 = 6,
    DIMX_2049 = 7,
    DIMX_4097 = 8
} tDimX;

/** Private prototypes */
static uint8 convertM2I(const LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam, LOOKUPTABLE1D_FIP16_IMPL_PARAM *impParam);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam, LOOKUPTABLE1D_FIP16_IMPL_PARAM *impParam)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    error = 1;  /* conversion of flash table is not supported/reasonable */

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
uint8 LookupTable1D_FiP16_LoadMP(const LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)25 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(maskParam->TableData)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(maskParam->TableData) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->TableData) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->TableData) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->TableData) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->TableData) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->TableData) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->TableData) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)(maskParam->DimX);
        data[9] = (uint8)((*(uint64*)&(maskParam->x_min)) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->x_min) >> 8) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->x_min) >> 16) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->x_min) >> 24) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->x_min) >> 32) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->x_min) >> 40) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->x_min) >> 48) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->x_min) >> 56) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->x_max)) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->x_max) >> 8) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->x_max) >> 16) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->x_max) >> 24) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->x_max) >> 32) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->x_max) >> 40) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->x_max) >> 48) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->x_max) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)25;
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
uint8 LookupTable1D_FiP16_SaveMP(LOOKUPTABLE1D_FIP16 *block, LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)25)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        LookupTable1D_FiP16_BackupMP(maskParam);

        /** - Save new mask parameters */
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        maskParam->TableData = (float64)(*(float64*)&tmp64);
        maskParam->DimX = data[8];
        tmp64 = (uint64)data[9] + \
            ((uint64)data[10] << 8) + ((uint64)data[11] << 16) + \
            ((uint64)data[12] << 24) + ((uint64)data[13] << 32) + \
            ((uint64)data[14] << 40) + ((uint64)data[15] << 48) + \
            ((uint64)data[16] << 56);
        maskParam->x_min = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[17] + \
            ((uint64)data[18] << 8) + ((uint64)data[19] << 16) + \
            ((uint64)data[20] << 24) + ((uint64)data[21] << 32) + \
            ((uint64)data[22] << 40) + ((uint64)data[23] << 48) + \
            ((uint64)data[24] << 56);
        maskParam->x_max = (float64)(*(float64*)&tmp64);

        error = LookupTable1D_FiP16_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            LookupTable1D_FiP16_RestoreMP(maskParam);
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
uint8 LookupTable1D_FiP16_InitMP(LOOKUPTABLE1D_FIP16 *block, const LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;

    LOOKUPTABLE1D_FIP16_IMPL_PARAM *implParam = (LOOKUPTABLE1D_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)implParam->sfrX;
    SaveFncDataBuffer[1] = (uint8)(implParam->maskX & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->maskX >> 8) & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)(implParam->idxOffsetX & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)((implParam->idxOffsetX >> 8) & 0x00FF);
    SaveFncDataBuffer[5] = (uint8)(implParam->gainX & 0x00FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->gainX >> 8) & 0x00FF);
    SaveFncDataBuffer[7] = (uint8)implParam->gainXsfr;
    SaveFncDataBuffer[8] = (uint8)(implParam->offsetX & 0x00FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->offsetX >> 8) & 0x00FF);
    SaveFncDataBuffer[10] = (uint8)(implParam->minX & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->minX >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->maxX & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->maxX >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = LookupTable1D_FiP16_Save(block, SaveFncDataBuffer, 14);

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
uint8 LookupTable1D_FiP16_ConvertMP(LOOKUPTABLE1D_FIP16 *block, LOOKUPTABLE1D_FIP16_MASK_PARAM *maskParam)
{
    uint8 error;
    LOOKUPTABLE1D_FIP16_IMPL_PARAM *implParam = (LOOKUPTABLE1D_FIP16_IMPL_PARAM*)ImplParamBuffer;

    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam);
    if (error)
    {
        return (error);
    }

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)implParam->sfrX;
    SaveFncDataBuffer[1] = (uint8)(implParam->maskX & 0x00FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->maskX >> 8) & 0x00FF);
    SaveFncDataBuffer[3] = (uint8)(implParam->idxOffsetX & 0x00FF);
    SaveFncDataBuffer[4] = (uint8)((implParam->idxOffsetX >> 8) & 0x00FF);
    SaveFncDataBuffer[5] = (uint8)(implParam->gainX & 0x00FF);
    SaveFncDataBuffer[6] = (uint8)((implParam->gainX >> 8) & 0x00FF);
    SaveFncDataBuffer[7] = (uint8)implParam->gainXsfr;
    SaveFncDataBuffer[8] = (uint8)(implParam->offsetX & 0x00FF);
    SaveFncDataBuffer[9] = (uint8)((implParam->offsetX >> 8) & 0x00FF);
    SaveFncDataBuffer[10] = (uint8)(implParam->minX & 0x00FF);
    SaveFncDataBuffer[11] = (uint8)((implParam->minX >> 8) & 0x00FF);
    SaveFncDataBuffer[12] = (uint8)(implParam->maxX & 0x00FF);
    SaveFncDataBuffer[13] = (uint8)((implParam->maxX >> 8) & 0x00FF);

    /** - Execute save function of block */
    error = LookupTable1D_FiP16_Save(block, SaveFncDataBuffer, 14);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void LookupTable1D_FiP16_BackupMP(LOOKUPTABLE1D_FIP16_MASK_PARAM* maskParam)
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
void LookupTable1D_FiP16_RestoreMP(LOOKUPTABLE1D_FIP16_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
