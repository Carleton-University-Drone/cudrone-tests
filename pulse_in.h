/* 
 * File:   pulseIn.h
 * Author: David
 *
 * Created on June 24, 2016, 9:31 PM
 */

#ifndef PULSE_IN_H
#define	PULSE_IN_H

#ifdef	__cplusplus
extern "C" {
#endif
    void setup_pulse_in(void);
    
    //Pitch input (int0)
    //private
    volatile unsigned int int0_start_time;
    volatile unsigned int int0_width;
    
    void int0_isr(void);
    unsigned int pitch_get_width(void);

    //Roll input (int1)
    //private
    volatile unsigned int int1_start_time;
    volatile unsigned int int1_width;
    
    void int1_isr(void);
    unsigned int roll_get_width(void);

    //Yaw input (int2)
    //private
    volatile unsigned int int2_start_time;
    volatile unsigned int int2_width;
    
    void int2_isr(void);
    unsigned int yaw_get_width(void);
    
    //Throttle input (cmr1)
    //private
    volatile unsigned int cmr1_start_time;
    volatile unsigned int cmr1_width;
    
    void cmr1_isr(void);
    unsigned int throttle_get_width(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PULSEIN_H */

