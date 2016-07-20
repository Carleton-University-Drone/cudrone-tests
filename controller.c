#include <xc.h>
#include "pulse_in.h"
#include "pulse_out.h"
#include "controller.h"
void setup_controller(void){
    //Assign inital variables
    pitch_last_value = 0;
    pitch_integral = 0;
    
    roll_last_value = 0;
    roll_integral = 0;
    
    yaw_last_value = 0;
    yaw_integral = 0;
    
    //Setup timer2
    T2CONbits.T2OUTPS = 0; // 1:1 Postscale
    T2CONbits.TMR2ON = 1; //Timer2 is on
    T2CONbits.T2CKPS = 0b11; //Prescaler is 16
    PR2 = timer2_period; //set inital time to compare
    
    //Setup timer2 interrupts
    PIR1bits.TMR2IF = 0; //Clear interrupt flag
    IPR1bits.TMR2IP = 0; //Set low priority interupt
    PIE1bits.TMR2IE = 1; //Enable timer2 interupts
    
}
void controller_step(void){
    /*
     Pitch
     */
    int pitch_error = get_pitch-pulse_in_to_pid(pitch_get_width());
    pitch_integral+=pitch_error;
    #define pitch_derivative (pitch_last_value-pitch_error)
    int pitch_feedback = kp*pitch_error+ki*pitch_integral+kd*pitch_derivative;
    pitch_last_value=pitch_error;
    
    /*
     Roll
     */
    int roll_error = get_roll-pulse_in_to_pid(roll_get_width());
    roll_integral+=roll_error;
    #define roll_derivative (roll_last_value-roll_error)
    int roll_feedback = kp*roll_error+ki*roll_integral+kd*roll_derivative;
    roll_last_value=roll_error;
    
    /*
     Yaw
     */
    int yaw_error = get_yaw-pulse_in_to_pid(yaw_get_width());
    yaw_integral+=yaw_error;
    #define yaw_derivative (yaw_last_value-yaw_error)
    int yaw_feedback = kp*yaw_error+ki*yaw_integral+kd*yaw_derivative;
    yaw_last_value=yaw_error;
    
    //send feedback to motors
    feed_back(pitch_feedback,roll_feedback,yaw_feedback);
}

void feed_back(int pitch, int roll, int yaw){
    //These are the functions for merging the feedback values to the different
    //motors. Currently just a placeholder
    #define M1 (pitch+roll+yaw)
    #define M2 (pitch+roll+yaw)
    #define M3 (pitch+roll+yaw)
    #define M4 (pitch+roll+yaw)
    
    set_M1(pid_to_pulse_out(M1));
    set_M2(pid_to_pulse_out(M2));
    set_M3(pid_to_pulse_out(M3));
    set_M4(pid_to_pulse_out(M4));
}