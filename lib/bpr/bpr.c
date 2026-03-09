// Basis physics regulators

// Types
// Pressure Regulators
// Voltage/Current Regulators
// Temperature Regulators
// Flow Regulators
// Speed/Frequency Regulators
// Force/Torque Regulators
// Radiation Regulators
// Vaccuum Regulators



void pressure_regulator(){
    

}




//////////////////////////////////////

// Speed regulator
// rotation=>
// currspeed=>
// accelerometer=> raw input 4mA - 20mA need to convert this, raw i 1V - 5V
// we've done this
// v = raw_adc/resolution * 5V 
// gval = (v - 3) / 2 * g_max
// 
// Exponential moving average
//

float speed_regulator(float gval, float pitch, float currv, float prefv){
    // if gval > triggermax => speed-increment
    // if gval < triggermin => speed+increment
    // v = ∫a , dx/dt = v or dv/dt = a
    // a_real = a_measured - 9.81 · sin(pitch)
    //
    
    float acc = gval - 9.81f * sinf(pitch);
    float dt = 0.01f; // time measurement aka loop frequency
    float estv  = currv + acc * dt;
    
    float err = prefv - estv;
    float Kp = 0.01f // control sensitivity
    float corr = 1.0f + Kp * err;

    if (corr > 1.05) return 1.05f;
    if (corr < 0.95) return 0.95f;
    
}
