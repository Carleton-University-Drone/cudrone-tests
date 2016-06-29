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
    
    //Input channel 1 (int0)
    //private
    long int0_start_time;
    long int0_width;
    
    void int0_isr(void);
    long channel_1_get_width(void);

    //Input channel 2 (int1)
    //private
    long int1_start_time;
    long int1_width;
    
    void int1_isr(void);
    long channel_2_get_width(void);

    //Input channel 3 (int2)
    //private
    long int2_start_time;
    long int2_width;
    
    void int2_isr(void);
    long channel_3_get_width(void);
    
    //Input channel 4 (cmr1)
    //private
    long cmr1_start_time;
    long cmr1_width;
    
    void cmr1_isr(void);
    long channel_4_get_width(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PULSEIN_H */

