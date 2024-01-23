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
#include "ConvFnc_LowpassBiQ_Float32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

#ifdef USE_FLOAT64_CONV_FNC
#define HALF_SQRT2  (sqrt(2.0) / 2.0)
#define HALF_SQRT3  (sqrt(3.0) / 2.0)
#define SQRT2       (sqrt(2.0))
#else
#define HALF_SQRT2  (sqrtf(2.0f) / 2.0f)
#define HALF_SQRT3  (sqrtf(3.0f) / 2.0f)
#define SQRT2       (sqrtf(2.0f))
#endif
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
} LOWPASSBIQ_FLOAT32_IMPL_PARAM;

/** characteristic enumeration */
typedef enum {
    CHARACTERISTIC_BUTTERWORTH = 0,
    CHARACTERISTIC_CHEBYSHEV_I = 1,
    CHARACTERISTIC_CHEBYSHEV_II = 2,
    CHARACTERISTIC_BESSEL = 3
} tcharacteristic;

/** Private prototypes */
static uint8 convertM2I(const LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam, LOWPASSBIQ_FLOAT32_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam, LOWPASSBIQ_FLOAT32_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
    float_CoT fs, rp, rs;
    float_CoT fc, fcScaled, fsScaled;
    float_CoT k, p_x, p_y, z_x, z_y, warped, relDegree;
    float_CoT arg, eps, mu, theta, x, de, scale_p;
    float_CoT fs2, zz_x, zz_y, nom_x, nom_y, denom_x, denom_y, mag_nom, mag_denom, mag, phase_nom, phase_denom, phase, prod_z;
    float_CoT pz_x, pz_y, prod_p, kz;
    float_CoT b0, b1, b2, a1, a2;

    fc = maskParam->fc;
    rp = getAbsValR64(maskParam->rp);
    rs = getAbsValR64(maskParam->rs);

    /* get sampling frequency */
    fs = 1 / ts;

    /* validate input */
    if ((2 * fc) >= fs) {
        /* Error: Wrong Input! Cutoff frequency was choosen to big! Should be less then fs/2. */
        return (1);
    }

    /* Normalize frequency */
    fcScaled = (2 * fc) / fs;

    /* ----------------------------------------------------------------------------------------- */
    /* Get analog lowpass prototype */
    /* ----------------------------------------------------------------------------------------- */
    if (maskParam->characteristic == CHARACTERISTIC_BUTTERWORTH) {
        /* poles */
        p_x = -HALF_SQRT2;
        p_y = HALF_SQRT2;
        /* gain */
        k = 1.0;
    } else if (maskParam->characteristic == CHARACTERISTIC_CHEBYSHEV_I) {
        if (rp == 0) {
            /*  Error: Division by zero! Choose a passband ripple different from zero! */
            return (2);
        } else if (rp < 0) {
            /*  Error: Negative ripple value given! Enter a positive passband ripple value! */
            return (3);
        }

#ifdef USE_FLOAT64_CONV_FNC
        /* poles */
        arg = pow(10.0, 0.1 * rp) - 1.0;
        eps = sqrt(arg);
        x = 1 / eps;
        mu = 0.5 * log(x + sqrt((x * x) + 1.0)); // = arcsinh(x)
        theta = PI_R64 / 4.0;
        /*
         * arg = mu + 1j*theta = x + jy p = -np.sinh(arg) = = -(cos(y)*sinh(x) +j sin(y)*cosh(x))
         */
        p_x = -cos(theta) * sinh(mu);
        p_y = -sin(theta) * cosh(mu);

        /* gain */
        prod_p = (p_x * p_x) + (p_y * p_y);
        k = prod_p / (sqrt(1.0 + (eps * eps)));
#else
        /* poles */
        arg = powf(10.0f, 0.1f * rp) - 1.0f;
        eps = sqrtf(arg);
        x = 1.0f / eps;
        mu = 0.5f * logf(x + sqrt((x * x) + 1.0f)); // = arcsinh(x)
        theta = PI_R32 / 4.0f;
        /*
         * arg = mu + 1j*theta = x + jy p = -np.sinh(arg) = = -(cos(y)*sinh(x) +j sin(y)*cosh(x))
         */
        p_x = -cosf(theta) * sinhf(mu);
        p_y = -sinf(theta) * coshf(mu);

        /* gain */
        prod_p = (p_x * p_x) + (p_y * p_y);
        k = prod_p / (sqrtf(1.0 + (eps * eps)));
#endif

    } else if (maskParam->characteristic == CHARACTERISTIC_CHEBYSHEV_II) {
        if (rs == 0) {
            /* Error: Division by zero! Choose a stopband ripple different from zero! */
            return (4);
        } else if (rs < 0) {
            /* Error: Negative ripple value given! Enter a positive stopband ripple value! */
            return (5);
        }
#ifdef USE_FLOAT64_CONV_FNC
        arg = pow(10.0, 0.1 * rs) - 1.0;
        de = 1.0 / sqrt(arg);
        x = 1.0 / de;
        mu = 0.5 * log(x + sqrt((x * x) + 1.0)); // = arcsinh(x)

        /* zeros */
        z_x = 0.0;
        z_y = -SQRT2;

        /* poles */
        p_x = -HALF_SQRT2;
        p_y = HALF_SQRT2;
        p_x = sinh(mu) * p_x;
        p_y = cosh(mu) * p_y;
#else
        arg = powf(10.0f, 0.1f * rs) - 1.0f;
        de = 1.0f / sqrtf(arg);
        x = 1.0f / de;
        mu = 0.5f * logf(x + sqrtf((x * x) + 1.0f)); // = arcsinh(x)

        /* zeros */
        z_x = 0.0;
        z_y = -SQRT2;

        /* poles */
        p_x = -HALF_SQRT2;
        p_y = HALF_SQRT2;
        p_x = sinhf(mu) * p_x;
        p_y = coshf(mu) * p_y;
#endif
        /* calculate p = 1/p */
        scale_p = (p_x * p_x) + (p_y * p_y); /* square of magnitude */
        p_x = p_x / scale_p;
        p_y = -p_y / scale_p;

        /* gain */
        prod_p = (p_x * p_x) + (p_y * p_y);
        prod_z = (z_x * z_x) + (z_y * z_y);
        k = prod_p / prod_z;

    } else if (maskParam->characteristic == CHARACTERISTIC_BESSEL) {
        /* poles */
        p_x = -1.5;
        p_y = HALF_SQRT3;
        /* gain */
        k = 3.0;
    }

    /* ----------------------------------------------------------------------------------------- */
    /* Pre-warp frequencies for digital filter design */
    /* ----------------------------------------------------------------------------------------- */
#ifdef USE_FLOAT64_CONV_FNC
    fsScaled = 2.0;
    warped = 2.0 * fsScaled * tan((PI_R64 * fcScaled) / fsScaled);
#else
    fsScaled = 2.0f;
    warped = 2.0f * fsScaled * tanf((PI_R32 * fcScaled) / fsScaled);
#endif

    /* ----------------------------------------------------------------------------------------- */
    /* transform to lowpass with proper cut-off frequency */
    /* ----------------------------------------------------------------------------------------- */
    if (maskParam->characteristic == CHARACTERISTIC_CHEBYSHEV_II) {
        relDegree = 0;
        /* Scale all points radially from origin to shift cutoff frequency */
        /*
         * zeros z_lp = warped * z
         */
        z_x = warped * z_x;
        z_y = warped * z_y;
    } else {
        relDegree = 2.0; /* =len(p)-len(z) */
    }
    /* Scale all points radially from origin to shift cutoff frequency */
    /*
     * z_lp = warped * z p_lp = warped * p
     */

    /* poles digital lowpass */
    p_x = warped * p_x;
    p_y = warped * p_y;
    /* gain digital lowpass */
#ifdef USE_FLOAT64_CONV_FNC
    k = k * pow(warped, relDegree);
#else
    k = k * powf(warped, relDegree);
#endif

    /* ----------------------------------------------------------------------------------------- */
    /* transform to discrete lowpass (bilinear transform) */
    /* ----------------------------------------------------------------------------------------- */
    fs2 = 2.0 * 2;

    /*
     * zeros z_z = (fs2 + z) / (fs2 - z)
     */
    if (maskParam->characteristic == CHARACTERISTIC_CHEBYSHEV_II) {
        nom_x = fs2 + z_x;
        nom_y = z_y;
        denom_x = fs2 - z_x;
        denom_y = -z_y;
        prod_z = (denom_x * denom_x) + (denom_y * denom_y); /* product of conjugate complex number */

#ifdef USE_FLOAT64_CONV_FNC
        /* rect2pol */
        mag_nom = sqrt(pow(nom_x, 2) + pow(nom_y, 2));
        mag_denom = sqrt(pow(denom_x, 2) + pow(denom_y, 2));
        mag = mag_nom / mag_denom;

        phase_nom = atan2(nom_y, nom_x);
        phase_denom = atan2(denom_y, denom_x);
        phase = phase_nom - phase_denom;

        /* pol2rect */
        zz_x = mag * cos(phase); /* real */
        zz_y = mag * sin(phase); /* imag */
#else
        /* rect2pol */
        mag_nom = sqrtf(powf(nom_x, 2) + powf(nom_y, 2));
        mag_denom = sqrtf(powf(denom_x, 2) + powf(denom_y, 2));
        mag = mag_nom / mag_denom;

        phase_nom = atan2f(nom_y, nom_x);
        phase_denom = atan2f(denom_y, denom_x);
        phase = phase_nom - phase_denom;

        /* pol2rect */
        zz_x = mag * cosf(phase); /* real */
        zz_y = mag * sinf(phase); /* imag */
#endif

    } else {
        zz_x = -1;
        zz_y = 0;
        prod_z = 1;
    }

    /* poles */
    /* p_z = (fs2 + p) / (fs2 - p) */
    nom_x = fs2 + p_x;
    nom_y = p_y;
    denom_x = fs2 - p_x;
    denom_y = -p_y;

#ifdef USE_FLOAT64_CONV_FNC
    /* rect2pol */
    mag_nom = sqrt(pow(nom_x, 2) + pow(nom_y, 2));
    mag_denom = sqrt(pow(denom_x, 2) + pow(denom_y, 2));
    mag = mag_nom / mag_denom;

    phase_nom = atan2(nom_y, nom_x);
    phase_denom = atan2(denom_y, denom_x);
    phase = phase_nom - phase_denom;

    /* pol2rect */
    pz_x = mag * cos(phase); /* real */
    pz_y = mag * sin(phase); /* imag */
#else
    /* rect2pol */
    mag_nom = sqrtf(powf(nom_x, 2) + powf(nom_y, 2));
    mag_denom = sqrtf(powf(denom_x, 2) + powf(denom_y, 2));
    mag = mag_nom / mag_denom;

    phase_nom = atan2f(nom_y, nom_x);
    phase_denom = atan2f(denom_y, denom_x);
    phase = phase_nom - phase_denom;

    /* pol2rect */
    pz_x = mag * cosf(phase); /* real */
    pz_y = mag * sinf(phase); /* imag */
#endif

    prod_p = (denom_x * denom_x) + (denom_y * denom_y); /* product of conjugate complex number */

    /* gain */
    kz = (k * prod_z) / prod_p;

    /* ----------------------------------------------------------------------------------------- */
    /* transform to proper form */
    /* ----------------------------------------------------------------------------------------- */
    /* numerator coefficients */
    b0 = kz * 1; /* coefficient to s^2 */
    b1 = kz * -2.0 * zz_x; /* coefficient to s^1 */
    b2 = kz * ((zz_x * zz_x) + (zz_y * zz_y)); /* coefficient to s^0 */

    /* denominator coefficients */
    //a0 = 1; /* coefficient to s^2 */
    a1 = -2.0 * pz_x; /* coefficient to s^1 */
    a2 = (pz_x * pz_x) + (pz_y * pz_y); /* coefficient to s^0 */

    /* set block parameter = filter coefficients */
    impParam->b0 = b0;
    impParam->b1 = b1;
    impParam->b2 = b2;
    impParam->a1 = a1;
    impParam->a2 = a2;

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
uint8 LowpassBiQ_Float32_LoadMP(const LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)33 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(maskParam->characteristic);
        data[1] = (uint8)((*(uint64*)&(maskParam->fc)) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(maskParam->fc) >> 8) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(maskParam->fc) >> 16) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(maskParam->fc) >> 24) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->fc) >> 32) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->fc) >> 40) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->fc) >> 48) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->fc) >> 56) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->rp)) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->rp) >> 8) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->rp) >> 16) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(maskParam->rp) >> 24) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(maskParam->rp) >> 32) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(maskParam->rp) >> 40) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(maskParam->rp) >> 48) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(maskParam->rp) >> 56) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(maskParam->rs)) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(maskParam->rs) >> 8) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(maskParam->rs) >> 16) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(maskParam->rs) >> 24) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(maskParam->rs) >> 32) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(maskParam->rs) >> 40) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(maskParam->rs) >> 48) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(maskParam->rs) >> 56) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)33;
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
uint8 LowpassBiQ_Float32_SaveMP(LOWPASSBIQ_FLOAT32 *block, LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)33)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        /** - Cache old mask parameters */
        LowpassBiQ_Float32_BackupMP(maskParam);

        /** - Save new mask parameters */
        maskParam->characteristic = data[0];
        tmp64 = (uint64)data[1] + \
            ((uint64)data[2] << 8) + ((uint64)data[3] << 16) + \
            ((uint64)data[4] << 24) + ((uint64)data[5] << 32) + \
            ((uint64)data[6] << 40) + ((uint64)data[7] << 48) + \
            ((uint64)data[8] << 56);
        maskParam->fc = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[9] + \
            ((uint64)data[10] << 8) + ((uint64)data[11] << 16) + \
            ((uint64)data[12] << 24) + ((uint64)data[13] << 32) + \
            ((uint64)data[14] << 40) + ((uint64)data[15] << 48) + \
            ((uint64)data[16] << 56);
        maskParam->rp = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[17] + \
            ((uint64)data[18] << 8) + ((uint64)data[19] << 16) + \
            ((uint64)data[20] << 24) + ((uint64)data[21] << 32) + \
            ((uint64)data[22] << 40) + ((uint64)data[23] << 48) + \
            ((uint64)data[24] << 56);
        maskParam->rs = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[25] + \
            ((uint64)data[26] << 8) + ((uint64)data[27] << 16) + \
            ((uint64)data[28] << 24) + ((uint64)data[29] << 32) + \
            ((uint64)data[30] << 40) + ((uint64)data[31] << 48) + \
            ((uint64)data[32] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        error = LowpassBiQ_Float32_ConvertMP(block, maskParam);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            LowpassBiQ_Float32_RestoreMP(maskParam);
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
uint8 LowpassBiQ_Float32_InitMP(LOWPASSBIQ_FLOAT32 *block, const LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    LOWPASSBIQ_FLOAT32_IMPL_PARAM *implParam = (LOWPASSBIQ_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

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
    error = LowpassBiQ_Float32_Save(block, SaveFncDataBuffer, 20);

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
uint8 LowpassBiQ_Float32_ConvertMP(LOWPASSBIQ_FLOAT32 *block, LOWPASSBIQ_FLOAT32_MASK_PARAM *maskParam)
{
    uint8 error;
    float_CoT block_ts;
    LOWPASSBIQ_FLOAT32_IMPL_PARAM *implParam = (LOWPASSBIQ_FLOAT32_IMPL_PARAM*)ImplParamBuffer;

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
    error = LowpassBiQ_Float32_Save(block, SaveFncDataBuffer, 20);

    return (error);
}

/**
 * @brief Backups current Mask parameters into global Mask parameter backup array.
 *
 * @param[in] maskParam Mask parameters
 *
 * @return Nothing
 */
void LowpassBiQ_Float32_BackupMP(LOWPASSBIQ_FLOAT32_MASK_PARAM* maskParam)
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
void LowpassBiQ_Float32_RestoreMP(LOWPASSBIQ_FLOAT32_MASK_PARAM* maskParam)
{
    memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
}
