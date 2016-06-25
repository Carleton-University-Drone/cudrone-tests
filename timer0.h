/* 
 * File:   timer0.h
 * Author: David
 *
 * Created on June 20, 2016, 8:38 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif
    //private
    long time_ovf;
    
    void enable_timer0(void);
    void timer0_isr(void);
    long timer0_millis(void); //Returns the current time in number of 0.1 miliseconds
                              //that have passed since enable_timer0 

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

