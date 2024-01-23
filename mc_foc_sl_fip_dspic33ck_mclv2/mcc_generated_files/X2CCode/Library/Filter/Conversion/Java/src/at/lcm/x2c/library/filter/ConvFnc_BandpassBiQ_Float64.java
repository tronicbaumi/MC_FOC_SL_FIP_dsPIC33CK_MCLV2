/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2159 $
 * $LastChangedDate:: 2021-03-22 17:32:11 +0100#$
 */
// USERCODE-BEGIN:Description                                                                                           
/* Description: */
// USERCODE-END:Description                                                                                             

package at.lcm.x2c.library.filter;

import at.lcm.x2c.core.structure.*;
import at.lcm.bu21.general.dtypes.*;

// USERCODE-BEGIN:Imports                                                                                               
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_BandpassBiQ_Float64 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: characteristic                                                                               
        MaskComboBox characteristicMaskVal = 
            (MaskComboBox)this.getMaskParameter("characteristic").getMaskDataType();
        TString characteristicMaskData = 
            (TString)characteristicMaskVal.getData();
        // Mask Parameter: fc1                                                                                          
        MaskDouble fc1MaskVal = 
            (MaskDouble)this.getMaskParameter("fc1").getMaskDataType();
        TNumeric fc1MaskData = 
            (TNumeric)fc1MaskVal.getData();
        // Mask Parameter: fc2                                                                                          
        MaskDouble fc2MaskVal = 
            (MaskDouble)this.getMaskParameter("fc2").getMaskDataType();
        TNumeric fc2MaskData = 
            (TNumeric)fc2MaskVal.getData();
        // Mask Parameter: rc                                                                                           
        MaskDouble rcMaskVal = 
            (MaskDouble)this.getMaskParameter("rc").getMaskDataType();
        TNumeric rcMaskData = 
            (TNumeric)rcMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: b2                                                                                 
        TNumeric b2CtrVal = this.getImplementationParameterData("b2");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_veryold                                                                         
        TNumeric in_veryoldCtrVal = this.getImplementationParameterData("in_veryold");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_veryold                                                                        
        TNumeric out_veryoldCtrVal = this.getImplementationParameterData("out_veryold");

