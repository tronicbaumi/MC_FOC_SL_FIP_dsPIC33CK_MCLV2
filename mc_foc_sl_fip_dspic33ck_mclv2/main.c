/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33  MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33  MCUs - 1.171.3
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "X2CUtils.h"
#include "X2CMain.h"
#include "pin_manager.h"
#include "userparms.h"
#include "adc1.h"
#include "interrupt_manager.h"
#include <stdbool.h>

/*
                         Main application
 */

//local functions
bool measureOffset(void);
void errorTrap(void); 

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalDisable(); // Stop control loop operation
    
    if( measureOffset() == false){ //if offset measure fail
        errorTrap(); // Stop operation
    }
    
    INTERRUPT_GlobalEnable(); // Start MC and X2C calculation at interrupt
    
    TMR1_Start();
    QEI_Initialize();
    
#ifdef FAULT_ON
       // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1FPCIL = 0x33;
    // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FPCIL = 0x33;
    // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3FPCIL = 0x33;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG1FPCIH = 0x303;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG2FPCIH = 0x303;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG3FPCIH = 0x303;
#else 
    // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1FPCIL = 0x00;
    // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FPCIL = 0x00;
    // PSS Device pin, PCI19; PPS Inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3FPCIL = 0x00;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG1FPCIH = 0x0;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG2FPCIH = 0x0;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS PWM Generator is triggered; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Latched; 
    PG3FPCIH = 0x0;
    
#endif
    
    while (1)
    {
        // Add your application code
        X2C_Communicate(); // X2C scope communication interface task. NON BLOCKING function.
    }
    return 1; 
    
}

/**
 * Measure offset before starting the motor control algorithm
 * ADC sampling must be triggered automatically
 * @return true - if measurement successful
 *         false - if offset is too high
 */

#define FCY (_XTAL_FREQ/2)
#include <libpic30.h>

extern int16_t offset_AN0_IA, offset_ANA1_IB;
bool measureOffset(void){
    uint32_t adcOffsetIa = 0, adcOffsetIb = 0, adcOffsetIc = 0;
    uint32_t i = 0;
    bool result = false;

    LED2_SetHigh(); // Signal the measurement is running
    __delay_ms(10); //wait some measurements
    /* Taking multiple samples to measure voltage
     * offset in all the channels */
    for (i = 0; i < CURRENT_OFFSET_SAMPLE_COUNT; i++)
    {
        while(!IFS5bits.ADCAN0IF); //Wait until next conversion not complete
        
        /* Sum up the converted results */
        adcOffsetIa = adcOffsetIa + (int16_t)ADC1_ConversionResultGet(AN0_IA);
        adcOffsetIb = adcOffsetIb + (int16_t)ADC1_ConversionResultGet(ANA1_IB);
        
        IFS5bits.ADCAN0IF = 0;
    }
    
    /* Averaging to find current offsets */
    offset_AN0_IA = (int16_t) (adcOffsetIa >> CURRENT_OFFSET_SAMPLE_SCALER);
    offset_ANA1_IB = (int16_t) (adcOffsetIb >> CURRENT_OFFSET_SAMPLE_SCALER);
    
    LED2_SetLow(); // Signal the measurement is finished
    result = true;
    
    //Check, if offset not too high
    if( offset_AN0_IA > 0) {
        if( offset_AN0_IA > CURRENT_MAX_OFFSET) result = false; //Offset over the limit
    }
    else{
        if(offset_AN0_IA < (-((int16_t)CURRENT_MAX_OFFSET))) result = false; //Offset over the limit (negative)
    }
    if( offset_ANA1_IB > 0) {
        if( offset_ANA1_IB > CURRENT_MAX_OFFSET) result = false; //Offset over the limit
    }
    else{
        if(offset_ANA1_IB < (-((int16_t)CURRENT_MAX_OFFSET))) result = false; //Offset over the limit (negative)
    }

    return result;
}

void errorTrap(void){
    while(1){
        __delay_ms(100);
        LED1_Toggle(); //10Hz blinking
    }
}

/**
 End of File
*/

