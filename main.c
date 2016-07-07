/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */

#include <xc.h>
#include "setup.h"
#include "pulse_in.h"
#include "timer0.h"
#ifdef DEBUG
#include "tests.h"
#endif

void main(void) {
    
    //Light Registers
    TRISB = 0;
    LATB = 0;    
    setup();

    while (1) {
        //LATB = time_ovf<<4;
    }
    return;
}

