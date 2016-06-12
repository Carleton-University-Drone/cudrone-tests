/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "configBits.h"


void setupTimerInterupt(void);
void interrupt low_priority low_priority_isr(void);

void main(void) {
    //Light Registers
    TRISB = 0;
    LATB = 0;
    //Button Registers
    PORTC = 0;
    TRISC = 0x04;
    
    setupTimerInterupt();
    while (1) {
        //do something else
    }
    return;
}

void setupTimerInterupt(void){
    //enable timer
    T0CON = 0b10001111;
    
    //Clear current count
    TMR0H=0;//this must come first
    TMR0L=0;
    
    
    RCONbits.IPEN=1;        //Enable low and high priority interupts
    INTCON2bits.TMR0IP=0;   //Set low priority
    INTCONbits.TMR0IE=1;    //Enable timer0 oveflow interupts
    INTCONbits.PEIE=1;      //Enable low priority interupts
    INTCONbits.GIE=1;       //Global Interupt enable
    INTCONbits.TMR0IF=0;    //Clear interupt flag
}

void interrupt low_priority low_priority_isr(void){
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){
        LATB = LATB^0x10;
        LATB = LATB^0x20;
        INTCONbits.TMR0IF=0; // Clear interupt flag
    }
}