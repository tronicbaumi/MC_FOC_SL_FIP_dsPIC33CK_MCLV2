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
import at.lcm.x2c.utils.QFormat;
// USERCODE-END:Imports                                                                                                 

@SuppressWarnings("unused")
public class ConvFnc_LowpassBiQ_FiP16 extends JavaConversionFunction {
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
        // Implementation Parameter: sfrb0                                                                              
        TNumeric sfrb0CtrVal = this.getImplementationParameterData("sfrb0");
        // Implementation Parameter: sfrb1                                                                              
        TNumeric sfrb1CtrVal = this.getImplementationParameterData("sfrb1");
        // Implementation Parameter: sfrb2                                                                              
        TNumeric sfrb2CtrVal = this.getImplementationParameterData("sfrb2");
        // Implementation Parameter: sfra1                                                                              
        TNumeric sfra1CtrVal = this.getImplementationParameterData("sfra1");
        // Implementation Parameter: sfra2                                                                              
        TNumeric sfra2CtrVal = this.getImplementationParameterData("sfra2");
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
            throw new Exception("Wrong Input! Cutoff frequency was choosen to big! Should be less then fs/2.");
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
            /* poles */
            p_x = -HALF_SQRT2;
            p_y = HALF_SQRT2;
            /* gain */
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
                throw new Exception("Division by zero! Choose a stopband ripple different from zero!");
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
        /* transform to lowpass with proper cut-off frequency */
        /* ----------------------------------------------------------------------------------------- */
        double relDegree = 0;
        if (characteristicMaskVal.getValue().equals("Chebyshev II")) {
            relDegree = 0;
            /* Scale all points radially from origin to shift cutoff frequency */
            /*
             * zeros z_lp = warped * z
             */
            z_x = warped * z_x;
            z_y = warped * z_y;
        } else {
            relDegree = 2.0; /* =len(p)-len(z) */
        }
        /* Scale all points radially from origin to shift cutoff frequency */
        /*
         * z_lp = warped * z p_lp = warped * p
         */

        /* poles digital lowpass */
        p_x = warped * p_x;
        p_y = warped * p_y;
        /* gain digital lowpass */
        k = k * Math.pow(warped, relDegree);

        /* ----------------------------------------------------------------------------------------- */
        /* transform to discrete lowpass (bilinear transform) */
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
        if (characteristicMaskVal.getValue().equals("Chebyshev II")) {
            nom_x = fs2 + z_x;
            nom_y = z_y;
            denom_x = fs2 - z_x;
            denom_y = -z_y;
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

        } else {
            zz_x = -1;
            zz_y = 0;
            prod_z = 1;
        }

        /* poles */
        /* p_z = (fs2 + p) / (fs2 - p) */
        double pz_x = 0;
        double pz_y = 0;

        nom_x = fs2 + p_x;
        nom_y = p_y;
        denom_x = fs2 - p_x;
        denom_y = -p_y;

        /* rect2pol */
        mag_nom = Math.sqrt(Math.pow(nom_x, 2) + Math.pow(nom_y, 2));
        mag_denom = Math.sqrt(Math.pow(denom_x, 2) + Math.pow(denom_y, 2));
        mag = mag_nom / mag_denom;

        phase_nom = Math.atan2(nom_y, nom_x);
        phase_denom = Math.atan2(denom_y, denom_x);
        phase = phase_nom - phase_denom;

        /* pol2rect */
        pz_x = mag * Math.cos(phase); /* real */
        pz_y = mag * Math.sin(phase); /* imag */

        double prod_p = (denom_x * denom_x) + (denom_y * denom_y); /* product of conjugate complex number */

        /* gain */
        double kz = (k * prod_z) / prod_p;

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
        final int BITS = 16;

        /* determine numerator shift factor */
        double sfrb0 = Double.valueOf(QFormat.getQFormat(b0, BITS, true));
        double sfrb1 = Double.valueOf(QFormat.getQFormat(b1, BITS, true));
        double sfrb2 = Double.valueOf(QFormat.getQFormat(b2, BITS, true));
        sfrb0CtrVal.setReal(0, 0, sfrb0);
        sfrb1CtrVal.setReal(0, 0, sfrb1);
        sfrb2CtrVal.setReal(0, 0, sfrb2);

        /* determine denominator shift factor */
        double sfra1 = Double.valueOf(QFormat.getQFormat(a1, BITS, true));
        double sfra2 = Double.valueOf(QFormat.getQFormat(a2, BITS, true));
        sfra1CtrVal.setReal(0, 0, sfra1);
        sfra2CtrVal.setReal(0, 0, sfra2);

        /* set coefficients */
        b0CtrVal.setReal(0, 0, QFormat.getQValue(b0, (int) sfrb0, BITS, true));
        b1CtrVal.setReal(0, 0, QFormat.getQValue(b1, (int) sfrb1, BITS, true));
        b2CtrVal.setReal(0, 0, QFormat.getQValue(b2, (int) sfrb2, BITS, true));
        a1CtrVal.setReal(0, 0, QFormat.getQValue(a1, (int) sfra1, BITS, true));
        a2CtrVal.setReal(0, 0, QFormat.getQValue(a2, (int) sfra2, BITS, true));

// USERCODE-END:ConvMaskToImplementation                                                                                
        this.setImplementationParameterData("b0", b0CtrVal);
        this.setImplementationParameterData("b1", b1CtrVal);
        this.setImplementationParameterData("b2", b2CtrVal);
        this.setImplementationParameterData("a1", a1CtrVal);
        this.setImplementationParameterData("a2", a2CtrVal);
        this.setImplementationParameterData("sfrb0", sfrb0CtrVal);
        this.setImplementationParameterData("sfrb1", sfrb1CtrVal);
        this.setImplementationParameterData("sfrb2", sfrb2CtrVal);
        this.setImplementationParameterData("sfra1", sfra1CtrVal);
        this.setImplementationParameterData("sfra2", sfra2CtrVal);
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
        // Implementation Parameter: sfrb0                                                                              
        TNumeric sfrb0CtrVal = this.getImplementationParameterData("sfrb0");
        // Implementation Parameter: sfrb1                                                                              
        TNumeric sfrb1CtrVal = this.getImplementationParameterData("sfrb1");
        // Implementation Parameter: sfrb2                                                                              
        TNumeric sfrb2CtrVal = this.getImplementationParameterData("sfrb2");
        // Implementation Parameter: sfra1                                                                              
        TNumeric sfra1CtrVal = this.getImplementationParameterData("sfra1");
        // Implementation Parameter: sfra2                                                                              
        TNumeric sfra2CtrVal = this.getImplementationParameterData("sfra2");
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
                    "Implementation-to-Mask conversion not implemented for Block 'LowpassBiQ', Implementation 'FiP16' in Library 'Filter' due to ambiguous parameters");
        }
// USERCODE-END:ConvImplementationToMask                                                                                
        this.getMaskParameter("characteristic").setValue(characteristicMaskData.getString());
        this.getMaskParameter("fc").setValue(fcMaskData.toFullString());
        this.getMaskParameter("rp").setValue(rpMaskData.toFullString());
        this.getMaskParameter("rs").setValue(rsMaskData.toFullString());
        this.getMaskParameter("ts_fact").setValue(ts_factMaskData.toFullString());
    }
}
