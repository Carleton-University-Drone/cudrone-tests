/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */


#include <xc.h>
#include "configBits.h"
void main(void) {
    TRISB = 0;
    LATB = 0;
    while (1) {
        LATB = 0x10;
        delay(30000);
        LATB = 0;
        delay(10000);
        LATB = 0x10;
        delay(10000);
        LATB = 0;
        delay(30000);
    }
    return;
}

void delay(int c){
    for(;c>0;c--);
}