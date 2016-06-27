/* 
 * File:   interupt.h
 * Author: David
 *
 * Created on June 20, 2016, 8:05 PM
 */

#ifndef INTERUPT_H
#define	INTERUPT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void enable_interrupts(void);
    void interrupt low_priority low_priority_isr(void);
    void interrupt high_priority high_priority_isr(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERUPT_H */

