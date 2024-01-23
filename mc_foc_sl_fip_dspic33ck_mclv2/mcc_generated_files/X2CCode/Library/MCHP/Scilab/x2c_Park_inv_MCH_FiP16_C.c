// This file was generated by createCFunction.sci on 09-03-2022 08:46

// Computational function for X2C block Park_inv_MCHP

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
#include <Park_inv_MCHP_FiP16.h>
#include <Park_inv_MCHP_FiP16.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_Park_inv_MCH_FiP16_C(scicos_block* block, scicos_flag flag);
static void x2c_Park_inv_MCH_FiP16_C__OutputUpdate(scicos_block* block);
static void x2c_Park_inv_MCH_FiP16_C__StateUpdate(scicos_block* block);
static void x2c_Park_inv_MCH_FiP16_C__Initialization(scicos_block* block);
static void x2c_Park_inv_MCH_FiP16_C__Ending(scicos_block* block);


void x2c_Park_inv_MCH_FiP16_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Park_inv_MCH_FiP16_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Park_inv_MCH_FiP16_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Park_inv_MCH_FiP16_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Park_inv_MCH_FiP16_C__Ending(block);
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


static void x2c_Park_inv_MCH_FiP16_C__set_parameter(scicos_block* block, PARK_INV_MCHP_FIP16 *blockParam) {
    int *paramI;
    double *paramR;
    PARK_INV_MCHP_FIP16 *pTPark_inv_MCHP_FiP16;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTPark_inv_MCHP_FiP16 = GetWorkPtrs(block);
}


static void x2c_Park_inv_MCH_FiP16_C__Initialization(scicos_block* block) {
    PARK_INV_MCHP_FIP16 *pTPark_inv_MCHP_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_d_p;
    int16 inport_d;
    double *inport_q_p;
    int16 inport_q;
    double *inport_theta_p;
    int16 inport_theta;

    /* Declaration of outports */
    double *outport_alpha;
    double *outport_beta;

    /* *** */
    pTPark_inv_MCHP_FiP16 = scicos_malloc(sizeof(PARK_INV_MCHP_FIP16));
    GetWorkPtrs(block) = pTPark_inv_MCHP_FiP16;
    x2c_Park_inv_MCH_FiP16_C__set_parameter(block, pTPark_inv_MCHP_FiP16);

    /* Assignment of inports */
    inport_d_p = GetInPortPtrs(block, 1);
    inport_d = convert_double_to_Q15(*inport_d_p);
    pTPark_inv_MCHP_FiP16->d = &inport_d;
    inport_q_p = GetInPortPtrs(block, 2);
    inport_q = convert_double_to_Q15(*inport_q_p);
    pTPark_inv_MCHP_FiP16->q = &inport_q;
    inport_theta_p = GetInPortPtrs(block, 3);
    inport_theta = convert_double_to_Q15(*inport_theta_p);
    pTPark_inv_MCHP_FiP16->theta = &inport_theta;

    /* Assignment of parameter arrays */
    arrayStart = 0;

    /* Initialization */
    Park_inv_MCHP_FiP16_Init(pTPark_inv_MCHP_FiP16);

    /* Assignment of outports */
    outport_alpha = GetOutPortPtrs(block, 1);
    *outport_alpha = convert_Q15_to_double(pTPark_inv_MCHP_FiP16->alpha);
    outport_beta = GetOutPortPtrs(block, 2);
    *outport_beta = convert_Q15_to_double(pTPark_inv_MCHP_FiP16->beta);

    /* Update of parameter arrays */
    arrayStart = 0;
}


static void x2c_Park_inv_MCH_FiP16_C__Ending(scicos_block* block) {
    PARK_INV_MCHP_FIP16 *pTPark_inv_MCHP_FiP16;
    pTPark_inv_MCHP_FiP16 = GetWorkPtrs(block);
    scicos_free(pTPark_inv_MCHP_FiP16);
}


static void x2c_Park_inv_MCH_FiP16_C__StateUpdate_f(scicos_block* block) {
    /* No time dependency -> execute Update function and Output assignment in Output Update function */
}


static void x2c_Park_inv_MCH_FiP16_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Park_inv_MCH_FiP16_C__StateUpdate_f(block);
    }
}


static void x2c_Park_inv_MCH_FiP16_C__OutputUpdate(scicos_block* block) {
    PARK_INV_MCHP_FIP16 *pTPark_inv_MCHP_FiP16;
    int16 arrayStart = 0;

    /* Declaration of inports */
    double *inport_d_p;
    int16 inport_d;
    double *inport_q_p;
    int16 inport_q;
    double *inport_theta_p;
    int16 inport_theta;

    /* Declaration of outports */
    double *outport_alpha;
    double *outport_beta;

    /* *** */
    pTPark_inv_MCHP_FiP16 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_d_p = GetInPortPtrs(block, 1);
    inport_d = convert_double_to_Q15(*inport_d_p);
    pTPark_inv_MCHP_FiP16->d = &inport_d;
    inport_q_p = GetInPortPtrs(block, 2);
    inport_q = convert_double_to_Q15(*inport_q_p);
    pTPark_inv_MCHP_FiP16->q = &inport_q;
    inport_theta_p = GetInPortPtrs(block, 3);
    inport_theta = convert_double_to_Q15(*inport_theta_p);
    pTPark_inv_MCHP_FiP16->theta = &inport_theta;

    /* Assignment of parameter arrays */

    /* Update */
    Park_inv_MCHP_FiP16_Update(pTPark_inv_MCHP_FiP16);

    /* Assignment of outports */
    outport_alpha = GetOutPortPtrs(block, 1);
    *outport_alpha = convert_Q15_to_double(pTPark_inv_MCHP_FiP16->alpha);
    outport_beta = GetOutPortPtrs(block, 2);
    *outport_beta = convert_Q15_to_double(pTPark_inv_MCHP_FiP16->beta);

    /* Update of parameter arrays */
    arrayStart = 0;
}


