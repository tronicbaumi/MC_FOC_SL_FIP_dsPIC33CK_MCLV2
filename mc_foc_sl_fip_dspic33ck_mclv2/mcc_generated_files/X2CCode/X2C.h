/**
 * @file
 * @brief Generated model file.
 * 
 * Date:  2023-10-12 13:56
 * 
 * X2C-Version: 6.4.2916
 * X2C-Edition: Free
 */
/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Model: mc_foc_sl_fip_dspic33ck_mclv2                                                                               */
/* Date:  2023-10-12 13:56                                                                                            */

/* X2C-Version: 6.4.2916                                                                                              */
/* X2C-Edition: Free                                                                                                  */

#ifndef X2C_H
#define X2C_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
/* Common includes                                                                                                    */
#include "Constant_Bool.h"
#include "Gain_FiP16.h"
#include "I_FiP16.h"
#include "RateLimiter_FiP16.h"
#include "LoopBreaker_Bool.h"
#include "BEMF_MCHP_FiP16.h"
#include "ManualSwitch_FiP16.h"
#include "LoopBreaker_FiP16.h"
#include "Constant_FiP16.h"
#include "Not_Bool.h"
#include "uSub_FiP16.h"
#include "Sin3Gen_FiP16.h"
#include "PI_FiP16.h"
#include "Saturation_FiP16.h"
#include "Park_MCHP_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "Sequencer_FiP16.h"
#include "SinGen_FiP16.h"
#include "Sub_FiP16.h"
#include "Clarke_Park_MCHP_FiP16.h"
#include "PT1_FiP16.h"
#include "uI_FiP16.h"
#include "TypeConv_FiP16_Bool.h"
#include "Park_Clarke_inv_SVM_MCHP_FiP16.h"
#include "Add_FiP16.h"
#include "Sign_FiP16.h"
#include "Mult_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS \
    CONSTANT_BOOL_FUNCTIONS , \
    GAIN_FIP16_FUNCTIONS , \
    I_FIP16_FUNCTIONS , \
    RATELIMITER_FIP16_FUNCTIONS , \
    LOOPBREAKER_BOOL_FUNCTIONS , \
    BEMF_MCHP_FIP16_FUNCTIONS , \
    MANUALSWITCH_FIP16_FUNCTIONS , \
    LOOPBREAKER_FIP16_FUNCTIONS , \
    CONSTANT_FIP16_FUNCTIONS , \
    NOT_BOOL_FUNCTIONS , \
    USUB_FIP16_FUNCTIONS , \
    SIN3GEN_FIP16_FUNCTIONS , \
    PI_FIP16_FUNCTIONS , \
    SATURATION_FIP16_FUNCTIONS , \
    PARK_MCHP_FIP16_FUNCTIONS , \
    AUTOSWITCH_FIP16_FUNCTIONS , \
    SEQUENCER_FIP16_FUNCTIONS , \
    SINGEN_FIP16_FUNCTIONS , \
    SUB_FIP16_FUNCTIONS , \
    CLARKE_PARK_MCHP_FIP16_FUNCTIONS , \
    PT1_FIP16_FUNCTIONS , \
    UI_FIP16_FUNCTIONS , \
    TYPECONV_FIP16_BOOL_FUNCTIONS , \
    PARK_CLARKE_INV_SVM_MCHP_FIP16_FUNCTIONS , \
    ADD_FIP16_FUNCTIONS , \
    SIGN_FIP16_FUNCTIONS , \
    MULT_FIP16_FUNCTIONS , \
    SCOPE_MAIN_FUNCTIONS

