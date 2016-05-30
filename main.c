/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "configBits.h"

#define DELAY_TIME 100

void delay(char c);
void main(void) {
    //Light Registers
    TRISB = 0;
    LATB = 0;
    //Button Registers
    PORTC = 0;
    TRISC = 0x04;
    while (1) {
        if (PORTC & 0x04 == 0x04) {
            LATB = 0x10;
        } else {
            LATB = 0x20;
        }
        delay(3*DELAY_TIME);
        LATB = 0;
        delay(DELAY_TIME);
        if (PORTC & 0x04 == 0x04) {
            LATB = 0x10;
        } else {
            LATB = 0x20;
        }
        delay(DELAY_TIME);
        LATB = 0;
        delay(3*DELAY_TIME);
    }
    return;
}

void delay(char c){
    //enable timer
    T0CON = 0b10001111;
    
    //Clear current count
    TMR0H=0;//this must come first
    TMR0L=0;
    
    //Constantly poll timer to see if it goes surpasses threshold
    while(TMR0H<c)TMR0L;
    
    //disable timer
    T0CON = 0b00000000;
}
