// This file was generated by createCFunction.sci on 09-03-2022 08:46

// Computational function for X2C block Clarke_MCHP

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
#include <Clarke_MCHP_Float32.h>
#include <Clarke_MCHP_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_Clarke_MCHP_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_Clarke_MCHP_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_Clarke_MCHP_Float32_C__StateUpdate(scicos_block* block);
static void x2c_Clarke_MCHP_Float32_C__Initialization(scicos_block* block);
static void x2c_Clarke_MCHP_Float32_C__Ending(scicos_block* block);


void x2c_Clarke_MCHP_Float32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Clarke_MCHP_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Clarke_MCHP_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Clarke_MCHP_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Clarke_MCHP_Float32_C__Ending(block);
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


static void x2c_Clarke_MCHP_Float32_C__set_parameter(scicos_block* block, CLARKE_MCHP_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    CLARKE_MCHP_FLOAT32 *pTClarke_MCHP_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTClarke_MCHP_Float32 = GetWorkPtrs(block);
}


static void x2c_Clarke_MCHP_Float32_C__Initialization(scicos_block* block) {
    CLARKE_MCHP_FLOAT32 *pTClarke_MCHP_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_a_p;
    float32 inport_a;
    double *inport_b_p;
    float32 inport_b;

    /* Declaration of outports */
    double *outport_alpha;
    double *outport_beta;

    /* *** */
    pTClarke_MCHP_Float32 = scicos_malloc(sizeof(CLARKE_MCHP_FLOAT32));
    GetWorkPtrs(block) = pTClarke_MCHP_Float32;
    x2c_Clarke_MCHP_Float32_C__set_parameter(block, pTClarke_MCHP_Float32);

    /* Assignment of inports */
    inport_a_p = GetInPortPtrs(block, 1);
    inport_a = convert_double_to_float32(*inport_a_p);
    pTClarke_MCHP_Float32->a = &inport_a;
    inport_b_p = GetInPortPtrs(block, 2);
    inport_b = convert_double_to_float32(*inport_b_p);
    pTClarke_MCHP_Float32->b = &inport_b;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    Clarke_MCHP_Float32_Init(pTClarke_MCHP_Float32);

    /* Assignment of outports */
    outport_alpha = GetOutPortPtrs(block, 1);
    *outport_alpha = convert_float32_to_double(pTClarke_MCHP_Float32->alpha);
    outport_beta = GetOutPortPtrs(block, 2);
    *outport_beta = convert_float32_to_double(pTClarke_MCHP_Float32->beta);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_Clarke_MCHP_Float32_C__Ending(scicos_block* block) {
    CLARKE_MCHP_FLOAT32 *pTClarke_MCHP_Float32;
    pTClarke_MCHP_Float32 = GetWorkPtrs(block);
    scicos_free(pTClarke_MCHP_Float32);
}


static void x2c_Clarke_MCHP_Float32_C__StateUpdate_f(scicos_block* block) {
    /* No time dependency -> execute Update function and Output assignment in Output Update function */
}


static void x2c_Clarke_MCHP_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Clarke_MCHP_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_Clarke_MCHP_Float32_C__OutputUpdate(scicos_block* block) {
    CLARKE_MCHP_FLOAT32 *pTClarke_MCHP_Float32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_a_p;
    float32 inport_a;
    double *inport_b_p;
    float32 inport_b;

    /* Declaration of outports */
    double *outport_alpha;
    double *outport_beta;

    /* *** */
    pTClarke_MCHP_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_a_p = GetInPortPtrs(block, 1);
    inport_a = convert_double_to_float32(*inport_a_p);
    pTClarke_MCHP_Float32->a = &inport_a;
    inport_b_p = GetInPortPtrs(block, 2);
    inport_b = convert_double_to_float32(*inport_b_p);
    pTClarke_MCHP_Float32->b = &inport_b;

    /* Assignment of parameter arrays */

    /* Update */
    Clarke_MCHP_Float32_Update(pTClarke_MCHP_Float32);

    /* Assignment of outports */
    outport_alpha = GetOutPortPtrs(block, 1);
    *outport_alpha = convert_float32_to_double(pTClarke_MCHP_Float32->alpha);
    outport_beta = GetOutPortPtrs(block, 2);
    *outport_beta = convert_float32_to_double(pTClarke_MCHP_Float32->beta);

    /* Update of parameter arrays */
    arrayStart = 0;
}