#define PARAMETER_TABLE \
    { 1, &x2cModel.blocks.sFOC_main.bClarke_Park_MCHP } , \
    { 2, &x2cModel.blocks.sFOC_main.bConstant } , \
    { 3, &x2cModel.blocks.sFOC_main.bConstant1 } , \
    { 4, &x2cModel.blocks.sFOC_main.bGain } , \
    { 5, &x2cModel.blocks.sFOC_main.bGain1 } , \
    { 6, &x2cModel.blocks.sFOC_main.bGain2 } , \
    { 7, &x2cModel.blocks.sFOC_main.bManualSwitch } , \
    { 8, &x2cModel.blocks.sFOC_main.bManualSwitch1 } , \
    { 9, &x2cModel.blocks.sFOC_main.bManualSwitch2 } , \
    { 10, &x2cModel.blocks.sFOC_main.bManualSwitch3 } , \
    { 11, &x2cModel.blocks.sFOC_main.bManualSwitch4 } , \
    { 12, &x2cModel.blocks.sFOC_main.bNot } , \
    { 13, &x2cModel.blocks.sFOC_main.bOpenLoop_Vd } , \
    { 14, &x2cModel.blocks.sFOC_main.bOpenLoop_Vq } , \
    { 15, &x2cModel.blocks.sFOC_main.bPI_flux } , \
    { 16, &x2cModel.blocks.sFOC_main.bPI_torque } , \
    { 17, &x2cModel.blocks.sFOC_main.sPLLEstimator.bBEMF_MCHP } , \
    { 18, &x2cModel.blocks.sFOC_main.sPLLEstimator.bEdfilter } , \
    { 19, &x2cModel.blocks.sFOC_main.sPLLEstimator.bEqfilter } , \
    { 20, &x2cModel.blocks.sFOC_main.sPLLEstimator.bLoopBreaker } , \
    { 21, &x2cModel.blocks.sFOC_main.sPLLEstimator.bPark_MCHP } , \
    { 22, &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAdd } , \
    { 23, &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bAutoSwitch } , \
    { 24, &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bGain } , \
    { 25, &x2cModel.blocks.sFOC_main.sPLLEstimator.sSpeed_Estim_Superblock.bSub } , \
    { 26, &x2cModel.blocks.sFOC_main.sPLLEstimator.buI } , \
    { 27, &x2cModel.blocks.sFOC_main.bPark_Clarke_inv_SVM_MCHP } , \
    { 28, &x2cModel.blocks.sFOC_main.bSaturation } , \
    { 29, &x2cModel.blocks.sFOC_main.bSaturation1 } , \
    { 30, &x2cModel.blocks.sFOC_main.bSin3Gen } , \
    { 31, &x2cModel.blocks.sFOC_main.bSub_flux } , \
    { 32, &x2cModel.blocks.sFOC_main.bSub_torque } , \
    { 33, &x2cModel.blocks.bGain } , \
    { 34, &x2cModel.blocks.bLoopBreaker } , \
    { 35, &x2cModel.blocks.bLoopBreaker1 } , \
    { 36, &x2cModel.blocks.bManualSwitch } , \
    { 37, &x2cModel.blocks.bManualSwitch1 } , \
    { 38, &x2cModel.blocks.bNot } , \
    { 39, &x2cModel.blocks.sSpeed_PI.bConstant } , \
    { 40, &x2cModel.blocks.sSpeed_PI.bConstant1 } , \
    { 41, &x2cModel.blocks.sSpeed_PI.bManualSwitch } , \
    { 42, &x2cModel.blocks.sSpeed_PI.bPI_speed } , \
    { 43, &x2cModel.blocks.sSpeed_PI.bRateLimiter } , \
    { 44, &x2cModel.blocks.sSpeed_PI.bSpeed_error } , \
    { 45, &x2cModel.blocks.sSpeed_PI.sperturbation.bAdd } , \
    { 46, &x2cModel.blocks.sSpeed_PI.sperturbation.bAutoSwitch } , \
    { 47, &x2cModel.blocks.sSpeed_PI.sperturbation.bConstant } , \
    { 48, &x2cModel.blocks.sSpeed_PI.sperturbation.bConstant1 } , \
    { 49, &x2cModel.blocks.sSpeed_PI.sperturbation.bConstant2 } , \
    { 50, &x2cModel.blocks.sSpeed_PI.sperturbation.bConstant3 } , \
    { 51, &x2cModel.blocks.sSpeed_PI.sperturbation.bGain } , \
    { 52, &x2cModel.blocks.sSpeed_PI.sperturbation.bRateLimiter } , \
    { 53, &x2cModel.blocks.sSpeed_PI.sperturbation.bSinGen } , \
    { 54, &x2cModel.blocks.sstartup.bConstant } , \
    { 55, &x2cModel.blocks.sstartup.bConstant1 } , \
    { 56, &x2cModel.blocks.sstartup.bConstant2 } , \
    { 57, &x2cModel.blocks.sstartup.bConstant3 } , \
    { 58, &x2cModel.blocks.sstartup.bConstant5 } , \
    { 59, &x2cModel.blocks.sstartup.bFlux_select } , \
    { 60, &x2cModel.blocks.sstartup.bFlux_select1 } , \
    { 61, &x2cModel.blocks.sstartup.bIdRateLimiter } , \
    { 62, &x2cModel.blocks.sstartup.bIq_select } , \
    { 63, &x2cModel.blocks.sstartup.bLoopBreaker } , \
    { 64, &x2cModel.blocks.sstartup.bLoopBreaker1 } , \
    { 65, &x2cModel.blocks.sstartup.bManualSwitch } , \
    { 66, &x2cModel.blocks.sstartup.bManualSwitch1 } , \
    { 67, &x2cModel.blocks.sstartup.bPI } , \
    { 68, &x2cModel.blocks.sstartup.bPosError } , \
    { 69, &x2cModel.blocks.sstartup.bPosSwitch } , \
    { 70, &x2cModel.blocks.sstartup.bRamp_Up_Current } , \
    { 71, &x2cModel.blocks.sstartup.sRamp_Up_SB.bConstant4 } , \
    { 72, &x2cModel.blocks.sstartup.sRamp_Up_SB.bI } , \
    { 73, &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero } , \
    { 74, &x2cModel.blocks.sstartup.sRamp_Up_SB.bI_Init_Zero1 } , \
    { 75, &x2cModel.blocks.sstartup.sRamp_Up_SB.bMult } , \
    { 76, &x2cModel.blocks.sstartup.sRamp_Up_SB.bRamp_Up_PositionGenerator } , \
    { 77, &x2cModel.blocks.sstartup.sRamp_Up_SB.bSaturation } , \
    { 78, &x2cModel.blocks.sstartup.sRamp_Up_SB.bSign } , \
    { 79, &x2cModel.blocks.sstartup.sRamp_Up_SB.bTypeConv } , \
    { 80, &x2cModel.blocks.sstartup.bSequencer } , \
    { 81, &x2cModel.blocks.sstartup.bTypeConv } , \
    { 82, &x2cModel.blocks.sstartup.bTypeConv1 } , \
    { 83, &x2cModel.blocks.sstartup.bTypeConv2 } , \
    { 101, &x2cScope }

