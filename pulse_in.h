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
    
    //private
    long int0_start_time;
    long int0_width;
    
    void setup_pulse_in(void);
    void int0_isr(void);
    long int0_get_width(void);


#ifdef	__cplusplus
}
#endif

#endif	/* PULSEIN_H */

