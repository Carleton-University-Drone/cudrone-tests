/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "configBits.h"
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
        delay(240);
        LATB = 0;
        delay(80);
        if (PORTC & 0x04 == 0x04) {
            LATB = 0x10;
        } else {
            LATB = 0x20;
        }
        delay(80);
        LATB = 0;
        delay(240);
    }
    return;
}

void delay(char c){
    //enable timer
    T0CON = 0b11001111;
    //Clear current count
    TMR0L=0;
    
    //Constantly poll timer to see if it goes surpasses threshold
    while(TMR0L<c);
    
    //disable timer
    T0CON = 0b01000000;
}
