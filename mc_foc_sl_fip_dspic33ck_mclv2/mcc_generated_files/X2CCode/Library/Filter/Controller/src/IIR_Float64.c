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
#include "IIR_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(IIR_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			    (*pTIIR_Float64->In)

/* Outputs */
#define OUT			    (pTIIR_Float64->Out)

/* Parameter */
#define	COEFF_A			(pTIIR_Float64->coeffA)         /* Denominator coefficients array in reversed order (an,...,a2,a1) */
#define	COEFF_B			(pTIIR_Float64->coeffB)         /* Numerator coefficients array in reversed order (bn,...,b2,b1,b0) */
#define ORDER_N			(pTIIR_Float64->orderN)         /* Length of numerator coefficients array */
#define ORDER_D			(pTIIR_Float64->orderD)         /* Length of denominator coefficients array */

/* Variables */
#define BUFFER_IN       (pTIIR_Float64->inputBuffer)    /* Circular buffer for input signal */
#define BUFFER_OUT      (pTIIR_Float64->outputBuffer)   /* Circular buffer for output signal */
#define IDX_IN			(pTIIR_Float64->indexIn)        /* Pointer to current position in input buffer */
#define IDX_OUT			(pTIIR_Float64->indexOut)       /* Pointer to current position in output buffer */

