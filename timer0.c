#include <xc.h>
#include "timer0.h"
void enable_timer0(void){
    //enable timer
    T0CON = 0b10001111;
    
    //Clear current count
    TMR0H=0;//this must come first
    TMR0L=0;
    INTCONbits.TMR0IE=1;    //Enable timer0 overflow interrupts

}

void timer0_isr(void){
    if (PORTCbits.RC2){
        LATB = LATB^0x10;
    }
    else {
        LATB = LATB^0x20;
    }
}