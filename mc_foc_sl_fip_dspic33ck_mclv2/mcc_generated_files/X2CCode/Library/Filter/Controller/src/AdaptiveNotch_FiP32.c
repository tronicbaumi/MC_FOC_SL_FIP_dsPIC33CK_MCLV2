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
/* Implementation:
 *
 *   A = -w0/2/Q*Ts
 *   B = -w0/2/Q*(sqrt(4*Q^2-1))*Ts
 *   C = w0*Ts
 *   a = [1, -2 * exp(A) * cos(B), exp(2*A)]
 *   b = [1, -2 * cos(C),          1]
 *
 *   K = sum(a) / sum(b)
 *   b = b * K
 */
/* USERCODE-END:Description                                                                                           */
#include "AdaptiveNotch_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AdaptiveNotch_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Exp_Data.h"
#include "Sin_Data.h"

/* Inputs */
#define IN              (*pTAdaptiveNotch_FiP32->In)
#define N               (*pTAdaptiveNotch_FiP32->n)

/* Outputs */
#define OUT             (pTAdaptiveNotch_FiP32->Out)

/* Parameter */
#define N_THRESH        (pTAdaptiveNotch_FiP32->n_thresh)
#define A_FACT          (pTAdaptiveNotch_FiP32->a_fact)
#define B_FACT          (pTAdaptiveNotch_FiP32->b_fact)
#define C_FACT          (pTAdaptiveNotch_FiP32->c_fact)
#define SFR_A           (pTAdaptiveNotch_FiP32->sfrA)

/* Variables */
#define A2              (pTAdaptiveNotch_FiP32->a2)
#define A1              (pTAdaptiveNotch_FiP32->a1)
#define B1              (pTAdaptiveNotch_FiP32->b1)
#define K               (pTAdaptiveNotch_FiP32->k)
#define IN_OLD          (pTAdaptiveNotch_FiP32->in_old)
#define IN_VERY_OLD     (pTAdaptiveNotch_FiP32->in_very_old)
#define OUT_OLD         (pTAdaptiveNotch_FiP32->out_old)
#define OUT_VERY_OLD    (pTAdaptiveNotch_FiP32->out_very_old)
#define N_OLD           (pTAdaptiveNotch_FiP32->n_old)

