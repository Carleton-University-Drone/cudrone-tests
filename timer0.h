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

    void enable_timer0(void);
    void timer0_isr(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

