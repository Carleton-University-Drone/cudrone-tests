#include <xc.h>
#include "timer0.h"
void enable_timer0(void){
    //enable timer
    T0CONbits.TMR0ON = 1; //Timer0 On/Off Control bit (on))
    T0CONbits.T08BIT = 0; //Timer0 8-bit/16-bit Control bit (16bit)
    T0CONbits.T0CS = 0; //Timer0 Clock Source Select bit (Internal instruction cycle clock)
    T0CONbits.PSA = 0; // Timer0 Prescaler Assignment bit (Enable Prescaller)
    T0CONbits.T0PS = 0b111; //Set prescaler to 256
    INTCON2bits.TMR0IP = 1; //Set high priority interrupt
    //Clear current count
    TMR0H=0;//this must come first
    TMR0L=0;
    INTCON2bits.TMR0IP=0;   //Set low priority
    INTCONbits.TMR0IF=0;    //Clear interrupt flag
    INTCONbits.TMR0IE=1;    //Enable timer0 overflow interrupts

    time_ovf = 0;
}

void timer0_isr(void){
    time_ovf++;
}

//Returns the current time in number of 0.1 milliseconds
//that have passed since enable_timer0 
unsigned int timer0_millis(void){
    unsigned long m = 0;
    m=time_ovf;
    m=m<<16;
    m+=TMR0L;
    m+=TMR0H<<8;
    m=(m*131)>>15; //This magic number is the scale factor for converting between
                // the timer values and the number of milli seconds.
                // The formula is 
                //    (clockPrscaller)/(Clock frequency) * 10000 (s->0.1 ms)
                //I didn't use a constant to multiply because the order of
                //operations are important, so minimize the division error.
                //Also since the processor doesn't have a division module I used
                //mutliply by a constant then big shift for the desired effect
                //these is some rounding error but it is not significant
    return m;
}