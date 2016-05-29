/*
 * File:   main.c
 * Author: Thompson
 *
 * Created on May 29, 2016, 4:42 PM
 */


#include <xc.h>
#include "configBits.h"
void main(void) {
    int loop;
    TRISB = 0;
    LATB = 0;
    while (1) {
        loop = 0;
        LATB++;
        while (loop < 30000) {
            loop++;
        }
    }
    return;
}

void delay(int c){
    for(;c>0;c--);
}