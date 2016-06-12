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
    ANSELbits.ANS6 = 0; //Disable analog to digital conversion RC2
    TRISCbits.TRISC2=1;
    
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
    
    RCONbits.IPEN=1;        //Enable low and high priority interrupts
    INTCON2bits.TMR0IP=0;   //Set low priority
    INTCONbits.TMR0IE=1;    //Enable timer0 overflow interrupts
    INTCONbits.PEIE=1;      //Enable low priority interrupts
    INTCONbits.GIE=1;       //Global Interrupt enable
    INTCONbits.TMR0IF=0;    //Clear interrupt flag
}

void interrupt low_priority low_priority_isr(void){
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){ //Timer0 ISR
        if (PORTCbits.RC2){
            LATB = LATB^0x10;
        }
        else {
            LATB = LATB^0x20;
        }
        INTCONbits.TMR0IF=0; // Clear interrupt flag
    }
}