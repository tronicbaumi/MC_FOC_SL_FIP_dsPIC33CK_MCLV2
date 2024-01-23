// This file was generated by createCFunction.sci on 09-03-2022 08:46

// Computational function for X2C block SVM_MCHP

#define SCILAB_SIM_FILE /* mark this file as Scilab simulation file */

/* include Scicos / Xcos headers */
#include <scicos.h>
#include <scicos_block4.h>
#include <scicos_malloc.h>
#include <scicos_free.h>
#include <Simulation_PortConversion.h>
//#define DEBUG // uncomment to enable debugging
#ifdef DEBUG
    #include <stdio.h>
#endif

/* include block implementation */
#include <SVM_MCHP_Float32.h>
#include <SVM_MCHP_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_SVM_MCHP_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_SVM_MCHP_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_SVM_MCHP_Float32_C__StateUpdate(scicos_block* block);
static void x2c_SVM_MCHP_Float32_C__Initialization(scicos_block* block);
static void x2c_SVM_MCHP_Float32_C__Ending(scicos_block* block);


void x2c_SVM_MCHP_Float32_C(scicos_block* block, scicos_flag flag) {
    /*
     * This function will be called by Xcos
     */
    switch (flag) {
        case DerivativeState:  /* 0 */
        {
            break;
        }
        case OutputUpdate:     /* 1 */
        {
            x2c_SVM_MCHP_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_SVM_MCHP_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_SVM_MCHP_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_SVM_MCHP_Float32_C__Ending(block);
            break;
        }
        case ReInitialization: /* 6 */
        {
            break;
        }
        case ZeroCrossing:     /* 9 */
        {
           break;
        }
        default:     /* ContinousPropertiesUpdate (v5.5.x) Jacobian (v5.5.x) or Residute (v5.4.1) or something else */
        {
           break;
        }
    }
}


static void x2c_SVM_MCHP_Float32_C__set_parameter(scicos_block* block, SVM_MCHP_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    SVM_MCHP_FLOAT32 *pTSVM_MCHP_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSVM_MCHP_Float32 = GetWorkPtrs(block);
}


static void x2c_SVM_MCHP_Float32_C__Initialization(scicos_block* block) {
    SVM_MCHP_FLOAT32 *pTSVM_MCHP_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_A_in_p;
    float32 inport_A_in;
    double *inport_B_in_p;
    float32 inport_B_in;
    double *inport_C_in_p;
    float32 inport_C_in;

    /* Declaration of outports */
    double *outport_A_out;
    double *outport_B_out;
    double *outport_C_out;

    /* *** */
    pTSVM_MCHP_Float32 = scicos_malloc(sizeof(SVM_MCHP_FLOAT32));
    GetWorkPtrs(block) = pTSVM_MCHP_Float32;
    x2c_SVM_MCHP_Float32_C__set_parameter(block, pTSVM_MCHP_Float32);

    /* Assignment of inports */
    inport_A_in_p = GetInPortPtrs(block, 1);
    inport_A_in = convert_double_to_float32(*inport_A_in_p);
    pTSVM_MCHP_Float32->A_in = &inport_A_in;
    inport_B_in_p = GetInPortPtrs(block, 2);
    inport_B_in = convert_double_to_float32(*inport_B_in_p);
    pTSVM_MCHP_Float32->B_in = &inport_B_in;
    inport_C_in_p = GetInPortPtrs(block, 3);
    inport_C_in = convert_double_to_float32(*inport_C_in_p);
    pTSVM_MCHP_Float32->C_in = &inport_C_in;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    SVM_MCHP_Float32_Init(pTSVM_MCHP_Float32);

    /* Assignment of outports */
    outport_A_out = GetOutPortPtrs(block, 1);
    *outport_A_out = convert_float32_to_double(pTSVM_MCHP_Float32->A_out);
    outport_B_out = GetOutPortPtrs(block, 2);
    *outport_B_out = convert_float32_to_double(pTSVM_MCHP_Float32->B_out);
    outport_C_out = GetOutPortPtrs(block, 3);
    *outport_C_out = convert_float32_to_double(pTSVM_MCHP_Float32->C_out);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_SVM_MCHP_Float32_C__Ending(scicos_block* block) {
    SVM_MCHP_FLOAT32 *pTSVM_MCHP_Float32;
    pTSVM_MCHP_Float32 = GetWorkPtrs(block);
    scicos_free(pTSVM_MCHP_Float32);
}


static void x2c_SVM_MCHP_Float32_C__StateUpdate_f(scicos_block* block) {
    /* No time dependency -> execute Update function and Output assignment in Output Update function */
}


static void x2c_SVM_MCHP_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_SVM_MCHP_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_SVM_MCHP_Float32_C__OutputUpdate(scicos_block* block) {
    SVM_MCHP_FLOAT32 *pTSVM_MCHP_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_A_in_p;
    float32 inport_A_in;
    double *inport_B_in_p;
    float32 inport_B_in;
    double *inport_C_in_p;
    float32 inport_C_in;

    /* Declaration of outports */
    double *outport_A_out;
    double *outport_B_out;
    double *outport_C_out;

    /* *** */
    pTSVM_MCHP_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_A_in_p = GetInPortPtrs(block, 1);
    inport_A_in = convert_double_to_float32(*inport_A_in_p);
    pTSVM_MCHP_Float32->A_in = &inport_A_in;
    inport_B_in_p = GetInPortPtrs(block, 2);
    inport_B_in = convert_double_to_float32(*inport_B_in_p);
    pTSVM_MCHP_Float32->B_in = &inport_B_in;
    inport_C_in_p = GetInPortPtrs(block, 3);
    inport_C_in = convert_double_to_float32(*inport_C_in_p);
    pTSVM_MCHP_Float32->C_in = &inport_C_in;

    /* Assignment of parameter arrays */

    /* Update */
    SVM_MCHP_Float32_Update(pTSVM_MCHP_Float32);

    /* Assignment of outports */
    outport_A_out = GetOutPortPtrs(block, 1);
    *outport_A_out = convert_float32_to_double(pTSVM_MCHP_Float32->A_out);
    outport_B_out = GetOutPortPtrs(block, 2);
    *outport_B_out = convert_float32_to_double(pTSVM_MCHP_Float32->B_out);
    outport_C_out = GetOutPortPtrs(block, 3);
    *outport_C_out = convert_float32_to_double(pTSVM_MCHP_Float32->C_out);

    /* Update of parameter arrays */
    arrayStart = 0;
}