/* Constants */
#define BUFFER_LEN      (32)                            /* Maximum length of circular buffer */
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void IIR_Float64_Update(IIR_FLOAT64 *pTIIR_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8 i;
	float64 sumA = 0, sumB = 0;

    /* enter In(k) and Out(k-1) in circular buffer */
    BUFFER_IN[IDX_IN]   = IN;
    BUFFER_OUT[IDX_OUT] = OUT;

    /* increase pointers to circular buffers */
	IDX_IN  = (IDX_IN  + 1) % ORDER_N;  /* pointer to element k-N */
	IDX_OUT = (IDX_OUT + 1) % ORDER_D;  /* pointer to element k-D */

    /* calculate sums of numerator and denominator */
    for (i=0; i < ORDER_N; i++)
    {
        sumB += (COEFF_B[i] * BUFFER_IN[(IDX_IN + i) % ORDER_N]);
		sumA += (COEFF_A[i] * BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
	}
    for (i=ORDER_N; i < ORDER_D; i++)
    {
        sumA += (COEFF_A[i] * BUFFER_OUT[(IDX_OUT + i) % ORDER_D]);
    }
    
    /* calculate total sum and assign output */
	OUT = sumB - sumA;
    
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void IIR_Float64_Init(IIR_FLOAT64 *pTIIR_Float64)
{
    pTIIR_Float64->ID = IIR_FLOAT64_ID;
    pTIIR_Float64->Out = 0;
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
uint8 IIR_Float64_Load(const IIR_FLOAT64 *pTIIR_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)506 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0])) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[0]) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1])) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[1]) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2])) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[2]) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3])) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[3]) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4])) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[4]) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5])) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[5]) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6])) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[6]) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7])) & 0x00000000000000FF);
        data[57] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 8) & 0x00000000000000FF);
        data[58] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 16) & 0x00000000000000FF);
        data[59] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 24) & 0x00000000000000FF);
        data[60] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 32) & 0x00000000000000FF);
        data[61] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 40) & 0x00000000000000FF);
        data[62] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 48) & 0x00000000000000FF);
        data[63] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[7]) >> 56) & 0x00000000000000FF);
        data[64] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8])) & 0x00000000000000FF);
        data[65] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 8) & 0x00000000000000FF);
        data[66] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 16) & 0x00000000000000FF);
        data[67] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 24) & 0x00000000000000FF);
        data[68] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 32) & 0x00000000000000FF);
        data[69] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 40) & 0x00000000000000FF);
        data[70] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 48) & 0x00000000000000FF);
        data[71] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[8]) >> 56) & 0x00000000000000FF);
        data[72] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9])) & 0x00000000000000FF);
        data[73] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 8) & 0x00000000000000FF);
        data[74] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 16) & 0x00000000000000FF);
        data[75] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 24) & 0x00000000000000FF);
        data[76] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 32) & 0x00000000000000FF);
        data[77] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 40) & 0x00000000000000FF);
        data[78] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 48) & 0x00000000000000FF);
        data[79] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[9]) >> 56) & 0x00000000000000FF);
        data[80] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10])) & 0x00000000000000FF);
        data[81] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 8) & 0x00000000000000FF);
        data[82] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 16) & 0x00000000000000FF);
        data[83] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 24) & 0x00000000000000FF);
        data[84] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 32) & 0x00000000000000FF);
        data[85] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 40) & 0x00000000000000FF);
        data[86] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 48) & 0x00000000000000FF);
        data[87] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[10]) >> 56) & 0x00000000000000FF);
        data[88] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11])) & 0x00000000000000FF);
        data[89] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 8) & 0x00000000000000FF);
        data[90] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 16) & 0x00000000000000FF);
        data[91] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 24) & 0x00000000000000FF);
        data[92] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 32) & 0x00000000000000FF);
        data[93] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 40) & 0x00000000000000FF);
        data[94] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 48) & 0x00000000000000FF);
        data[95] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[11]) >> 56) & 0x00000000000000FF);
        data[96] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12])) & 0x00000000000000FF);
        data[97] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 8) & 0x00000000000000FF);
        data[98] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 16) & 0x00000000000000FF);
        data[99] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 24) & 0x00000000000000FF);
        data[100] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 32) & 0x00000000000000FF);
        data[101] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 40) & 0x00000000000000FF);
        data[102] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 48) & 0x00000000000000FF);
        data[103] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[12]) >> 56) & 0x00000000000000FF);
        data[104] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13])) & 0x00000000000000FF);
        data[105] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 8) & 0x00000000000000FF);
        data[106] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 16) & 0x00000000000000FF);
        data[107] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 24) & 0x00000000000000FF);
        data[108] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 32) & 0x00000000000000FF);
        data[109] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 40) & 0x00000000000000FF);
        data[110] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 48) & 0x00000000000000FF);
        data[111] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[13]) >> 56) & 0x00000000000000FF);
        data[112] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14])) & 0x00000000000000FF);
        data[113] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 8) & 0x00000000000000FF);
        data[114] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 16) & 0x00000000000000FF);
        data[115] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 24) & 0x00000000000000FF);
        data[116] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 32) & 0x00000000000000FF);
        data[117] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 40) & 0x00000000000000FF);
        data[118] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 48) & 0x00000000000000FF);
        data[119] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[14]) >> 56) & 0x00000000000000FF);
        data[120] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15])) & 0x00000000000000FF);
        data[121] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 8) & 0x00000000000000FF);
        data[122] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 16) & 0x00000000000000FF);
        data[123] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 24) & 0x00000000000000FF);
        data[124] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 32) & 0x00000000000000FF);
        data[125] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 40) & 0x00000000000000FF);
        data[126] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 48) & 0x00000000000000FF);
        data[127] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[15]) >> 56) & 0x00000000000000FF);
        data[128] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16])) & 0x00000000000000FF);
        data[129] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 8) & 0x00000000000000FF);
        data[130] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 16) & 0x00000000000000FF);
        data[131] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 24) & 0x00000000000000FF);
        data[132] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 32) & 0x00000000000000FF);
        data[133] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 40) & 0x00000000000000FF);
        data[134] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 48) & 0x00000000000000FF);
        data[135] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[16]) >> 56) & 0x00000000000000FF);
        data[136] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17])) & 0x00000000000000FF);
        data[137] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 8) & 0x00000000000000FF);
        data[138] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 16) & 0x00000000000000FF);
        data[139] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 24) & 0x00000000000000FF);
        data[140] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 32) & 0x00000000000000FF);
        data[141] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 40) & 0x00000000000000FF);
        data[142] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 48) & 0x00000000000000FF);
        data[143] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[17]) >> 56) & 0x00000000000000FF);
        data[144] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18])) & 0x00000000000000FF);
        data[145] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 8) & 0x00000000000000FF);
        data[146] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 16) & 0x00000000000000FF);
        data[147] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 24) & 0x00000000000000FF);
        data[148] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 32) & 0x00000000000000FF);
        data[149] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 40) & 0x00000000000000FF);
        data[150] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 48) & 0x00000000000000FF);
        data[151] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[18]) >> 56) & 0x00000000000000FF);
        data[152] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19])) & 0x00000000000000FF);
        data[153] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 8) & 0x00000000000000FF);
        data[154] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 16) & 0x00000000000000FF);
        data[155] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 24) & 0x00000000000000FF);
        data[156] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 32) & 0x00000000000000FF);
        data[157] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 40) & 0x00000000000000FF);
        data[158] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 48) & 0x00000000000000FF);
        data[159] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[19]) >> 56) & 0x00000000000000FF);
        data[160] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20])) & 0x00000000000000FF);
        data[161] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 8) & 0x00000000000000FF);
        data[162] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 16) & 0x00000000000000FF);
        data[163] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 24) & 0x00000000000000FF);
        data[164] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 32) & 0x00000000000000FF);
        data[165] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 40) & 0x00000000000000FF);
        data[166] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 48) & 0x00000000000000FF);
        data[167] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[20]) >> 56) & 0x00000000000000FF);
        data[168] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21])) & 0x00000000000000FF);
        data[169] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 8) & 0x00000000000000FF);
        data[170] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 16) & 0x00000000000000FF);
        data[171] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 24) & 0x00000000000000FF);
        data[172] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 32) & 0x00000000000000FF);
        data[173] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 40) & 0x00000000000000FF);
        data[174] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 48) & 0x00000000000000FF);
        data[175] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[21]) >> 56) & 0x00000000000000FF);
        data[176] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22])) & 0x00000000000000FF);
        data[177] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 8) & 0x00000000000000FF);
        data[178] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 16) & 0x00000000000000FF);
        data[179] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 24) & 0x00000000000000FF);
        data[180] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 32) & 0x00000000000000FF);
        data[181] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 40) & 0x00000000000000FF);
        data[182] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 48) & 0x00000000000000FF);
        data[183] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[22]) >> 56) & 0x00000000000000FF);
        data[184] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23])) & 0x00000000000000FF);
        data[185] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 8) & 0x00000000000000FF);
        data[186] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 16) & 0x00000000000000FF);
        data[187] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 24) & 0x00000000000000FF);
        data[188] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 32) & 0x00000000000000FF);
        data[189] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 40) & 0x00000000000000FF);
        data[190] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 48) & 0x00000000000000FF);
        data[191] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[23]) >> 56) & 0x00000000000000FF);
        data[192] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24])) & 0x00000000000000FF);
        data[193] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 8) & 0x00000000000000FF);
        data[194] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 16) & 0x00000000000000FF);
        data[195] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 24) & 0x00000000000000FF);
        data[196] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 32) & 0x00000000000000FF);
        data[197] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 40) & 0x00000000000000FF);
        data[198] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 48) & 0x00000000000000FF);
        data[199] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[24]) >> 56) & 0x00000000000000FF);
        data[200] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25])) & 0x00000000000000FF);
        data[201] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 8) & 0x00000000000000FF);
        data[202] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 16) & 0x00000000000000FF);
        data[203] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 24) & 0x00000000000000FF);
        data[204] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 32) & 0x00000000000000FF);
        data[205] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 40) & 0x00000000000000FF);
        data[206] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 48) & 0x00000000000000FF);
        data[207] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[25]) >> 56) & 0x00000000000000FF);
        data[208] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26])) & 0x00000000000000FF);
        data[209] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 8) & 0x00000000000000FF);
        data[210] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 16) & 0x00000000000000FF);
        data[211] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 24) & 0x00000000000000FF);
        data[212] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 32) & 0x00000000000000FF);
        data[213] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 40) & 0x00000000000000FF);
        data[214] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 48) & 0x00000000000000FF);
        data[215] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[26]) >> 56) & 0x00000000000000FF);
        data[216] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27])) & 0x00000000000000FF);
        data[217] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 8) & 0x00000000000000FF);
        data[218] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 16) & 0x00000000000000FF);
        data[219] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 24) & 0x00000000000000FF);
        data[220] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 32) & 0x00000000000000FF);
        data[221] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 40) & 0x00000000000000FF);
        data[222] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 48) & 0x00000000000000FF);
        data[223] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[27]) >> 56) & 0x00000000000000FF);
        data[224] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28])) & 0x00000000000000FF);
        data[225] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 8) & 0x00000000000000FF);
        data[226] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 16) & 0x00000000000000FF);
        data[227] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 24) & 0x00000000000000FF);
        data[228] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 32) & 0x00000000000000FF);
        data[229] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 40) & 0x00000000000000FF);
        data[230] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 48) & 0x00000000000000FF);
        data[231] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[28]) >> 56) & 0x00000000000000FF);
        data[232] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29])) & 0x00000000000000FF);
        data[233] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 8) & 0x00000000000000FF);
        data[234] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 16) & 0x00000000000000FF);
        data[235] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 24) & 0x00000000000000FF);
        data[236] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 32) & 0x00000000000000FF);
        data[237] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 40) & 0x00000000000000FF);
        data[238] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 48) & 0x00000000000000FF);
        data[239] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[29]) >> 56) & 0x00000000000000FF);
        data[240] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30])) & 0x00000000000000FF);
        data[241] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 8) & 0x00000000000000FF);
        data[242] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 16) & 0x00000000000000FF);
        data[243] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 24) & 0x00000000000000FF);
        data[244] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 32) & 0x00000000000000FF);
        data[245] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 40) & 0x00000000000000FF);
        data[246] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 48) & 0x00000000000000FF);
        data[247] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[30]) >> 56) & 0x00000000000000FF);
        data[248] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31])) & 0x00000000000000FF);
        data[249] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 8) & 0x00000000000000FF);
        data[250] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 16) & 0x00000000000000FF);
        data[251] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 24) & 0x00000000000000FF);
        data[252] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 32) & 0x00000000000000FF);
        data[253] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 40) & 0x00000000000000FF);
        data[254] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 48) & 0x00000000000000FF);
        data[255] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffB[31]) >> 56) & 0x00000000000000FF);
        data[256] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0])) & 0x00000000000000FF);
        data[257] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 8) & 0x00000000000000FF);
        data[258] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 16) & 0x00000000000000FF);
        data[259] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 24) & 0x00000000000000FF);
        data[260] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 32) & 0x00000000000000FF);
        data[261] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 40) & 0x00000000000000FF);
        data[262] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 48) & 0x00000000000000FF);
        data[263] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[0]) >> 56) & 0x00000000000000FF);
        data[264] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1])) & 0x00000000000000FF);
        data[265] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 8) & 0x00000000000000FF);
        data[266] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 16) & 0x00000000000000FF);
        data[267] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 24) & 0x00000000000000FF);
        data[268] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 32) & 0x00000000000000FF);
        data[269] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 40) & 0x00000000000000FF);
        data[270] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 48) & 0x00000000000000FF);
        data[271] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[1]) >> 56) & 0x00000000000000FF);
        data[272] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2])) & 0x00000000000000FF);
        data[273] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 8) & 0x00000000000000FF);
        data[274] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 16) & 0x00000000000000FF);
        data[275] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 24) & 0x00000000000000FF);
        data[276] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 32) & 0x00000000000000FF);
        data[277] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 40) & 0x00000000000000FF);
        data[278] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 48) & 0x00000000000000FF);
        data[279] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[2]) >> 56) & 0x00000000000000FF);
        data[280] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3])) & 0x00000000000000FF);
        data[281] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 8) & 0x00000000000000FF);
        data[282] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 16) & 0x00000000000000FF);
        data[283] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 24) & 0x00000000000000FF);
        data[284] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 32) & 0x00000000000000FF);
        data[285] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 40) & 0x00000000000000FF);
        data[286] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 48) & 0x00000000000000FF);
        data[287] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[3]) >> 56) & 0x00000000000000FF);
        data[288] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4])) & 0x00000000000000FF);
        data[289] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 8) & 0x00000000000000FF);
        data[290] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 16) & 0x00000000000000FF);
        data[291] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 24) & 0x00000000000000FF);
        data[292] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 32) & 0x00000000000000FF);
        data[293] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 40) & 0x00000000000000FF);
        data[294] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 48) & 0x00000000000000FF);
        data[295] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[4]) >> 56) & 0x00000000000000FF);
        data[296] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5])) & 0x00000000000000FF);
        data[297] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 8) & 0x00000000000000FF);
        data[298] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 16) & 0x00000000000000FF);
        data[299] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 24) & 0x00000000000000FF);
        data[300] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 32) & 0x00000000000000FF);
        data[301] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 40) & 0x00000000000000FF);
        data[302] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 48) & 0x00000000000000FF);
        data[303] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[5]) >> 56) & 0x00000000000000FF);
        data[304] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6])) & 0x00000000000000FF);
        data[305] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 8) & 0x00000000000000FF);
        data[306] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 16) & 0x00000000000000FF);
        data[307] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 24) & 0x00000000000000FF);
        data[308] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 32) & 0x00000000000000FF);
        data[309] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 40) & 0x00000000000000FF);
        data[310] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 48) & 0x00000000000000FF);
        data[311] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[6]) >> 56) & 0x00000000000000FF);
        data[312] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7])) & 0x00000000000000FF);
        data[313] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 8) & 0x00000000000000FF);
        data[314] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 16) & 0x00000000000000FF);
        data[315] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 24) & 0x00000000000000FF);
        data[316] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 32) & 0x00000000000000FF);
        data[317] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 40) & 0x00000000000000FF);
        data[318] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 48) & 0x00000000000000FF);
        data[319] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[7]) >> 56) & 0x00000000000000FF);
        data[320] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8])) & 0x00000000000000FF);
        data[321] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 8) & 0x00000000000000FF);
        data[322] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 16) & 0x00000000000000FF);
        data[323] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 24) & 0x00000000000000FF);
        data[324] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 32) & 0x00000000000000FF);
        data[325] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 40) & 0x00000000000000FF);
        data[326] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 48) & 0x00000000000000FF);
        data[327] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[8]) >> 56) & 0x00000000000000FF);
        data[328] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9])) & 0x00000000000000FF);
        data[329] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 8) & 0x00000000000000FF);
        data[330] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 16) & 0x00000000000000FF);
        data[331] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 24) & 0x00000000000000FF);
        data[332] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 32) & 0x00000000000000FF);
        data[333] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 40) & 0x00000000000000FF);
        data[334] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 48) & 0x00000000000000FF);
        data[335] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[9]) >> 56) & 0x00000000000000FF);
        data[336] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10])) & 0x00000000000000FF);
        data[337] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 8) & 0x00000000000000FF);
        data[338] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 16) & 0x00000000000000FF);
        data[339] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 24) & 0x00000000000000FF);
        data[340] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 32) & 0x00000000000000FF);
        data[341] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 40) & 0x00000000000000FF);
        data[342] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 48) & 0x00000000000000FF);
        data[343] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[10]) >> 56) & 0x00000000000000FF);
        data[344] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11])) & 0x00000000000000FF);
        data[345] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 8) & 0x00000000000000FF);
        data[346] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 16) & 0x00000000000000FF);
        data[347] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 24) & 0x00000000000000FF);
        data[348] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 32) & 0x00000000000000FF);
        data[349] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 40) & 0x00000000000000FF);
        data[350] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 48) & 0x00000000000000FF);
        data[351] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[11]) >> 56) & 0x00000000000000FF);
        data[352] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12])) & 0x00000000000000FF);
        data[353] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 8) & 0x00000000000000FF);
        data[354] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 16) & 0x00000000000000FF);
        data[355] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 24) & 0x00000000000000FF);
        data[356] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 32) & 0x00000000000000FF);
        data[357] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 40) & 0x00000000000000FF);
        data[358] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 48) & 0x00000000000000FF);
        data[359] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[12]) >> 56) & 0x00000000000000FF);
        data[360] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13])) & 0x00000000000000FF);
        data[361] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 8) & 0x00000000000000FF);
        data[362] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 16) & 0x00000000000000FF);
        data[363] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 24) & 0x00000000000000FF);
        data[364] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 32) & 0x00000000000000FF);
        data[365] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 40) & 0x00000000000000FF);
        data[366] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 48) & 0x00000000000000FF);
        data[367] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[13]) >> 56) & 0x00000000000000FF);
        data[368] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14])) & 0x00000000000000FF);
        data[369] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 8) & 0x00000000000000FF);
        data[370] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 16) & 0x00000000000000FF);
        data[371] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 24) & 0x00000000000000FF);
        data[372] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 32) & 0x00000000000000FF);
        data[373] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 40) & 0x00000000000000FF);
        data[374] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 48) & 0x00000000000000FF);
        data[375] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[14]) >> 56) & 0x00000000000000FF);
        data[376] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15])) & 0x00000000000000FF);
        data[377] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 8) & 0x00000000000000FF);
        data[378] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 16) & 0x00000000000000FF);
        data[379] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 24) & 0x00000000000000FF);
        data[380] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 32) & 0x00000000000000FF);
        data[381] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 40) & 0x00000000000000FF);
        data[382] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 48) & 0x00000000000000FF);
        data[383] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[15]) >> 56) & 0x00000000000000FF);
        data[384] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16])) & 0x00000000000000FF);
        data[385] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 8) & 0x00000000000000FF);
        data[386] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 16) & 0x00000000000000FF);
        data[387] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 24) & 0x00000000000000FF);
        data[388] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 32) & 0x00000000000000FF);
        data[389] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 40) & 0x00000000000000FF);
        data[390] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 48) & 0x00000000000000FF);
        data[391] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[16]) >> 56) & 0x00000000000000FF);
        data[392] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17])) & 0x00000000000000FF);
        data[393] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 8) & 0x00000000000000FF);
        data[394] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 16) & 0x00000000000000FF);
        data[395] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 24) & 0x00000000000000FF);
        data[396] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 32) & 0x00000000000000FF);
        data[397] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 40) & 0x00000000000000FF);
        data[398] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 48) & 0x00000000000000FF);
        data[399] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[17]) >> 56) & 0x00000000000000FF);
        data[400] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18])) & 0x00000000000000FF);
        data[401] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 8) & 0x00000000000000FF);
        data[402] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 16) & 0x00000000000000FF);
        data[403] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 24) & 0x00000000000000FF);
        data[404] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 32) & 0x00000000000000FF);
        data[405] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 40) & 0x00000000000000FF);
        data[406] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 48) & 0x00000000000000FF);
        data[407] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[18]) >> 56) & 0x00000000000000FF);
        data[408] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19])) & 0x00000000000000FF);
        data[409] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 8) & 0x00000000000000FF);
        data[410] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 16) & 0x00000000000000FF);
        data[411] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 24) & 0x00000000000000FF);
        data[412] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 32) & 0x00000000000000FF);
        data[413] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 40) & 0x00000000000000FF);
        data[414] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 48) & 0x00000000000000FF);
        data[415] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[19]) >> 56) & 0x00000000000000FF);
        data[416] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20])) & 0x00000000000000FF);
        data[417] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 8) & 0x00000000000000FF);
        data[418] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 16) & 0x00000000000000FF);
        data[419] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 24) & 0x00000000000000FF);
        data[420] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 32) & 0x00000000000000FF);
        data[421] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 40) & 0x00000000000000FF);
        data[422] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 48) & 0x00000000000000FF);
        data[423] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[20]) >> 56) & 0x00000000000000FF);
        data[424] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21])) & 0x00000000000000FF);
        data[425] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 8) & 0x00000000000000FF);
        data[426] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 16) & 0x00000000000000FF);
        data[427] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 24) & 0x00000000000000FF);
        data[428] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 32) & 0x00000000000000FF);
        data[429] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 40) & 0x00000000000000FF);
        data[430] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 48) & 0x00000000000000FF);
        data[431] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[21]) >> 56) & 0x00000000000000FF);
        data[432] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22])) & 0x00000000000000FF);
        data[433] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 8) & 0x00000000000000FF);
        data[434] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 16) & 0x00000000000000FF);
        data[435] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 24) & 0x00000000000000FF);
        data[436] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 32) & 0x00000000000000FF);
        data[437] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 40) & 0x00000000000000FF);
        data[438] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 48) & 0x00000000000000FF);
        data[439] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[22]) >> 56) & 0x00000000000000FF);
        data[440] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23])) & 0x00000000000000FF);
        data[441] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 8) & 0x00000000000000FF);
        data[442] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 16) & 0x00000000000000FF);
        data[443] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 24) & 0x00000000000000FF);
        data[444] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 32) & 0x00000000000000FF);
        data[445] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 40) & 0x00000000000000FF);
        data[446] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 48) & 0x00000000000000FF);
        data[447] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[23]) >> 56) & 0x00000000000000FF);
        data[448] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24])) & 0x00000000000000FF);
        data[449] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 8) & 0x00000000000000FF);
        data[450] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 16) & 0x00000000000000FF);
        data[451] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 24) & 0x00000000000000FF);
        data[452] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 32) & 0x00000000000000FF);
        data[453] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 40) & 0x00000000000000FF);
        data[454] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 48) & 0x00000000000000FF);
        data[455] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[24]) >> 56) & 0x00000000000000FF);
        data[456] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25])) & 0x00000000000000FF);
        data[457] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 8) & 0x00000000000000FF);
        data[458] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 16) & 0x00000000000000FF);
        data[459] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 24) & 0x00000000000000FF);
        data[460] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 32) & 0x00000000000000FF);
        data[461] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 40) & 0x00000000000000FF);
        data[462] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 48) & 0x00000000000000FF);
        data[463] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[25]) >> 56) & 0x00000000000000FF);
        data[464] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26])) & 0x00000000000000FF);
        data[465] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 8) & 0x00000000000000FF);
        data[466] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 16) & 0x00000000000000FF);
        data[467] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 24) & 0x00000000000000FF);
        data[468] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 32) & 0x00000000000000FF);
        data[469] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 40) & 0x00000000000000FF);
        data[470] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 48) & 0x00000000000000FF);
        data[471] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[26]) >> 56) & 0x00000000000000FF);
        data[472] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27])) & 0x00000000000000FF);
        data[473] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 8) & 0x00000000000000FF);
        data[474] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 16) & 0x00000000000000FF);
        data[475] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 24) & 0x00000000000000FF);
        data[476] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 32) & 0x00000000000000FF);
        data[477] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 40) & 0x00000000000000FF);
        data[478] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 48) & 0x00000000000000FF);
        data[479] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[27]) >> 56) & 0x00000000000000FF);
        data[480] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28])) & 0x00000000000000FF);
        data[481] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 8) & 0x00000000000000FF);
        data[482] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 16) & 0x00000000000000FF);
        data[483] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 24) & 0x00000000000000FF);
        data[484] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 32) & 0x00000000000000FF);
        data[485] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 40) & 0x00000000000000FF);
        data[486] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 48) & 0x00000000000000FF);
        data[487] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[28]) >> 56) & 0x00000000000000FF);
        data[488] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29])) & 0x00000000000000FF);
        data[489] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 8) & 0x00000000000000FF);
        data[490] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 16) & 0x00000000000000FF);
        data[491] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 24) & 0x00000000000000FF);
        data[492] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 32) & 0x00000000000000FF);
        data[493] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 40) & 0x00000000000000FF);
        data[494] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 48) & 0x00000000000000FF);
        data[495] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[29]) >> 56) & 0x00000000000000FF);
        data[496] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30])) & 0x00000000000000FF);
        data[497] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 8) & 0x00000000000000FF);
        data[498] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 16) & 0x00000000000000FF);
        data[499] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 24) & 0x00000000000000FF);
        data[500] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 32) & 0x00000000000000FF);
        data[501] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 40) & 0x00000000000000FF);
        data[502] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 48) & 0x00000000000000FF);
        data[503] = (uint8)((*(uint64*)&(pTIIR_Float64->coeffA[30]) >> 56) & 0x00000000000000FF);
        data[504] = (uint8)pTIIR_Float64->orderN;
        data[505] = (uint8)pTIIR_Float64->orderD;
        *dataLength = (uint16)506;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 IIR_Float64_Save(IIR_FLOAT64 *pTIIR_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)506)
    {
        error = (uint8)1;
    }
    else
    {
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        pTIIR_Float64->coeffB[0] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTIIR_Float64->coeffB[1] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTIIR_Float64->coeffB[2] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTIIR_Float64->coeffB[3] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        pTIIR_Float64->coeffB[4] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        pTIIR_Float64->coeffB[5] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        pTIIR_Float64->coeffB[6] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[56] + \
            ((uint64)data[57] << 8) + ((uint64)data[58] << 16) + \
            ((uint64)data[59] << 24) + ((uint64)data[60] << 32) + \
            ((uint64)data[61] << 40) + ((uint64)data[62] << 48) + \
            ((uint64)data[63] << 56);
        pTIIR_Float64->coeffB[7] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[64] + \
            ((uint64)data[65] << 8) + ((uint64)data[66] << 16) + \
            ((uint64)data[67] << 24) + ((uint64)data[68] << 32) + \
            ((uint64)data[69] << 40) + ((uint64)data[70] << 48) + \
            ((uint64)data[71] << 56);
        pTIIR_Float64->coeffB[8] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[72] + \
            ((uint64)data[73] << 8) + ((uint64)data[74] << 16) + \
            ((uint64)data[75] << 24) + ((uint64)data[76] << 32) + \
            ((uint64)data[77] << 40) + ((uint64)data[78] << 48) + \
            ((uint64)data[79] << 56);
        pTIIR_Float64->coeffB[9] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[80] + \
            ((uint64)data[81] << 8) + ((uint64)data[82] << 16) + \
            ((uint64)data[83] << 24) + ((uint64)data[84] << 32) + \
            ((uint64)data[85] << 40) + ((uint64)data[86] << 48) + \
            ((uint64)data[87] << 56);
        pTIIR_Float64->coeffB[10] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[88] + \
            ((uint64)data[89] << 8) + ((uint64)data[90] << 16) + \
            ((uint64)data[91] << 24) + ((uint64)data[92] << 32) + \
            ((uint64)data[93] << 40) + ((uint64)data[94] << 48) + \
            ((uint64)data[95] << 56);
        pTIIR_Float64->coeffB[11] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[96] + \
            ((uint64)data[97] << 8) + ((uint64)data[98] << 16) + \
            ((uint64)data[99] << 24) + ((uint64)data[100] << 32) + \
            ((uint64)data[101] << 40) + ((uint64)data[102] << 48) + \
            ((uint64)data[103] << 56);
        pTIIR_Float64->coeffB[12] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[104] + \
            ((uint64)data[105] << 8) + ((uint64)data[106] << 16) + \
            ((uint64)data[107] << 24) + ((uint64)data[108] << 32) + \
            ((uint64)data[109] << 40) + ((uint64)data[110] << 48) + \
            ((uint64)data[111] << 56);
        pTIIR_Float64->coeffB[13] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[112] + \
            ((uint64)data[113] << 8) + ((uint64)data[114] << 16) + \
            ((uint64)data[115] << 24) + ((uint64)data[116] << 32) + \
            ((uint64)data[117] << 40) + ((uint64)data[118] << 48) + \
            ((uint64)data[119] << 56);
        pTIIR_Float64->coeffB[14] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[120] + \
            ((uint64)data[121] << 8) + ((uint64)data[122] << 16) + \
            ((uint64)data[123] << 24) + ((uint64)data[124] << 32) + \
            ((uint64)data[125] << 40) + ((uint64)data[126] << 48) + \
            ((uint64)data[127] << 56);
        pTIIR_Float64->coeffB[15] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[128] + \
            ((uint64)data[129] << 8) + ((uint64)data[130] << 16) + \
            ((uint64)data[131] << 24) + ((uint64)data[132] << 32) + \
            ((uint64)data[133] << 40) + ((uint64)data[134] << 48) + \
            ((uint64)data[135] << 56);
        pTIIR_Float64->coeffB[16] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[136] + \
            ((uint64)data[137] << 8) + ((uint64)data[138] << 16) + \
            ((uint64)data[139] << 24) + ((uint64)data[140] << 32) + \
            ((uint64)data[141] << 40) + ((uint64)data[142] << 48) + \
            ((uint64)data[143] << 56);
        pTIIR_Float64->coeffB[17] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[144] + \
            ((uint64)data[145] << 8) + ((uint64)data[146] << 16) + \
            ((uint64)data[147] << 24) + ((uint64)data[148] << 32) + \
            ((uint64)data[149] << 40) + ((uint64)data[150] << 48) + \
            ((uint64)data[151] << 56);
        pTIIR_Float64->coeffB[18] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[152] + \
            ((uint64)data[153] << 8) + ((uint64)data[154] << 16) + \
            ((uint64)data[155] << 24) + ((uint64)data[156] << 32) + \
            ((uint64)data[157] << 40) + ((uint64)data[158] << 48) + \
            ((uint64)data[159] << 56);
        pTIIR_Float64->coeffB[19] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[160] + \
            ((uint64)data[161] << 8) + ((uint64)data[162] << 16) + \
            ((uint64)data[163] << 24) + ((uint64)data[164] << 32) + \
            ((uint64)data[165] << 40) + ((uint64)data[166] << 48) + \
            ((uint64)data[167] << 56);
        pTIIR_Float64->coeffB[20] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[168] + \
            ((uint64)data[169] << 8) + ((uint64)data[170] << 16) + \
            ((uint64)data[171] << 24) + ((uint64)data[172] << 32) + \
            ((uint64)data[173] << 40) + ((uint64)data[174] << 48) + \
            ((uint64)data[175] << 56);
        pTIIR_Float64->coeffB[21] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[176] + \
            ((uint64)data[177] << 8) + ((uint64)data[178] << 16) + \
            ((uint64)data[179] << 24) + ((uint64)data[180] << 32) + \
            ((uint64)data[181] << 40) + ((uint64)data[182] << 48) + \
            ((uint64)data[183] << 56);
        pTIIR_Float64->coeffB[22] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[184] + \
            ((uint64)data[185] << 8) + ((uint64)data[186] << 16) + \
            ((uint64)data[187] << 24) + ((uint64)data[188] << 32) + \
            ((uint64)data[189] << 40) + ((uint64)data[190] << 48) + \
            ((uint64)data[191] << 56);
        pTIIR_Float64->coeffB[23] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[192] + \
            ((uint64)data[193] << 8) + ((uint64)data[194] << 16) + \
            ((uint64)data[195] << 24) + ((uint64)data[196] << 32) + \
            ((uint64)data[197] << 40) + ((uint64)data[198] << 48) + \
            ((uint64)data[199] << 56);
        pTIIR_Float64->coeffB[24] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[200] + \
            ((uint64)data[201] << 8) + ((uint64)data[202] << 16) + \
            ((uint64)data[203] << 24) + ((uint64)data[204] << 32) + \
            ((uint64)data[205] << 40) + ((uint64)data[206] << 48) + \
            ((uint64)data[207] << 56);
        pTIIR_Float64->coeffB[25] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[208] + \
            ((uint64)data[209] << 8) + ((uint64)data[210] << 16) + \
            ((uint64)data[211] << 24) + ((uint64)data[212] << 32) + \
            ((uint64)data[213] << 40) + ((uint64)data[214] << 48) + \
            ((uint64)data[215] << 56);
        pTIIR_Float64->coeffB[26] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[216] + \
            ((uint64)data[217] << 8) + ((uint64)data[218] << 16) + \
            ((uint64)data[219] << 24) + ((uint64)data[220] << 32) + \
            ((uint64)data[221] << 40) + ((uint64)data[222] << 48) + \
            ((uint64)data[223] << 56);
        pTIIR_Float64->coeffB[27] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[224] + \
            ((uint64)data[225] << 8) + ((uint64)data[226] << 16) + \
            ((uint64)data[227] << 24) + ((uint64)data[228] << 32) + \
            ((uint64)data[229] << 40) + ((uint64)data[230] << 48) + \
            ((uint64)data[231] << 56);
        pTIIR_Float64->coeffB[28] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[232] + \
            ((uint64)data[233] << 8) + ((uint64)data[234] << 16) + \
            ((uint64)data[235] << 24) + ((uint64)data[236] << 32) + \
            ((uint64)data[237] << 40) + ((uint64)data[238] << 48) + \
            ((uint64)data[239] << 56);
        pTIIR_Float64->coeffB[29] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[240] + \
            ((uint64)data[241] << 8) + ((uint64)data[242] << 16) + \
            ((uint64)data[243] << 24) + ((uint64)data[244] << 32) + \
            ((uint64)data[245] << 40) + ((uint64)data[246] << 48) + \
            ((uint64)data[247] << 56);
        pTIIR_Float64->coeffB[30] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[248] + \
            ((uint64)data[249] << 8) + ((uint64)data[250] << 16) + \
            ((uint64)data[251] << 24) + ((uint64)data[252] << 32) + \
            ((uint64)data[253] << 40) + ((uint64)data[254] << 48) + \
            ((uint64)data[255] << 56);
        pTIIR_Float64->coeffB[31] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[256] + \
            ((uint64)data[257] << 8) + ((uint64)data[258] << 16) + \
            ((uint64)data[259] << 24) + ((uint64)data[260] << 32) + \
            ((uint64)data[261] << 40) + ((uint64)data[262] << 48) + \
            ((uint64)data[263] << 56);
        pTIIR_Float64->coeffA[0] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[264] + \
            ((uint64)data[265] << 8) + ((uint64)data[266] << 16) + \
            ((uint64)data[267] << 24) + ((uint64)data[268] << 32) + \
            ((uint64)data[269] << 40) + ((uint64)data[270] << 48) + \
            ((uint64)data[271] << 56);
        pTIIR_Float64->coeffA[1] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[272] + \
            ((uint64)data[273] << 8) + ((uint64)data[274] << 16) + \
            ((uint64)data[275] << 24) + ((uint64)data[276] << 32) + \
            ((uint64)data[277] << 40) + ((uint64)data[278] << 48) + \
            ((uint64)data[279] << 56);
        pTIIR_Float64->coeffA[2] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[280] + \
            ((uint64)data[281] << 8) + ((uint64)data[282] << 16) + \
            ((uint64)data[283] << 24) + ((uint64)data[284] << 32) + \
            ((uint64)data[285] << 40) + ((uint64)data[286] << 48) + \
            ((uint64)data[287] << 56);
        pTIIR_Float64->coeffA[3] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[288] + \
            ((uint64)data[289] << 8) + ((uint64)data[290] << 16) + \
            ((uint64)data[291] << 24) + ((uint64)data[292] << 32) + \
            ((uint64)data[293] << 40) + ((uint64)data[294] << 48) + \
            ((uint64)data[295] << 56);
        pTIIR_Float64->coeffA[4] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[296] + \
            ((uint64)data[297] << 8) + ((uint64)data[298] << 16) + \
            ((uint64)data[299] << 24) + ((uint64)data[300] << 32) + \
            ((uint64)data[301] << 40) + ((uint64)data[302] << 48) + \
            ((uint64)data[303] << 56);
        pTIIR_Float64->coeffA[5] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[304] + \
            ((uint64)data[305] << 8) + ((uint64)data[306] << 16) + \
            ((uint64)data[307] << 24) + ((uint64)data[308] << 32) + \
            ((uint64)data[309] << 40) + ((uint64)data[310] << 48) + \
            ((uint64)data[311] << 56);
        pTIIR_Float64->coeffA[6] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[312] + \
            ((uint64)data[313] << 8) + ((uint64)data[314] << 16) + \
            ((uint64)data[315] << 24) + ((uint64)data[316] << 32) + \
            ((uint64)data[317] << 40) + ((uint64)data[318] << 48) + \
            ((uint64)data[319] << 56);
        pTIIR_Float64->coeffA[7] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[320] + \
            ((uint64)data[321] << 8) + ((uint64)data[322] << 16) + \
            ((uint64)data[323] << 24) + ((uint64)data[324] << 32) + \
            ((uint64)data[325] << 40) + ((uint64)data[326] << 48) + \
            ((uint64)data[327] << 56);
        pTIIR_Float64->coeffA[8] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[328] + \
            ((uint64)data[329] << 8) + ((uint64)data[330] << 16) + \
            ((uint64)data[331] << 24) + ((uint64)data[332] << 32) + \
            ((uint64)data[333] << 40) + ((uint64)data[334] << 48) + \
            ((uint64)data[335] << 56);
        pTIIR_Float64->coeffA[9] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[336] + \
            ((uint64)data[337] << 8) + ((uint64)data[338] << 16) + \
            ((uint64)data[339] << 24) + ((uint64)data[340] << 32) + \
            ((uint64)data[341] << 40) + ((uint64)data[342] << 48) + \
            ((uint64)data[343] << 56);
        pTIIR_Float64->coeffA[10] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[344] + \
            ((uint64)data[345] << 8) + ((uint64)data[346] << 16) + \
            ((uint64)data[347] << 24) + ((uint64)data[348] << 32) + \
            ((uint64)data[349] << 40) + ((uint64)data[350] << 48) + \
            ((uint64)data[351] << 56);
        pTIIR_Float64->coeffA[11] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[352] + \
            ((uint64)data[353] << 8) + ((uint64)data[354] << 16) + \
            ((uint64)data[355] << 24) + ((uint64)data[356] << 32) + \
            ((uint64)data[357] << 40) + ((uint64)data[358] << 48) + \
            ((uint64)data[359] << 56);
        pTIIR_Float64->coeffA[12] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[360] + \
            ((uint64)data[361] << 8) + ((uint64)data[362] << 16) + \
            ((uint64)data[363] << 24) + ((uint64)data[364] << 32) + \
            ((uint64)data[365] << 40) + ((uint64)data[366] << 48) + \
            ((uint64)data[367] << 56);
        pTIIR_Float64->coeffA[13] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[368] + \
            ((uint64)data[369] << 8) + ((uint64)data[370] << 16) + \
            ((uint64)data[371] << 24) + ((uint64)data[372] << 32) + \
            ((uint64)data[373] << 40) + ((uint64)data[374] << 48) + \
            ((uint64)data[375] << 56);
        pTIIR_Float64->coeffA[14] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[376] + \
            ((uint64)data[377] << 8) + ((uint64)data[378] << 16) + \
            ((uint64)data[379] << 24) + ((uint64)data[380] << 32) + \
            ((uint64)data[381] << 40) + ((uint64)data[382] << 48) + \
            ((uint64)data[383] << 56);
        pTIIR_Float64->coeffA[15] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[384] + \
            ((uint64)data[385] << 8) + ((uint64)data[386] << 16) + \
            ((uint64)data[387] << 24) + ((uint64)data[388] << 32) + \
            ((uint64)data[389] << 40) + ((uint64)data[390] << 48) + \
            ((uint64)data[391] << 56);
        pTIIR_Float64->coeffA[16] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[392] + \
            ((uint64)data[393] << 8) + ((uint64)data[394] << 16) + \
            ((uint64)data[395] << 24) + ((uint64)data[396] << 32) + \
            ((uint64)data[397] << 40) + ((uint64)data[398] << 48) + \
            ((uint64)data[399] << 56);
        pTIIR_Float64->coeffA[17] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[400] + \
            ((uint64)data[401] << 8) + ((uint64)data[402] << 16) + \
            ((uint64)data[403] << 24) + ((uint64)data[404] << 32) + \
            ((uint64)data[405] << 40) + ((uint64)data[406] << 48) + \
            ((uint64)data[407] << 56);
        pTIIR_Float64->coeffA[18] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[408] + \
            ((uint64)data[409] << 8) + ((uint64)data[410] << 16) + \
            ((uint64)data[411] << 24) + ((uint64)data[412] << 32) + \
            ((uint64)data[413] << 40) + ((uint64)data[414] << 48) + \
            ((uint64)data[415] << 56);
        pTIIR_Float64->coeffA[19] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[416] + \
            ((uint64)data[417] << 8) + ((uint64)data[418] << 16) + \
            ((uint64)data[419] << 24) + ((uint64)data[420] << 32) + \
            ((uint64)data[421] << 40) + ((uint64)data[422] << 48) + \
            ((uint64)data[423] << 56);
        pTIIR_Float64->coeffA[20] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[424] + \
            ((uint64)data[425] << 8) + ((uint64)data[426] << 16) + \
            ((uint64)data[427] << 24) + ((uint64)data[428] << 32) + \
            ((uint64)data[429] << 40) + ((uint64)data[430] << 48) + \
            ((uint64)data[431] << 56);
        pTIIR_Float64->coeffA[21] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[432] + \
            ((uint64)data[433] << 8) + ((uint64)data[434] << 16) + \
            ((uint64)data[435] << 24) + ((uint64)data[436] << 32) + \
            ((uint64)data[437] << 40) + ((uint64)data[438] << 48) + \
            ((uint64)data[439] << 56);
        pTIIR_Float64->coeffA[22] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[440] + \
            ((uint64)data[441] << 8) + ((uint64)data[442] << 16) + \
            ((uint64)data[443] << 24) + ((uint64)data[444] << 32) + \
            ((uint64)data[445] << 40) + ((uint64)data[446] << 48) + \
            ((uint64)data[447] << 56);
        pTIIR_Float64->coeffA[23] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[448] + \
            ((uint64)data[449] << 8) + ((uint64)data[450] << 16) + \
            ((uint64)data[451] << 24) + ((uint64)data[452] << 32) + \
            ((uint64)data[453] << 40) + ((uint64)data[454] << 48) + \
            ((uint64)data[455] << 56);
        pTIIR_Float64->coeffA[24] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[456] + \
            ((uint64)data[457] << 8) + ((uint64)data[458] << 16) + \
            ((uint64)data[459] << 24) + ((uint64)data[460] << 32) + \
            ((uint64)data[461] << 40) + ((uint64)data[462] << 48) + \
            ((uint64)data[463] << 56);
        pTIIR_Float64->coeffA[25] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[464] + \
            ((uint64)data[465] << 8) + ((uint64)data[466] << 16) + \
            ((uint64)data[467] << 24) + ((uint64)data[468] << 32) + \
            ((uint64)data[469] << 40) + ((uint64)data[470] << 48) + \
            ((uint64)data[471] << 56);
        pTIIR_Float64->coeffA[26] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[472] + \
            ((uint64)data[473] << 8) + ((uint64)data[474] << 16) + \
            ((uint64)data[475] << 24) + ((uint64)data[476] << 32) + \
            ((uint64)data[477] << 40) + ((uint64)data[478] << 48) + \
            ((uint64)data[479] << 56);
        pTIIR_Float64->coeffA[27] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[480] + \
            ((uint64)data[481] << 8) + ((uint64)data[482] << 16) + \
            ((uint64)data[483] << 24) + ((uint64)data[484] << 32) + \
            ((uint64)data[485] << 40) + ((uint64)data[486] << 48) + \
            ((uint64)data[487] << 56);
        pTIIR_Float64->coeffA[28] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[488] + \
            ((uint64)data[489] << 8) + ((uint64)data[490] << 16) + \
            ((uint64)data[491] << 24) + ((uint64)data[492] << 32) + \
            ((uint64)data[493] << 40) + ((uint64)data[494] << 48) + \
            ((uint64)data[495] << 56);
        pTIIR_Float64->coeffA[29] = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[496] + \
            ((uint64)data[497] << 8) + ((uint64)data[498] << 16) + \
            ((uint64)data[499] << 24) + ((uint64)data[500] << 32) + \
            ((uint64)data[501] << 40) + ((uint64)data[502] << 48) + \
            ((uint64)data[503] << 56);
        pTIIR_Float64->coeffA[30] = (float64)(*(float64*)&tmp64);
        pTIIR_Float64->orderN = UINT8_TO_INT8((uint8)data[504]);
        pTIIR_Float64->orderD = UINT8_TO_INT8((uint8)data[505]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(IIR_FLOAT64_ISLINKED)
void* IIR_Float64_GetAddress(const IIR_FLOAT64* block, uint16 elementId)
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