#define INPORT_PARAMID_TABLE \
    { 84, 2, &x2cModel.inports.bCPU_LOAD } , \
    { 85, 2, &x2cModel.inports.bI_a } , \
    { 86, 2, &x2cModel.inports.bI_b } , \
    { 87, 2, &x2cModel.inports.bI_sum } , \
    { 88, 2, &x2cModel.inports.bQEI_POS } , \
    { 89, 2, &x2cModel.inports.bQEI_VEL } , \
    { 90, 1, &x2cModel.inports.bS2 } , \
    { 91, 2, &x2cModel.inports.bS3 } , \
    { 92, 2, &x2cModel.inports.bV_POT } 

#define OUTPORT_PARAMID_TABLE \
    { 93, 2, &x2cModel.outports.sFOC_main.bEstimated_angle } , \
    { 94, 2, &x2cModel.outports.sFOC_main.bEstimated_speed } , \
    { 95, 1, &x2cModel.outports.bHOME_INIT } , \
    { 96, 1, &x2cModel.outports.bLED_D17 } , \
    { 97, 2, &x2cModel.outports.bLED_D2 } , \
    { 98, 2, &x2cModel.outports.bPWM1 } , \
    { 99, 2, &x2cModel.outports.bPWM2 } , \
    { 100, 2, &x2cModel.outports.bPWM3 } 