// USERCODE-BEGIN:ConvMaskToImplementation                                                                              
        double fc1 = Math.abs(Double.valueOf(fc1MaskVal.getValue()));
        double fc2 = Math.abs(Double.valueOf(fc2MaskVal.getValue()));

        /* get sample time */
        double ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
        if (ts_fact <= 0) {
            ts_fact = 1;
        }
        double Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

        /* get sampling frequency */
        double fs = 1 / Ts;

        // validate input
        if (fc1 >= fc2) {
            throw new Exception(
                    "Wrong Input! lower cut-off frequency happens to be greater than upper cut-off frequency!");
        }
        if ((2 * fc2) >= fs) {
            throw new Exception("Wrong Input! Upper cut-off frequency was choosen to big! Should be less then fs/2.");
        }

        /* -------------- Normalize frequency */
        double fcScaled1 = (2 * fc1) / fs;
        double fcScaled2 = (2 * fc2) / fs;

        /* ----------------------------------------------------------------------------------------- */
        /* Get analog lowpass prototype */
        /* ----------------------------------------------------------------------------------------- */
        double p_x = 0;
        double p_y = 0;
        double k = 0;

        if (characteristicMaskVal.getValue().equals("Butterworth")
                || characteristicMaskVal.getValue().equals("Bessel")) {
            /* poles */
            p_x = -1;
            p_y = -0;
            /* gain */
            k = 1.0;
        } else if (characteristicMaskVal.getValue().equals("Chebyshev")) {
            double rp = Math.abs(Double.valueOf(rcMaskVal.getValue()));
            if (rp == 0) {
                throw new Exception("Division by zero! Choose maximum passband ripple 'rc' different from zero!");
            }

            /* poles */
            double arg = Math.pow(10, 0.1 * rp) - 1.0;
            double eps = Math.sqrt(arg);
            double x = 1 / eps;
            double mu = Math.log(x + Math.sqrt((x * x) + 1)); // = arcsinh(x)
            double theta = 0;
            /*
             * arg = mu + 1j*theta = x + jy p = -np.sinh(arg) = = -(cos(y)*sinh(x) +j sin(y)*cosh(x))
             */
            p_x = -Math.cos(theta) * Math.sinh(mu);
            p_y = -Math.sin(theta) * Math.cosh(mu);

            /* gain */
            k = -p_x;
        }

        /* ----------------------------------------------------------------------------------------- */
        /* Pre-warp frequencies for digital filter design */
        /* ----------------------------------------------------------------------------------------- */
        double fsScaled = 2.0;
        double warped1 = 2 * fsScaled * Math.tan((Math.PI * fcScaled1) / fsScaled);
        double warped2 = 2 * fsScaled * Math.tan((Math.PI * fcScaled2) / fsScaled);
        double bw = warped2 - warped1; /* bandwidth */
        double wo = Math.sqrt(warped1 * warped2); /* center frequency */

        /* ----------------------------------------------------------------------------------------- */
        /* transform to bandpass */
        /* ----------------------------------------------------------------------------------------- */
        /* Scale poles and zeros to desired bandwidth */
        /* zeros */
        double zBp = 0;
        /* poles */
        double pLp_x = (p_x * bw) / 2;
        double pLp_y = 0;

        /* Duplicate poles and zeros and shift from baseband to +wo and -wo */
        double pBp_x = pLp_x;
        double arg = (pLp_x * pLp_x) - (wo * wo); /* argument of sqrt */
        double pBp_y = Math.sqrt(Math.abs(arg));

        /* Cancel out gain change from frequency scaling */
        double kBp = k * bw;

        /* ----------------------------------------------------------------------------------------- */
        /* transform to discrete bandpass (bilinear transform) */
        /* ----------------------------------------------------------------------------------------- */
        double fs2 = 2.0 * 2;

        /* Bilinear transform of zeros always results in */
        double zz[] = { 1, -1 };

        /* Bilinear transform of poles */
        /* p_z = (fs2 + pBp) / (fs2 - pBp) */
        double nom_x = fs2 + pBp_x;
        double nom_y = pBp_y;
        double denom_x = fs2 - pBp_x;
        double denom_y = -pBp_y;

        /* rect2pol */
        double mag_nom = Math.sqrt(Math.pow(nom_x, 2) + Math.pow(nom_y, 2));
        double mag_denom = Math.sqrt(Math.pow(denom_x, 2) + Math.pow(denom_y, 2));
        double mag = mag_nom / mag_denom;

        double phase_nom = Math.atan2(nom_y, nom_x);
        double phase_denom = Math.atan2(denom_y, denom_x);
        double phase = phase_nom - phase_denom;

        /* pol2rect */
        double pz_x = mag * Math.cos(phase); /* real */
        double pz_y = mag * Math.sin(phase); /* imag */

        double prod = (denom_x * denom_x) + (denom_y * denom_y); /* product of conj complex number */
        double kz = (kBp * 4) / prod;

        /* ----------------------------------------------------------------------------------------- */
        /* transform to proper form */
        /* ----------------------------------------------------------------------------------------- */
        /* numerator coefficients */
        double b0 = kz * 1; /* coefficient to s^2 */
        double b1 = kz * 0; /* coefficient to s^1 */
        double b2 = kz * -1; /* coefficient to s^0 */

        /* denominator coefficients */
        double a0 = 1; /* coefficient to s^2 */
        double a1 = -2.0 * pz_x; /* coefficient to s^1 */
        double a2 = Math.pow(pz_x, 2) + Math.pow(pz_y, 2); /* coefficient to s^0 */

        /* set block parameter = filter coefficients */
        b0CtrVal.setReal(0, 0, b0);
        b1CtrVal.setReal(0, 0, b1);
        b2CtrVal.setReal(0, 0, b2);
        a1CtrVal.setReal(0, 0, a1);
        a2CtrVal.setReal(0, 0, a2);

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("b0", b0CtrVal);
        this.setImplementationParameterData("b1", b1CtrVal);
        this.setImplementationParameterData("b2", b2CtrVal);
        this.setImplementationParameterData("a1", a1CtrVal);
        this.setImplementationParameterData("a2", a2CtrVal);
        this.setImplementationParameterData("in_old", in_oldCtrVal);
        this.setImplementationParameterData("in_veryold", in_veryoldCtrVal);
        this.setImplementationParameterData("out_old", out_oldCtrVal);
        this.setImplementationParameterData("out_veryold", out_veryoldCtrVal);
    }

    @Override
    public void convertImplementationToMask() throws Exception {

        // Mask Parameter: characteristic                                                                               
        MaskComboBox characteristicMaskVal = 
            (MaskComboBox)this.getMaskParameter("characteristic").getMaskDataType();
        TString characteristicMaskData = 
            (TString)characteristicMaskVal.getData();
        // Mask Parameter: fc1                                                                                          
        MaskDouble fc1MaskVal = 
            (MaskDouble)this.getMaskParameter("fc1").getMaskDataType();
        TNumeric fc1MaskData = 
            (TNumeric)fc1MaskVal.getData();
        // Mask Parameter: fc2                                                                                          
        MaskDouble fc2MaskVal = 
            (MaskDouble)this.getMaskParameter("fc2").getMaskDataType();
        TNumeric fc2MaskData = 
            (TNumeric)fc2MaskVal.getData();
        // Mask Parameter: rc                                                                                           
        MaskDouble rcMaskVal = 
            (MaskDouble)this.getMaskParameter("rc").getMaskDataType();
        TNumeric rcMaskData = 
            (TNumeric)rcMaskVal.getData();
        // Mask Parameter: ts_fact                                                                                      
        MaskDouble ts_factMaskVal = 
            (MaskDouble)this.getMaskParameter("ts_fact").getMaskDataType();
        TNumeric ts_factMaskData = 
            (TNumeric)ts_factMaskVal.getData();

        // Implementation Parameter: b0                                                                                 
        TNumeric b0CtrVal = this.getImplementationParameterData("b0");
        // Implementation Parameter: b1                                                                                 
        TNumeric b1CtrVal = this.getImplementationParameterData("b1");
        // Implementation Parameter: b2                                                                                 
        TNumeric b2CtrVal = this.getImplementationParameterData("b2");
        // Implementation Parameter: a1                                                                                 
        TNumeric a1CtrVal = this.getImplementationParameterData("a1");
        // Implementation Parameter: a2                                                                                 
        TNumeric a2CtrVal = this.getImplementationParameterData("a2");
        // Implementation Parameter: in_old                                                                             
        TNumeric in_oldCtrVal = this.getImplementationParameterData("in_old");
        // Implementation Parameter: in_veryold                                                                         
        TNumeric in_veryoldCtrVal = this.getImplementationParameterData("in_veryold");
        // Implementation Parameter: out_old                                                                            
        TNumeric out_oldCtrVal = this.getImplementationParameterData("out_old");
        // Implementation Parameter: out_veryold                                                                        
        TNumeric out_veryoldCtrVal = this.getImplementationParameterData("out_veryold");

// USERCODE-BEGIN:ConvImplementationToMask                                                                              
        if (true) {
            throw new Exception(
                    "Implementation-to-Mask conversion not implemented for Block 'BandpassBiQ', Implementation 'Float64' in Library 'Filter' due to ambiguous parameters");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("characteristic").setValue(characteristicMaskData.getString());
        this.getMaskParameter("fc1").setValue(fc1MaskData.toFullString());
        this.getMaskParameter("fc2").setValue(fc2MaskData.toFullString());
        this.getMaskParameter("rc").setValue(rcMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
