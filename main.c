/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "configBits.h"
void delay(int c);
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
        delay(30000);
        LATB = 0;
        delay(10000);
        if (PORTC & 0x04 == 0x04) {
            LATB = 0x10;
        } else {
            LATB = 0x20;
        }
        delay(10000);
        LATB = 0;
        delay(30000);
    }
    return;
}

void delay(int c){
    for(;c>0;c--);
}