/**********************************************************************************************************************/
/**                                            Model structure definition                                            **/
/**********************************************************************************************************************/
struct x2cModel {
/*  Control Blocks                                                                                                    */
    struct {
/*      Sub-system FOC_main                                                                                           */
        struct {
/*          Sub-system PLLEstimator                                                                                   */
            struct {
/*              Sub-system Speed_Estim_Superblock                                                                     */
                struct {
                    ADD_FIP16 bAdd;
                    AUTOSWITCH_FIP16 bAutoSwitch;
                    GAIN_FIP16 bGain;
                    SUB_FIP16 bSub;
                } sSpeed_Estim_Superblock;
                BEMF_MCHP_FIP16 bBEMF_MCHP;
                PT1_FIP16 bEdfilter;
                PT1_FIP16 bEqfilter;
                LOOPBREAKER_FIP16 bLoopBreaker;
                PARK_MCHP_FIP16 bPark_MCHP;
                UI_FIP16 buI;
            } sPLLEstimator;
            CLARKE_PARK_MCHP_FIP16 bClarke_Park_MCHP;
            CONSTANT_FIP16 bConstant;
            CONSTANT_FIP16 bConstant1;
            GAIN_FIP16 bGain;
            GAIN_FIP16 bGain1;
            GAIN_FIP16 bGain2;
            MANUALSWITCH_FIP16 bManualSwitch;
            MANUALSWITCH_FIP16 bManualSwitch1;
            MANUALSWITCH_FIP16 bManualSwitch2;
            MANUALSWITCH_FIP16 bManualSwitch3;
            MANUALSWITCH_FIP16 bManualSwitch4;
            NOT_BOOL bNot;
            CONSTANT_FIP16 bOpenLoop_Vd;
            CONSTANT_FIP16 bOpenLoop_Vq;
            PI_FIP16 bPI_flux;
            PI_FIP16 bPI_torque;
            PARK_CLARKE_INV_SVM_MCHP_FIP16 bPark_Clarke_inv_SVM_MCHP;
            SATURATION_FIP16 bSaturation;
            SATURATION_FIP16 bSaturation1;
            SIN3GEN_FIP16 bSin3Gen;
            SUB_FIP16 bSub_flux;
            SUB_FIP16 bSub_torque;
        } sFOC_main;
/*      Sub-system Speed_PI                                                                                           */
        struct {
/*          Sub-system perturbation                                                                                   */
            struct {
                ADD_FIP16 bAdd;
                AUTOSWITCH_FIP16 bAutoSwitch;
                CONSTANT_FIP16 bConstant;
                CONSTANT_FIP16 bConstant1;
                CONSTANT_BOOL bConstant2;
                CONSTANT_FIP16 bConstant3;
                GAIN_FIP16 bGain;
                RATELIMITER_FIP16 bRateLimiter;
                SINGEN_FIP16 bSinGen;
            } sperturbation;
            CONSTANT_FIP16 bConstant;
            CONSTANT_FIP16 bConstant1;
            MANUALSWITCH_FIP16 bManualSwitch;
            PI_FIP16 bPI_speed;
            RATELIMITER_FIP16 bRateLimiter;
            SUB_FIP16 bSpeed_error;
        } sSpeed_PI;
/*      Sub-system startup                                                                                            */
        struct {
/*          Sub-system Ramp_Up_SB                                                                                     */
            struct {
                CONSTANT_FIP16 bConstant4;
                I_FIP16 bI;
                CONSTANT_FIP16 bI_Init_Zero;
                CONSTANT_FIP16 bI_Init_Zero1;
                MULT_FIP16 bMult;
                UI_FIP16 bRamp_Up_PositionGenerator;
                SATURATION_FIP16 bSaturation;
                SIGN_FIP16 bSign;
                TYPECONV_FIP16_BOOL bTypeConv;
            } sRamp_Up_SB;
            CONSTANT_FIP16 bConstant;
            CONSTANT_FIP16 bConstant1;
            CONSTANT_FIP16 bConstant2;
            CONSTANT_FIP16 bConstant3;
            CONSTANT_BOOL bConstant5;
            AUTOSWITCH_FIP16 bFlux_select;
            AUTOSWITCH_FIP16 bFlux_select1;
            RATELIMITER_FIP16 bIdRateLimiter;
            AUTOSWITCH_FIP16 bIq_select;
            LOOPBREAKER_FIP16 bLoopBreaker;
            LOOPBREAKER_BOOL bLoopBreaker1;
            MANUALSWITCH_FIP16 bManualSwitch;
            MANUALSWITCH_FIP16 bManualSwitch1;
            PI_FIP16 bPI;
            USUB_FIP16 bPosError;
            AUTOSWITCH_FIP16 bPosSwitch;
            CONSTANT_FIP16 bRamp_Up_Current;
            SEQUENCER_FIP16 bSequencer;
            TYPECONV_FIP16_BOOL bTypeConv;
            TYPECONV_FIP16_BOOL bTypeConv1;
            TYPECONV_FIP16_BOOL bTypeConv2;
        } sstartup;
        GAIN_FIP16 bGain;
        LOOPBREAKER_FIP16 bLoopBreaker;
        LOOPBREAKER_FIP16 bLoopBreaker1;
        MANUALSWITCH_FIP16 bManualSwitch;
        MANUALSWITCH_FIP16 bManualSwitch1;
        NOT_BOOL bNot;
    } blocks;
/*  Inports                                                                                                           */
    struct {
        int16 bCPU_LOAD;
        int16 bI_a;
        int16 bI_b;
        int16 bI_sum;
        int16 bQEI_POS;
        int16 bQEI_VEL;
        bool bS2;
        int16 bS3;
        int16 bV_POT;
    } inports;
/*  Outports                                                                                                          */
    struct {
/*      Sub-system FOC_main                                                                                           */
        struct {
            int16* bEstimated_angle;
            int16* bEstimated_speed;
        } sFOC_main;
        bool* bHOME_INIT;
        bool* bLED_D17;
        int16* bLED_D2;
        int16* bPWM1;
        int16* bPWM2;
        int16* bPWM3;
    } outports;
};

/**********************************************************************************************************************/
/**     Externals                                                                                                    **/
/**********************************************************************************************************************/
extern struct x2cModel x2cModel;

extern const tBlockFunctions blockFunctionTable[];
extern const tParameterTable parameterIdTable[];
extern const tIoParamIdEntry inportParamIdTable[];
extern const tIoParamIdEntry outportParamIdTable[];

#define X2C_UPDATE_10_DIVIDER 10

/**********************************************************************************************************************/
/**     Prototypes                                                                                                   **/
/**********************************************************************************************************************/
void X2C_Init(void);
void X2C_Update(void);
void X2C_Update_1(void);
void X2C_Update_10(void);

#ifdef __cplusplus
}
#endif

#endif
