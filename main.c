/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "config_bits.h"
#include "interrupt.h"
#include "timer0.h"
#include "setup.h"
#include "pulse_in.h"
#ifdef DEBUG
#include "tests.h"
#endif

void main(void) {
    
    //Light Registers
    TRISB = 0;
    LATB = 0;
    //Button Registers
    PORTC = 0;
    ANSELbits.ANS6 = 0; //Disable analog to digital conversion RC2
    TRISCbits.TRISC2=1;
    
    setup();

    while (1) {
        //main loop
    }
    return;
}

