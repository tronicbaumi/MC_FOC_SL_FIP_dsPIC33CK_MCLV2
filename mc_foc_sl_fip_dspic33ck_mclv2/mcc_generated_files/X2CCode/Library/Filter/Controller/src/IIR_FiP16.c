/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2162 $
 * $LastChangedDate:: 2021-03-23 19:32:05 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "IIR_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(IIR_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			    (*pTIIR_FiP16->In)

/* Outputs */
#define OUT			    (pTIIR_FiP16->Out)

/* Parameter */
#define	COEFF_A			(pTIIR_FiP16->coeffA)       /* Denominator coefficients array in reversed order (an,...,a2,a1) */
#define	COEFF_B			(pTIIR_FiP16->coeffB)       /* Numerator coefficients array in reversed order (bn,...,b2,b1,b0) */
#define SFRB            (pTIIR_FiP16->sfrB)         /* Shift factor for numerator coefficients */
#define SFRA            (pTIIR_FiP16->sfrA)         /* Shift factor for denominator coefficients */
#define ORDER_N			(pTIIR_FiP16->orderN)       /* Length of numerator coefficients array */
#define ORDER_D			(pTIIR_FiP16->orderD)       /* Length of denominator coefficients array */

/* Variables */
#define BUFFER_IN       (pTIIR_FiP16->inputBuffer)  /* Circular buffer for input signal */
#define BUFFER_OUT      (pTIIR_FiP16->outputBuffer) /* Circular buffer for output signal */
#define IDX_IN			(pTIIR_FiP16->indexIn)      /* Pointer to current position in input buffer */
#define IDX_OUT			(pTIIR_FiP16->indexOut)     /* Pointer to current position in output buffer */

