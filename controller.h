/* 
 * File:   controller.h
 * Author: David
 *
 * Created on July 16, 2016, 11:14 AM
 */
#include "timer0.h"
#include "pulse_in.h"
#include "pulse_out.h"

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif

    //The are the pid constants for the drone, as the drone is symetrical, the
    //pitch, roll and yaw will have the same coefficients
    //These are kinda constants but as i might want to modify them over radio so
    //I will leave them as variables for this reason
    int kp = 1; //Proportional term coefficient
    int ki = 0; //Integral term coefficient
    int kd = 0; //Derivative term coefficient
    int timer2_period = 256; //timer2 period: time between pid steps
    
    //Variables for pitch
    int pitch_last_value;
    int pitch_integral;
    
    //Variables for roll
    int roll_last_value;
    int roll_integral;
    
    //Variables for yaw
    int yaw_last_value;
    int yaw_integral;
    
    //Inline helper functions
    
    inline int pulse_in_to_pid(int in){ //this function converts and scales the value outputed by pulse in
        return in;                      //to the format used by the pid
    }
    
    inline int pid_to_pulse_out(int out){ // Converts the output from the pid to the correct scale
        return out;                       //for the pulse out functions
    }
    
    inline int get_pitch(void) { // gets the current pitch from the IMU
        return 0;
    }
    
    inline int get_roll(void) { // gets the current roll from the IMU
        return 0;
    }
    
    inline int get_yaw(void) { // gets the current yaw from the IMU
        return 0;
    }
    
    //Main pid logic
    
    void setup_controller(void); //Sets up everything needed to run controller
    void controller_step(void); //Runs one step of the PID simulation, it is timer2 isr
    void feed_back(int pitch, int roll, int yaw); //Called by controller_step. Given the plant
                                                  //output from the pid this merges the values 
                                                  //for the different diretions into output to
                                                  //the motor
#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

