// This file was generated by createCFunction.sci on 09-03-2022 08:46

// Computational function for X2C block SquareGen

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
#include <SquareGen_FiP32.h>
#include <SquareGen_FiP32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_SquareGen_FiP32_C(scicos_block* block, scicos_flag flag);
static void x2c_SquareGen_FiP32_C__OutputUpdate(scicos_block* block);
static void x2c_SquareGen_FiP32_C__StateUpdate(scicos_block* block);
static void x2c_SquareGen_FiP32_C__Initialization(scicos_block* block);
static void x2c_SquareGen_FiP32_C__Ending(scicos_block* block);


void x2c_SquareGen_FiP32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_SquareGen_FiP32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_SquareGen_FiP32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_SquareGen_FiP32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_SquareGen_FiP32_C__Ending(block);
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


static void x2c_SquareGen_FiP32_C__set_parameter(scicos_block* block, SQUAREGEN_FIP32 *blockParam) {
    int *paramI;
    double *paramR;
    SQUAREGEN_FIP32 *pTSquareGen_FiP32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSquareGen_FiP32 = GetWorkPtrs(block);
    blockParam->delta_phi = (uint32)paramI[0];
    blockParam->phi = (int32)paramI[1];
    blockParam->level_low = (int32)paramI[2];
    blockParam->level_high = (int32)paramI[3];
}


static void x2c_SquareGen_FiP32_C__Initialization(scicos_block* block) {
    SQUAREGEN_FIP32 *pTSquareGen_FiP32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_f_p;
    int32 inport_f;
    double *inport_dc_p;
    int32 inport_dc;

    /* Declaration of outports */
    double *outport_u;

    /* *** */
    pTSquareGen_FiP32 = scicos_malloc(sizeof(SQUAREGEN_FIP32));
    GetWorkPtrs(block) = pTSquareGen_FiP32;
    x2c_SquareGen_FiP32_C__set_parameter(block, pTSquareGen_FiP32);

    /* Assignment of inports */
    inport_f_p = GetInPortPtrs(block, 1);
    inport_f = convert_double_to_Q31(*inport_f_p);
    pTSquareGen_FiP32->f = &inport_f;
    inport_dc_p = GetInPortPtrs(block, 2);
    inport_dc = convert_double_to_Q31(*inport_dc_p);
    pTSquareGen_FiP32->dc = &inport_dc;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    SquareGen_FiP32_Init(pTSquareGen_FiP32);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q31_to_double(pTSquareGen_FiP32->u);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_SquareGen_FiP32_C__Ending(scicos_block* block) {
    SQUAREGEN_FIP32 *pTSquareGen_FiP32;
    pTSquareGen_FiP32 = GetWorkPtrs(block);
    scicos_free(pTSquareGen_FiP32);
}


static void x2c_SquareGen_FiP32_C__StateUpdate_f(scicos_block* block) {
    SQUAREGEN_FIP32 *pTSquareGen_FiP32;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_f_p;
    int32 inport_f;
    double *inport_dc_p;
    int32 inport_dc;

    /* Declaration of outports */
    double *outport_u;

    /* *** */
    pTSquareGen_FiP32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_f_p = GetInPortPtrs(block, 1);
    inport_f = convert_double_to_Q31(*inport_f_p);
    pTSquareGen_FiP32->f = &inport_f;
    inport_dc_p = GetInPortPtrs(block, 2);
    inport_dc = convert_double_to_Q31(*inport_dc_p);
    pTSquareGen_FiP32->dc = &inport_dc;

    /* Assignment of parameter arrays */

    /* Update */
    SquareGen_FiP32_Update(pTSquareGen_FiP32);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q31_to_double(pTSquareGen_FiP32->u);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_SquareGen_FiP32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_SquareGen_FiP32_C__StateUpdate_f(block);
    }
}


static void x2c_SquareGen_FiP32_C__OutputUpdate(scicos_block* block) {
    /* Time dependency -> execute Update function and Output assignment in State Update function */
}