/* Constants */
#define BUFFER_LEN      (32)                        /* Maximum length of circular buffer */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void IIR_FiP16_Update(IIR_FIP16 *pTIIR_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8 i;
	int32 sumA = 0, sumB = 0;

    /* enter In(k) and Out(k-1) in circular buffer */
    BUFFER_IN[IDX_IN]   = IN;
    BUFFER_OUT[IDX_OUT] = OUT;

    /* increase pointers to circular buffers */
	IDX_IN  = (IDX_IN  + 1) % ORDER_N;  /* pointer to element k-N */
	IDX_OUT = (IDX_OUT + 1) % ORDER_D;  /* pointer to element k-D */

    /* calculate sums of numerator and denominator */
    for (i=0; i < ORDER_N; i++)
    {
        sumB += ((int32)COEFF_B[i] * (int32)BUFFER_IN[(IDX_IN + i) % ORDER_N]);
		sumA += ((int32)COEFF_A[i] * (int32)BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
	}
    for (i=ORDER_N; i < ORDER_D; i++)
    {
        sumA += ((int32)COEFF_A[i] * (int32)BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
    }
    sumA = sumA >> SFRA;
    sumB = sumB >> SFRB;
    
    /* calculate total sum */
    sumA = sumB - sumA;
    
    /* check for overflow */
    LIMIT(sumA, INT16_MAX);
    
    /* assign output */
	OUT = sumA;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void IIR_FiP16_Init(IIR_FIP16 *pTIIR_FiP16)
{
    pTIIR_FiP16->ID = IIR_FIP16_ID;
    pTIIR_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    IDX_IN = 0;
	IDX_OUT = 0;
    {
        int8 i;
        for (i=0; i < (BUFFER_LEN-1); i++)
        {
            BUFFER_IN[i]  = 0;
            BUFFER_OUT[i] = 0;
        }
        BUFFER_IN[i+1] = 0;
    }
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 IIR_FiP16_Load(const IIR_FIP16 *pTIIR_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)130 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTIIR_FiP16->coeffB[0] & 0x00FF);
        data[1] = (uint8)((pTIIR_FiP16->coeffB[0] >> 8) & 0x00FF);
        data[2] = (uint8)(pTIIR_FiP16->coeffB[1] & 0x00FF);
        data[3] = (uint8)((pTIIR_FiP16->coeffB[1] >> 8) & 0x00FF);
        data[4] = (uint8)(pTIIR_FiP16->coeffB[2] & 0x00FF);
        data[5] = (uint8)((pTIIR_FiP16->coeffB[2] >> 8) & 0x00FF);
        data[6] = (uint8)(pTIIR_FiP16->coeffB[3] & 0x00FF);
        data[7] = (uint8)((pTIIR_FiP16->coeffB[3] >> 8) & 0x00FF);
        data[8] = (uint8)(pTIIR_FiP16->coeffB[4] & 0x00FF);
        data[9] = (uint8)((pTIIR_FiP16->coeffB[4] >> 8) & 0x00FF);
        data[10] = (uint8)(pTIIR_FiP16->coeffB[5] & 0x00FF);
        data[11] = (uint8)((pTIIR_FiP16->coeffB[5] >> 8) & 0x00FF);
        data[12] = (uint8)(pTIIR_FiP16->coeffB[6] & 0x00FF);
        data[13] = (uint8)((pTIIR_FiP16->coeffB[6] >> 8) & 0x00FF);
        data[14] = (uint8)(pTIIR_FiP16->coeffB[7] & 0x00FF);
        data[15] = (uint8)((pTIIR_FiP16->coeffB[7] >> 8) & 0x00FF);
        data[16] = (uint8)(pTIIR_FiP16->coeffB[8] & 0x00FF);
        data[17] = (uint8)((pTIIR_FiP16->coeffB[8] >> 8) & 0x00FF);
        data[18] = (uint8)(pTIIR_FiP16->coeffB[9] & 0x00FF);
        data[19] = (uint8)((pTIIR_FiP16->coeffB[9] >> 8) & 0x00FF);
        data[20] = (uint8)(pTIIR_FiP16->coeffB[10] & 0x00FF);
        data[21] = (uint8)((pTIIR_FiP16->coeffB[10] >> 8) & 0x00FF);
        data[22] = (uint8)(pTIIR_FiP16->coeffB[11] & 0x00FF);
        data[23] = (uint8)((pTIIR_FiP16->coeffB[11] >> 8) & 0x00FF);
        data[24] = (uint8)(pTIIR_FiP16->coeffB[12] & 0x00FF);
        data[25] = (uint8)((pTIIR_FiP16->coeffB[12] >> 8) & 0x00FF);
        data[26] = (uint8)(pTIIR_FiP16->coeffB[13] & 0x00FF);
        data[27] = (uint8)((pTIIR_FiP16->coeffB[13] >> 8) & 0x00FF);
        data[28] = (uint8)(pTIIR_FiP16->coeffB[14] & 0x00FF);
        data[29] = (uint8)((pTIIR_FiP16->coeffB[14] >> 8) & 0x00FF);
        data[30] = (uint8)(pTIIR_FiP16->coeffB[15] & 0x00FF);
        data[31] = (uint8)((pTIIR_FiP16->coeffB[15] >> 8) & 0x00FF);
        data[32] = (uint8)(pTIIR_FiP16->coeffB[16] & 0x00FF);
        data[33] = (uint8)((pTIIR_FiP16->coeffB[16] >> 8) & 0x00FF);
        data[34] = (uint8)(pTIIR_FiP16->coeffB[17] & 0x00FF);
        data[35] = (uint8)((pTIIR_FiP16->coeffB[17] >> 8) & 0x00FF);
        data[36] = (uint8)(pTIIR_FiP16->coeffB[18] & 0x00FF);
        data[37] = (uint8)((pTIIR_FiP16->coeffB[18] >> 8) & 0x00FF);
        data[38] = (uint8)(pTIIR_FiP16->coeffB[19] & 0x00FF);
        data[39] = (uint8)((pTIIR_FiP16->coeffB[19] >> 8) & 0x00FF);
        data[40] = (uint8)(pTIIR_FiP16->coeffB[20] & 0x00FF);
        data[41] = (uint8)((pTIIR_FiP16->coeffB[20] >> 8) & 0x00FF);
        data[42] = (uint8)(pTIIR_FiP16->coeffB[21] & 0x00FF);
        data[43] = (uint8)((pTIIR_FiP16->coeffB[21] >> 8) & 0x00FF);
        data[44] = (uint8)(pTIIR_FiP16->coeffB[22] & 0x00FF);
        data[45] = (uint8)((pTIIR_FiP16->coeffB[22] >> 8) & 0x00FF);
        data[46] = (uint8)(pTIIR_FiP16->coeffB[23] & 0x00FF);
        data[47] = (uint8)((pTIIR_FiP16->coeffB[23] >> 8) & 0x00FF);
        data[48] = (uint8)(pTIIR_FiP16->coeffB[24] & 0x00FF);
        data[49] = (uint8)((pTIIR_FiP16->coeffB[24] >> 8) & 0x00FF);
        data[50] = (uint8)(pTIIR_FiP16->coeffB[25] & 0x00FF);
        data[51] = (uint8)((pTIIR_FiP16->coeffB[25] >> 8) & 0x00FF);
        data[52] = (uint8)(pTIIR_FiP16->coeffB[26] & 0x00FF);
        data[53] = (uint8)((pTIIR_FiP16->coeffB[26] >> 8) & 0x00FF);
        data[54] = (uint8)(pTIIR_FiP16->coeffB[27] & 0x00FF);
        data[55] = (uint8)((pTIIR_FiP16->coeffB[27] >> 8) & 0x00FF);
        data[56] = (uint8)(pTIIR_FiP16->coeffB[28] & 0x00FF);
        data[57] = (uint8)((pTIIR_FiP16->coeffB[28] >> 8) & 0x00FF);
        data[58] = (uint8)(pTIIR_FiP16->coeffB[29] & 0x00FF);
        data[59] = (uint8)((pTIIR_FiP16->coeffB[29] >> 8) & 0x00FF);
        data[60] = (uint8)(pTIIR_FiP16->coeffB[30] & 0x00FF);
        data[61] = (uint8)((pTIIR_FiP16->coeffB[30] >> 8) & 0x00FF);
        data[62] = (uint8)(pTIIR_FiP16->coeffB[31] & 0x00FF);
        data[63] = (uint8)((pTIIR_FiP16->coeffB[31] >> 8) & 0x00FF);
        data[64] = (uint8)(pTIIR_FiP16->coeffA[0] & 0x00FF);
        data[65] = (uint8)((pTIIR_FiP16->coeffA[0] >> 8) & 0x00FF);
        data[66] = (uint8)(pTIIR_FiP16->coeffA[1] & 0x00FF);
        data[67] = (uint8)((pTIIR_FiP16->coeffA[1] >> 8) & 0x00FF);
        data[68] = (uint8)(pTIIR_FiP16->coeffA[2] & 0x00FF);
        data[69] = (uint8)((pTIIR_FiP16->coeffA[2] >> 8) & 0x00FF);
        data[70] = (uint8)(pTIIR_FiP16->coeffA[3] & 0x00FF);
        data[71] = (uint8)((pTIIR_FiP16->coeffA[3] >> 8) & 0x00FF);
        data[72] = (uint8)(pTIIR_FiP16->coeffA[4] & 0x00FF);
        data[73] = (uint8)((pTIIR_FiP16->coeffA[4] >> 8) & 0x00FF);
        data[74] = (uint8)(pTIIR_FiP16->coeffA[5] & 0x00FF);
        data[75] = (uint8)((pTIIR_FiP16->coeffA[5] >> 8) & 0x00FF);
        data[76] = (uint8)(pTIIR_FiP16->coeffA[6] & 0x00FF);
        data[77] = (uint8)((pTIIR_FiP16->coeffA[6] >> 8) & 0x00FF);
        data[78] = (uint8)(pTIIR_FiP16->coeffA[7] & 0x00FF);
        data[79] = (uint8)((pTIIR_FiP16->coeffA[7] >> 8) & 0x00FF);
        data[80] = (uint8)(pTIIR_FiP16->coeffA[8] & 0x00FF);
        data[81] = (uint8)((pTIIR_FiP16->coeffA[8] >> 8) & 0x00FF);
        data[82] = (uint8)(pTIIR_FiP16->coeffA[9] & 0x00FF);
        data[83] = (uint8)((pTIIR_FiP16->coeffA[9] >> 8) & 0x00FF);
        data[84] = (uint8)(pTIIR_FiP16->coeffA[10] & 0x00FF);
        data[85] = (uint8)((pTIIR_FiP16->coeffA[10] >> 8) & 0x00FF);
        data[86] = (uint8)(pTIIR_FiP16->coeffA[11] & 0x00FF);
        data[87] = (uint8)((pTIIR_FiP16->coeffA[11] >> 8) & 0x00FF);
        data[88] = (uint8)(pTIIR_FiP16->coeffA[12] & 0x00FF);
        data[89] = (uint8)((pTIIR_FiP16->coeffA[12] >> 8) & 0x00FF);
        data[90] = (uint8)(pTIIR_FiP16->coeffA[13] & 0x00FF);
        data[91] = (uint8)((pTIIR_FiP16->coeffA[13] >> 8) & 0x00FF);
        data[92] = (uint8)(pTIIR_FiP16->coeffA[14] & 0x00FF);
        data[93] = (uint8)((pTIIR_FiP16->coeffA[14] >> 8) & 0x00FF);
        data[94] = (uint8)(pTIIR_FiP16->coeffA[15] & 0x00FF);
        data[95] = (uint8)((pTIIR_FiP16->coeffA[15] >> 8) & 0x00FF);
        data[96] = (uint8)(pTIIR_FiP16->coeffA[16] & 0x00FF);
        data[97] = (uint8)((pTIIR_FiP16->coeffA[16] >> 8) & 0x00FF);
        data[98] = (uint8)(pTIIR_FiP16->coeffA[17] & 0x00FF);
        data[99] = (uint8)((pTIIR_FiP16->coeffA[17] >> 8) & 0x00FF);
        data[100] = (uint8)(pTIIR_FiP16->coeffA[18] & 0x00FF);
        data[101] = (uint8)((pTIIR_FiP16->coeffA[18] >> 8) & 0x00FF);
        data[102] = (uint8)(pTIIR_FiP16->coeffA[19] & 0x00FF);
        data[103] = (uint8)((pTIIR_FiP16->coeffA[19] >> 8) & 0x00FF);
        data[104] = (uint8)(pTIIR_FiP16->coeffA[20] & 0x00FF);
        data[105] = (uint8)((pTIIR_FiP16->coeffA[20] >> 8) & 0x00FF);
        data[106] = (uint8)(pTIIR_FiP16->coeffA[21] & 0x00FF);
        data[107] = (uint8)((pTIIR_FiP16->coeffA[21] >> 8) & 0x00FF);
        data[108] = (uint8)(pTIIR_FiP16->coeffA[22] & 0x00FF);
        data[109] = (uint8)((pTIIR_FiP16->coeffA[22] >> 8) & 0x00FF);
        data[110] = (uint8)(pTIIR_FiP16->coeffA[23] & 0x00FF);
        data[111] = (uint8)((pTIIR_FiP16->coeffA[23] >> 8) & 0x00FF);
        data[112] = (uint8)(pTIIR_FiP16->coeffA[24] & 0x00FF);
        data[113] = (uint8)((pTIIR_FiP16->coeffA[24] >> 8) & 0x00FF);
        data[114] = (uint8)(pTIIR_FiP16->coeffA[25] & 0x00FF);
        data[115] = (uint8)((pTIIR_FiP16->coeffA[25] >> 8) & 0x00FF);
        data[116] = (uint8)(pTIIR_FiP16->coeffA[26] & 0x00FF);
        data[117] = (uint8)((pTIIR_FiP16->coeffA[26] >> 8) & 0x00FF);
        data[118] = (uint8)(pTIIR_FiP16->coeffA[27] & 0x00FF);
        data[119] = (uint8)((pTIIR_FiP16->coeffA[27] >> 8) & 0x00FF);
        data[120] = (uint8)(pTIIR_FiP16->coeffA[28] & 0x00FF);
        data[121] = (uint8)((pTIIR_FiP16->coeffA[28] >> 8) & 0x00FF);
        data[122] = (uint8)(pTIIR_FiP16->coeffA[29] & 0x00FF);
        data[123] = (uint8)((pTIIR_FiP16->coeffA[29] >> 8) & 0x00FF);
        data[124] = (uint8)(pTIIR_FiP16->coeffA[30] & 0x00FF);
        data[125] = (uint8)((pTIIR_FiP16->coeffA[30] >> 8) & 0x00FF);
        data[126] = (uint8)pTIIR_FiP16->sfrB;
        data[127] = (uint8)pTIIR_FiP16->sfrA;
        data[128] = (uint8)pTIIR_FiP16->orderN;
        data[129] = (uint8)pTIIR_FiP16->orderD;
        *dataLength = (uint16)130;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 IIR_FiP16_Save(IIR_FIP16 *pTIIR_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)130)
    {
        error = (uint8)1;
    }
    else
    {
        pTIIR_FiP16->coeffB[0] = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTIIR_FiP16->coeffB[1] = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTIIR_FiP16->coeffB[2] = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTIIR_FiP16->coeffB[3] = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTIIR_FiP16->coeffB[4] = UINT16_TO_INT16((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTIIR_FiP16->coeffB[5] = UINT16_TO_INT16((uint16)data[10] + \
            ((uint16)data[11] << 8));
        pTIIR_FiP16->coeffB[6] = UINT16_TO_INT16((uint16)data[12] + \
            ((uint16)data[13] << 8));
        pTIIR_FiP16->coeffB[7] = UINT16_TO_INT16((uint16)data[14] + \
            ((uint16)data[15] << 8));
        pTIIR_FiP16->coeffB[8] = UINT16_TO_INT16((uint16)data[16] + \
            ((uint16)data[17] << 8));
        pTIIR_FiP16->coeffB[9] = UINT16_TO_INT16((uint16)data[18] + \
            ((uint16)data[19] << 8));
        pTIIR_FiP16->coeffB[10] = UINT16_TO_INT16((uint16)data[20] + \
            ((uint16)data[21] << 8));
        pTIIR_FiP16->coeffB[11] = UINT16_TO_INT16((uint16)data[22] + \
            ((uint16)data[23] << 8));
        pTIIR_FiP16->coeffB[12] = UINT16_TO_INT16((uint16)data[24] + \
            ((uint16)data[25] << 8));
        pTIIR_FiP16->coeffB[13] = UINT16_TO_INT16((uint16)data[26] + \
            ((uint16)data[27] << 8));
        pTIIR_FiP16->coeffB[14] = UINT16_TO_INT16((uint16)data[28] + \
            ((uint16)data[29] << 8));
        pTIIR_FiP16->coeffB[15] = UINT16_TO_INT16((uint16)data[30] + \
            ((uint16)data[31] << 8));
        pTIIR_FiP16->coeffB[16] = UINT16_TO_INT16((uint16)data[32] + \
            ((uint16)data[33] << 8));
        pTIIR_FiP16->coeffB[17] = UINT16_TO_INT16((uint16)data[34] + \
            ((uint16)data[35] << 8));
        pTIIR_FiP16->coeffB[18] = UINT16_TO_INT16((uint16)data[36] + \
            ((uint16)data[37] << 8));
        pTIIR_FiP16->coeffB[19] = UINT16_TO_INT16((uint16)data[38] + \
            ((uint16)data[39] << 8));
        pTIIR_FiP16->coeffB[20] = UINT16_TO_INT16((uint16)data[40] + \
            ((uint16)data[41] << 8));
        pTIIR_FiP16->coeffB[21] = UINT16_TO_INT16((uint16)data[42] + \
            ((uint16)data[43] << 8));
        pTIIR_FiP16->coeffB[22] = UINT16_TO_INT16((uint16)data[44] + \
            ((uint16)data[45] << 8));
        pTIIR_FiP16->coeffB[23] = UINT16_TO_INT16((uint16)data[46] + \
            ((uint16)data[47] << 8));
        pTIIR_FiP16->coeffB[24] = UINT16_TO_INT16((uint16)data[48] + \
            ((uint16)data[49] << 8));
        pTIIR_FiP16->coeffB[25] = UINT16_TO_INT16((uint16)data[50] + \
            ((uint16)data[51] << 8));
        pTIIR_FiP16->coeffB[26] = UINT16_TO_INT16((uint16)data[52] + \
            ((uint16)data[53] << 8));
        pTIIR_FiP16->coeffB[27] = UINT16_TO_INT16((uint16)data[54] + \
            ((uint16)data[55] << 8));
        pTIIR_FiP16->coeffB[28] = UINT16_TO_INT16((uint16)data[56] + \
            ((uint16)data[57] << 8));
        pTIIR_FiP16->coeffB[29] = UINT16_TO_INT16((uint16)data[58] + \
            ((uint16)data[59] << 8));
        pTIIR_FiP16->coeffB[30] = UINT16_TO_INT16((uint16)data[60] + \
            ((uint16)data[61] << 8));
        pTIIR_FiP16->coeffB[31] = UINT16_TO_INT16((uint16)data[62] + \
            ((uint16)data[63] << 8));
        pTIIR_FiP16->coeffA[0] = UINT16_TO_INT16((uint16)data[64] + \
            ((uint16)data[65] << 8));
        pTIIR_FiP16->coeffA[1] = UINT16_TO_INT16((uint16)data[66] + \
            ((uint16)data[67] << 8));
        pTIIR_FiP16->coeffA[2] = UINT16_TO_INT16((uint16)data[68] + \
            ((uint16)data[69] << 8));
        pTIIR_FiP16->coeffA[3] = UINT16_TO_INT16((uint16)data[70] + \
            ((uint16)data[71] << 8));
        pTIIR_FiP16->coeffA[4] = UINT16_TO_INT16((uint16)data[72] + \
            ((uint16)data[73] << 8));
        pTIIR_FiP16->coeffA[5] = UINT16_TO_INT16((uint16)data[74] + \
            ((uint16)data[75] << 8));
        pTIIR_FiP16->coeffA[6] = UINT16_TO_INT16((uint16)data[76] + \
            ((uint16)data[77] << 8));
        pTIIR_FiP16->coeffA[7] = UINT16_TO_INT16((uint16)data[78] + \
            ((uint16)data[79] << 8));
        pTIIR_FiP16->coeffA[8] = UINT16_TO_INT16((uint16)data[80] + \
            ((uint16)data[81] << 8));
        pTIIR_FiP16->coeffA[9] = UINT16_TO_INT16((uint16)data[82] + \
            ((uint16)data[83] << 8));
        pTIIR_FiP16->coeffA[10] = UINT16_TO_INT16((uint16)data[84] + \
            ((uint16)data[85] << 8));
        pTIIR_FiP16->coeffA[11] = UINT16_TO_INT16((uint16)data[86] + \
            ((uint16)data[87] << 8));
        pTIIR_FiP16->coeffA[12] = UINT16_TO_INT16((uint16)data[88] + \
            ((uint16)data[89] << 8));
        pTIIR_FiP16->coeffA[13] = UINT16_TO_INT16((uint16)data[90] + \
            ((uint16)data[91] << 8));
        pTIIR_FiP16->coeffA[14] = UINT16_TO_INT16((uint16)data[92] + \
            ((uint16)data[93] << 8));
        pTIIR_FiP16->coeffA[15] = UINT16_TO_INT16((uint16)data[94] + \
            ((uint16)data[95] << 8));
        pTIIR_FiP16->coeffA[16] = UINT16_TO_INT16((uint16)data[96] + \
            ((uint16)data[97] << 8));
        pTIIR_FiP16->coeffA[17] = UINT16_TO_INT16((uint16)data[98] + \
            ((uint16)data[99] << 8));
        pTIIR_FiP16->coeffA[18] = UINT16_TO_INT16((uint16)data[100] + \
            ((uint16)data[101] << 8));
        pTIIR_FiP16->coeffA[19] = UINT16_TO_INT16((uint16)data[102] + \
            ((uint16)data[103] << 8));
        pTIIR_FiP16->coeffA[20] = UINT16_TO_INT16((uint16)data[104] + \
            ((uint16)data[105] << 8));
        pTIIR_FiP16->coeffA[21] = UINT16_TO_INT16((uint16)data[106] + \
            ((uint16)data[107] << 8));
        pTIIR_FiP16->coeffA[22] = UINT16_TO_INT16((uint16)data[108] + \
            ((uint16)data[109] << 8));
        pTIIR_FiP16->coeffA[23] = UINT16_TO_INT16((uint16)data[110] + \
            ((uint16)data[111] << 8));
        pTIIR_FiP16->coeffA[24] = UINT16_TO_INT16((uint16)data[112] + \
            ((uint16)data[113] << 8));
        pTIIR_FiP16->coeffA[25] = UINT16_TO_INT16((uint16)data[114] + \
            ((uint16)data[115] << 8));
        pTIIR_FiP16->coeffA[26] = UINT16_TO_INT16((uint16)data[116] + \
            ((uint16)data[117] << 8));
        pTIIR_FiP16->coeffA[27] = UINT16_TO_INT16((uint16)data[118] + \
            ((uint16)data[119] << 8));
        pTIIR_FiP16->coeffA[28] = UINT16_TO_INT16((uint16)data[120] + \
            ((uint16)data[121] << 8));
        pTIIR_FiP16->coeffA[29] = UINT16_TO_INT16((uint16)data[122] + \
            ((uint16)data[123] << 8));
        pTIIR_FiP16->coeffA[30] = UINT16_TO_INT16((uint16)data[124] + \
            ((uint16)data[125] << 8));
        pTIIR_FiP16->sfrB = UINT8_TO_INT8((uint8)data[126]);
        pTIIR_FiP16->sfrA = UINT8_TO_INT8((uint8)data[127]);
        pTIIR_FiP16->orderN = UINT8_TO_INT8((uint8)data[128]);
        pTIIR_FiP16->orderD = UINT8_TO_INT8((uint8)data[129]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(IIR_FIP16_ISLINKED)
void* IIR_FiP16_GetAddress(const IIR_FIP16* block, uint16 elementId)
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
