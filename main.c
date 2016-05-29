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
    TRISB = 0;
    LATB = 0;
    while (1) {
        LATB++;
        delay(100);
    }
    return;
}

void delay(char c){
    //enable timer
    T0CON = 0b11001011;
    //Clear current count
    TMR0L=0;
    
    //Constantly poll timer to see if it goes surpasses threshold
    while(TMR0L<c);
    
    //disable timer
    T0CON = 0b01000000;
}