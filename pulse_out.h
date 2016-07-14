/* 
 * File:   pulse_out.h
 * Author: David
 *
 * Created on July 11, 2016, 8:29 PM
 */

#ifndef PULSE_OUT_H
#define	PULSE_OUT_H

#ifdef	__cplusplus
extern "C" {
#endif
    #define DUTY_CYCLE 200*200 //20 ms duty cycle period, multiplied by same constant from millis_to_timer1
    int channel; //the currently outputting channel (0=none,1=M1,2=M2,3=M3,4=M4)
    void setup_pulse_out(void); //setup ECCP

    //Cycles between the pulse on the different channels
    void timer1_isr(void);
    
    static inline void load_timer1(int value){ //This function loads the 16 bit timer1
                                        //with a 16 bit value through two
                                        //8 bit registers
        TMR1L = value;
        TMR1H = value>>8;
    }
    
    //Converts the number of 0.1 ms the pulse width is to the register value for the timer
    static inline int millis_to_timer1 (int millis){
         return millis*200;
                 //This magic number is a constant used to determine the register
                 //values for timer1. The formula is 
                 // (1/40000)*Fosc/timer1_prescale
    }
    
    /*
     * Input channel M1 (RC5)
     */
    volatile int M1_width;
    static inline void set_M1(int millis){
        M1_width = millis_to_timer1(millis);
    }
    
    /*
     * Input channel M2 (RC4)
     */
    volatile int M2_width;
    static inline void set_M2(int millis){ 
        M2_width = millis_to_timer1(millis);
    }
    
    /*
     * Input channel M3 (RC3)
     */
    volatile int M3_width;
    static inline void set_M3(int millis){
        M3_width = millis_to_timer1(millis);
    }
    
    /*
     * Input channel M4 (RC2)
     */
    volatile int M4_width;
    static inline void set_M4(int millis){
        M4_width = millis_to_timer1(millis);
    }
    
#ifdef	__cplusplus
}
#endif

#endif	/* PULSE_OUT_H */

