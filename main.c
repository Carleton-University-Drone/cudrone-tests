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
    /* TODO:
     *      Integrate xbee uart debug
     *      Test pulse in and pulse out
     *      communicate with imu
     *      calibrate pid controller
     *      Integrate xbee uart for control
     */
    //Light Registers
    TRISA = 0;
    LATA = 0;    
    setup();

    while (1) {
        LATA =  timer0_millis();
    }
    return;
}

