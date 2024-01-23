/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 2584 $
 * $LastChangedDate:: 2022-05-03 15:06:23 +0200#$
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
public class ConvFnc_HighpassBiQ_Float32 extends JavaConversionFunction {
    private static final long serialVersionUID = 1L;

    @Override
    public void convertMaskToImplementation() throws Exception {

        // Mask Parameter: characteristic                                                                               
        MaskComboBox characteristicMaskVal = 
            (MaskComboBox)this.getMaskParameter("characteristic").getMaskDataType();
        TString characteristicMaskData = 
            (TString)characteristicMaskVal.getData();
        // Mask Parameter: fc                                                                                           
        MaskDouble fcMaskVal = 
            (MaskDouble)this.getMaskParameter("fc").getMaskDataType();
        TNumeric fcMaskData = 
            (TNumeric)fcMaskVal.getData();
        // Mask Parameter: rp                                                                                           
        MaskDouble rpMaskVal = 
            (MaskDouble)this.getMaskParameter("rp").getMaskDataType();
        TNumeric rpMaskData = 
            (TNumeric)rpMaskVal.getData();
        // Mask Parameter: rs                                                                                           
        MaskDouble rsMaskVal = 
            (MaskDouble)this.getMaskParameter("rs").getMaskDataType();
        TNumeric rsMaskData = 
            (TNumeric)rsMaskVal.getData();
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
        double fc = Math.abs(Double.valueOf(fcMaskVal.getValue()));
        /* get sample time */
        double ts_fact = Double.valueOf(ts_factMaskVal.getValue()).intValue();
        if (ts_fact <= 0) {
            ts_fact = 1;
        }
        double Ts = ts_fact * this.getDedicatedBlock().getModel().getSampleTime();

        /* get sampling frequency */
        double fs = 1 / Ts;

        /* validate input */
        if ((2 * fc) >= fs) {
            throw new Exception("Wrong Input! Cut-Off frequency was choosen to big! Should be less then fs/2.");
        }

        /* Normalize frequency */
        double fcScaled = (2 * fc) / fs;

        /* ----------------------------------------------------------------------------------------- */
        /* Get analog lowpass prototype */
        /* ----------------------------------------------------------------------------------------- */
        final double HALF_SQRT2 = Math.sqrt(2) / 2;
        final double HALF_SQRT3 = Math.sqrt(3) / 2;
        final double SQRT2 = Math.sqrt(2);
        double z_x = 0;
        double z_y = 0;
        double p_x = 0;
        double p_y = 0;
        double k = 0;
        if (characteristicMaskVal.getValue().equals("Butterworth")) {
            p_x = -HALF_SQRT2;
            p_y = HALF_SQRT2;
            k = 1.0;
        } else if (characteristicMaskVal.getValue().equals("Chebyshev I")) {
            double rp = Math.abs(Double.valueOf(rpMaskVal.getValue()));
            if (rp == 0) {
                throw new Exception("Division by zero! Choose a passband ripple different from zero!");
            } else if (rp < 0) {
                throw new Exception("Negative ripple value given! Enter a positive passband ripple value!");
            }

            /* poles */
            double arg = Math.pow(10, 0.1 * rp) - 1.0;
            double eps = Math.sqrt(arg);
            double x = 1 / eps;
            double mu = 0.5 * Math.log(x + Math.sqrt((x * x) + 1)); // = arcsinh(x)
            double theta = Math.PI / 4;
            /*
             * arg = mu + 1j*theta = x + jy p = -np.sinh(arg) = = -(cos(y)*sinh(x) +j sin(y)*cosh(x))
             */
            p_x = -Math.cos(theta) * Math.sinh(mu);
            p_y = -Math.sin(theta) * Math.cosh(mu);

            /* gain */
            double prod_p = (p_x * p_x) + (p_y * p_y);
            k = prod_p / (Math.sqrt(1 + (eps * eps)));

        } else if (characteristicMaskVal.getValue().equals("Chebyshev II")) {
            double rs = Math.abs(Double.valueOf(rsMaskVal.getValue()));
            if (rs == 0) {
                throw new Exception("Division by zero! Choose a passband ripple different from zero!");
            } else if (rs < 0) {
                throw new Exception("Negative ripple value given! Enter a positive stopband ripple value!");
            }
            double arg = Math.pow(10, 0.1 * rs) - 1.0;
            double de = 1 / Math.sqrt(arg);
            double x = 1 / de;
            double mu = Math.log(x + Math.sqrt((x * x) + 1)) / 2; // = arcsinh(x)

            /* zeros */
            z_x = 0;
            z_y = -SQRT2;

            /* poles */
            p_x = -HALF_SQRT2;
            p_y = HALF_SQRT2;
            p_x = Math.sinh(mu) * p_x;
            p_y = Math.cosh(mu) * p_y;

            /* calculate p = 1/p */
            double scale_p = (p_x * p_x) + (p_y * p_y); /* square of magnitude */
            p_x = p_x / scale_p;
            p_y = -p_y / scale_p;

            /* gain */
            double prod_p = (p_x * p_x) + (p_y * p_y);
            double prod_z = (z_x * z_x) + (z_y * z_y);
            k = prod_p / prod_z;
        } else if (characteristicMaskVal.getValue().equals("Bessel")) {
            /* poles */
            p_x = -1.5;
            p_y = HALF_SQRT3;
            /* gain */
            k = 3.0;
        }

        /* ----------------------------------------------------------------------------------------- */
        /* Pre-warp frequencies for digital filter design */
        /* ----------------------------------------------------------------------------------------- */
        double fsScaled = 2.0;
        double warped = 2 * fsScaled * Math.tan((Math.PI * fcScaled) / fsScaled);

        /* ----------------------------------------------------------------------------------------- */
        /* transform to highpass */
        /* ----------------------------------------------------------------------------------------- */
        double relDegree = 0;

        /* zeros */
        double zHp_x = 0;
        double zHp_y = 0;
        double scale_z = 0;
        if (characteristicMaskVal.getValue().equals("Chebyshev II")) {
            relDegree = 0;
            /*
             * Invert positions radially about unit circle to convert LPF to HPF Scale all points radially from origin
             * to shift cutoff frequency z_hp = warped / z
             */
            scale_z = (z_x * z_x) + (z_y * z_y);
            zHp_x = (warped * z_x) / scale_z;
            zHp_y = (warped * z_y) / scale_z;
        } else {
            relDegree = 2.0; /* =len(p)-len(z) */
            zHp_x = 0;
            zHp_y = 0;
            scale_z = 1;
        }

        /* poles */
        /*
         * Invert positions radially about unit circle to convert LPF to HPF Scale all points radially from origin to
         * shift cutoff frequency p_hp = warped / p
         */
        double scale_p = (p_x * p_x) + (p_y * p_y); /* square of magnitude */
        double pHp_x = (warped * p_x) / scale_p; /* real part of conj poles of highpass */
        double pHp_y = (warped * p_y) / scale_p; /* magnitude of imag. part of conj poles of highpass */

        /* gain */
        /*
         * Cancel out gain change caused by inversion k_hp = k * np.real(np.prod(-z) / np.prod(-p))
         */
        double k_hp = (k * scale_z) / scale_p;

        /* ----------------------------------------------------------------------------------------- */
        /* transform to discrete highpass (bilinear transform) */
        /* ----------------------------------------------------------------------------------------- */
        double fs2 = 2.0 * 2;
        double zz_x = 0;
        double zz_y = 0;
        double nom_x = 0;
        double nom_y = 0;
        double denom_x = 0;
        double denom_y = 0;
        double mag_nom;
        double mag_denom;
        double mag;
        double phase_nom;
        double phase_denom;
        double phase;
        double prod_z = 0;

        /*
         * zeros z_z = (fs2 + z) / (fs2 - z)
         */
        nom_x = fs2 + zHp_x;
        nom_y = zHp_y;
        denom_x = fs2 - zHp_x;
        denom_y = -zHp_y;
        prod_z = (denom_x * denom_x) + (denom_y * denom_y); /* product of conjugate complex number */

        /* rect2pol */
        mag_nom = Math.sqrt(Math.pow(nom_x, 2) + Math.pow(nom_y, 2));
        mag_denom = Math.sqrt(Math.pow(denom_x, 2) + Math.pow(denom_y, 2));
        mag = mag_nom / mag_denom;

        phase_nom = Math.atan2(nom_y, nom_x);
        phase_denom = Math.atan2(denom_y, denom_x);
        phase = phase_nom - phase_denom;

        /* pol2rect */
        zz_x = mag * Math.cos(phase); /* real */
        zz_y = mag * Math.sin(phase); /* imag */

        /* poles */
        /* p_z = (fs2 + p) / (fs2 - p) */
        nom_x = fs2 + pHp_x;
        nom_y = pHp_y;
        denom_x = fs2 - pHp_x;
        denom_y = -pHp_y;

        /* rect2pol */
        mag_nom = Math.sqrt(Math.pow(nom_x, 2) + Math.pow(nom_y, 2));
        mag_denom = Math.sqrt(Math.pow(denom_x, 2) + Math.pow(denom_y, 2));
        mag = mag_nom / mag_denom;

        phase_nom = Math.atan2(nom_y, nom_x);
        phase_denom = Math.atan2(denom_y, denom_x);
        phase = phase_nom - phase_denom;

        /* pol2rect */
        double pz_x = mag * Math.cos(phase); /* real */
        double pz_y = mag * Math.sin(phase); /* imag */

        double prod_p = (denom_x * denom_x) + (denom_y * denom_y); /* product of conjugate complex number */

        /* gain */
        double kz = (k_hp * prod_z) / prod_p;

        /* ----------------------------------------------------------------------------------------- */
        /* transform to proper form */
        /* ----------------------------------------------------------------------------------------- */
        /* numerator coefficients */
        double b0 = kz * 1; /* coefficient to s^2 */
        double b1 = kz * -2.0 * zz_x; /* coefficient to s^1 */
        double b2 = kz * ((zz_x * zz_x) + (zz_y * zz_y)); /* coefficient to s^0 */

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
        // Mask Parameter: fc                                                                                           
        MaskDouble fcMaskVal = 
            (MaskDouble)this.getMaskParameter("fc").getMaskDataType();
        TNumeric fcMaskData = 
            (TNumeric)fcMaskVal.getData();
        // Mask Parameter: rp                                                                                           
        MaskDouble rpMaskVal = 
            (MaskDouble)this.getMaskParameter("rp").getMaskDataType();
        TNumeric rpMaskData = 
            (TNumeric)rpMaskVal.getData();
        // Mask Parameter: rs                                                                                           
        MaskDouble rsMaskVal = 
            (MaskDouble)this.getMaskParameter("rs").getMaskDataType();
        TNumeric rsMaskData = 
            (TNumeric)rsMaskVal.getData();
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
                    "Implementation-to-Mask conversion not implemented for Block 'HighpassBiQ', Implementation 'Float32' in Library 'Filter' due to ambiguous parameters");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("characteristic").setValue(characteristicMaskData.getString());
        this.getMaskParameter("fc").setValue(fcMaskData.toFullString());
        this.getMaskParameter("rp").setValue(rpMaskData.toFullString());
        this.getMaskParameter("rs").setValue(rsMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
