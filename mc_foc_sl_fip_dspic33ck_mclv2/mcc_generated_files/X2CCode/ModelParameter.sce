// Scilab script file to store Model parameters
// This file is automatically executed by initProject.sce
// initScript.sce and this script is executed automatically, if model is opened from MPLAB X MCC X2C library.

// Simulation settings
//endTime     = 5;
//stepSize    = 1.0E-2; 
X2C_sampleTime =100E-6;//10kHz control loop

sim_step = 0.0001;
sim_buffer = 250000;


// POWERSTAGE DATA
U_DCLINK = 24;
Vbus = U_DCLINK;
Rshunt = 0.025;
Igain = -15;
I_MAX = 3.95;


// MOTOR parameters for PLL
MotorLs = 0.34;
MotorRs = 0.30;
BEMF_D_UDC = 0.65;
PLL_INT = 800;

// Speed PI
SpeedKp = 2;
SpeedKi = 1;
SpeedDemandRate = 0.2;

// Current PI
PIFluxKp =  0.8;
PIFluxKi = 0.5;

PITorqueKp = 0.8;
PITorqueKi = 0.5


// MOTORDATA for MOTOR SIMULATION MODEL
Nm_ozin = 7.061552e-3;
KRPM_rads = 0.060/2/%pi;

Rs = 0.78;
Ld = 707e-6;
Lq = 690e-6;
Kell = 6.2;     //7.24;
n_p = 5;        // number of polepairs




J = 0.000628 * Nm_ozin;   // inertia
cf = 0;
chy = 0;
d = 0;
ced = 0;
ded = 0;

alphaCU = 0;
alphaPM = 0;
Temp_nom = 25;
omega_m0 = 0;
theta_m0 = 0;
psi_pm = Kell/sqrt(3)*60/(2*%pi*1000)/n_p;
theta_r0 = theta_m0*2*%pi*n_p;
omega_r0 = omega_m0/60*2*%pi*n_p;


// Umrechnen auf Rechnenwerte fuer Modell
Ld = Ld/2;
Lq = Lq/2;
Rs = Rs/2;


// initalize input for simulation
exec("./gen_inputs.sci");
exec("./qei_sim.sce");
exec("./qei_sim2.sce");