/* Constants */
#define A0              ((int32)INT32_MAX)
#define B0              ((int32)INT32_MAX)
#define B2              ((int32)INT32_MAX)
#define PI_HALF         ((int32)0x40000000)     /* Pi/2	[Q31] */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AdaptiveNotch_FiP32_Update(ADAPTIVENOTCH_FIP32 *pTAdaptiveNotch_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int64 temp64;
    int32 absN;
    
    /* calculate absolute value of speed to ensure correct computation of coefficients */
    absN = getAbsValI32(N);

    if (absN > N_THRESH)
    {
        /* current speed is above threshold -> filter the input signal */
        if (N != N_OLD)
        {
            /* speed has changed -> update filter coefficients */
            int32 expA, cosine, temp;
       
            temp = ((int64)absN * (int64)A_FACT) >> SFR_A;  /* A = -w0/2/Q*Ts */
            LOOKUP32(Exp_Table32, temp, expA);              /* exp(A) */

            /** - calculate filter coefficients */
            temp = ((int64)absN * (int64)B_FACT) >> 31;     /* B = -w0/2/Q*(sqrt(4*Q^2-1))*Ts */
            temp = PI_HALF - temp;	                        /* cos(temp) = sin(pi/2 - temp) */
            LOOKUP32(Sin_Table32, temp, cosine);            /* cos(B)*/
            A1 = -((int64)expA * (int64)cosine) >> 31;      /* -2 * exp(A) * cos(B)  [Q30] */
            
            A2 = ((int64)expA * (int64)expA) >> 31;         /* exp(2*A) [Q31] */  
            
            temp = ((int64)absN * (int64)C_FACT) >> 31;     /* C = w0 * Ts */
            temp = PI_HALF - temp;	                        /* cos(temp) = sin(pi/2 - temp) */
            LOOKUP32(Sin_Table32, temp, cosine);            /* cos(C)*/
            B1 = -cosine;                                   /* -2 * cos(C) [Q30] */

            /** - calculate gain correction value */
            K = (((int64)A0 + (((int64)A1)<<1) + (int64)A2) << 31) / ((((int64)B0)) + (((int64)B1)<<1) + (((int64)B2))); /* Q62 / Q31 = Q31 */

            N_OLD = N;
        }

        /** - do the filtering */
        temp64  = (int64)IN;                                    /* b0*u(k) */
        temp64 += (((int64)B1 * (int64)IN_OLD) >> 30);          /* b1*u(k-1)*/
        temp64 += ((int64)IN_VERY_OLD);                         /* b2*u(k-2) */
        temp64  = (temp64 * (int64)K) >> 31;                    /* adjust gain */
        temp64 -= (((int64)A1 * (int64)OUT_OLD) >> 30);         /* a1*y(k-1)*/
        temp64 -= (((int64)A2 * (int64)OUT_VERY_OLD) >> 31);    /* a2*y(k-2)*/

        /** - set output */
        LIMIT(temp64, INT32_MAX);
        OUT = (int32)temp64;            /* y(k) = b0*u(k) + b1*u(k-1) + b2*u(k-2) - a1*y(k-1) - a2*y(k-2) */
    }
    else
    {
        /* current speed is below threshold -> do not filter the input signal */
        OUT = IN;
    }

    /** - save in- and output values for next cycle */
    IN_VERY_OLD = IN_OLD;
    IN_OLD = IN;
    OUT_VERY_OLD = OUT_OLD;
    OUT_OLD = OUT;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void AdaptiveNotch_FiP32_Init(ADAPTIVENOTCH_FIP32 *pTAdaptiveNotch_FiP32)
{
    pTAdaptiveNotch_FiP32->ID = ADAPTIVENOTCH_FIP32_ID;
    pTAdaptiveNotch_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    A2 = 0;
    A1 = 0;
    B1 = 0;
    IN_VERY_OLD = 0;
    IN_OLD = 0;
    OUT_VERY_OLD = 0;
    OUT_OLD = 0;
    N_OLD = 0;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_FiP32_Load(const ADAPTIVENOTCH_FIP32 *pTAdaptiveNotch_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)17 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTAdaptiveNotch_FiP32->n_thresh & 0x000000FF);
        data[1] = (uint8)((pTAdaptiveNotch_FiP32->n_thresh >> 8) & 0x000000FF);
        data[2] = (uint8)((pTAdaptiveNotch_FiP32->n_thresh >> 16) & 0x000000FF);
        data[3] = (uint8)((pTAdaptiveNotch_FiP32->n_thresh >> 24) & 0x000000FF);
        data[4] = (uint8)(pTAdaptiveNotch_FiP32->a_fact & 0x000000FF);
        data[5] = (uint8)((pTAdaptiveNotch_FiP32->a_fact >> 8) & 0x000000FF);
        data[6] = (uint8)((pTAdaptiveNotch_FiP32->a_fact >> 16) & 0x000000FF);
        data[7] = (uint8)((pTAdaptiveNotch_FiP32->a_fact >> 24) & 0x000000FF);
        data[8] = (uint8)(pTAdaptiveNotch_FiP32->b_fact & 0x000000FF);
        data[9] = (uint8)((pTAdaptiveNotch_FiP32->b_fact >> 8) & 0x000000FF);
        data[10] = (uint8)((pTAdaptiveNotch_FiP32->b_fact >> 16) & 0x000000FF);
        data[11] = (uint8)((pTAdaptiveNotch_FiP32->b_fact >> 24) & 0x000000FF);
        data[12] = (uint8)(pTAdaptiveNotch_FiP32->c_fact & 0x000000FF);
        data[13] = (uint8)((pTAdaptiveNotch_FiP32->c_fact >> 8) & 0x000000FF);
        data[14] = (uint8)((pTAdaptiveNotch_FiP32->c_fact >> 16) & 0x000000FF);
        data[15] = (uint8)((pTAdaptiveNotch_FiP32->c_fact >> 24) & 0x000000FF);
        data[16] = (uint8)pTAdaptiveNotch_FiP32->sfrA;
        *dataLength = (uint16)17;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptiveNotch_FiP32_Save(ADAPTIVENOTCH_FIP32 *pTAdaptiveNotch_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)17)
    {
        error = (uint8)1;
    }
    else
    {
        pTAdaptiveNotch_FiP32->n_thresh = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTAdaptiveNotch_FiP32->a_fact = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTAdaptiveNotch_FiP32->b_fact = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTAdaptiveNotch_FiP32->c_fact = UINT32_TO_INT32((uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24));
        pTAdaptiveNotch_FiP32->sfrA = UINT8_TO_INT8((uint8)data[16]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ADAPTIVENOTCH_FIP32_ISLINKED)
void* AdaptiveNotch_FiP32_GetAddress(const ADAPTIVENOTCH_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->n;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
