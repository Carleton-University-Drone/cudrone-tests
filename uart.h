/* 
 * File:   uart.h
 * Author: David
 *
 * Created on August 6, 2016, 7:36 PM
 */
#include "queue.h"

#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    volatile queue transmit_queue;
    volatile queue recive_queue;
    
    void setup_uart(void);
    
    //isr
    void uart_transmit_complete(void);
    void uart_received(void);
    
    //add 
    void uart_send(unsigned char c); //add to send queue
    unsigned char uart_read(void); //read from received queue
    int uart_avalible(void); //More bytes to read
    
#ifdef DEBUG
    void putch(unsigned char data);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

