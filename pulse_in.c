#include <xc.h>
#include "pulse_in.h"
#include "timer0.h"
void setup_pulse_in(void){
    INTCONbits.INT0IE = 1; //Enables the INT0 external interrupt
    INTCON2bits.INTEDG0 = 1; //Interrupt on rising edge (This is the starting state))
    int0_start_time = timer0_millis();
}

void int0_isr(void){
    if(INTCON2bits.INTEDG0){
        int0_start_time = timer0_millis();
    }
    else {
        int0_width = timer0_millis()-int0_start_time;
    }
    
    INTCON2bits.INTEDG0 = !INTCON2bits.INTEDG0;
}

long int0_get_width(void){
    return int0_width;
}
