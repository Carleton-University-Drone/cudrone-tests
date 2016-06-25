#include <xc.h>
#include "interrupt.h"
#include "timer0.h"
#include "pulse_in.h"
void enable_interrupts(void){
    RCONbits.IPEN=1;        //Enable low and high priority interrupts
    INTCON2bits.TMR0IP=0;   //Set low priority
    INTCONbits.PEIE=1;      //Enable low priority interrupts
    INTCONbits.GIE=1;       //Global Interrupt enable
    INTCONbits.TMR0IF=0;    //Clear interrupt flag
}

void interrupt low_priority low_priority_isr(void){
    if (INTCONbits.INT0IF && INTCONbits.INT0IE){
        int0_isr();
        INTCONbits.INT0IF=0;
    }
}

void interrupt high_priority high_priority_isr(void){
    if (INTCONbits.INT0IF && INTCONbits.INT0IE){
        int0_isr();
        INTCONbits.INT0IF=0;
    }
}