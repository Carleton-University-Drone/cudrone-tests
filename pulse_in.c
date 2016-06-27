#include <xc.h>
#include "pulse_in.h"
#include "timer0.h"
void setup_pulse_in(void){
    //Input channel 1 (int0)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCONbits.INT0IE = 1; //Enables the INT0 external interrupt
    INTCON2bits.INTEDG0 = 1; //Interrupt on rising edge (This is the starting state)
    int0_start_time = timer0_millis();
    
    //Input channel 2 (int1)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCON3bits.INT1E = 1; //Enables the INT1 external interrupt
    INTCON3bits.INT1IP = 0; //Low priority
    INTCON2bits.INTEDG1 = 1; //Interrupt on rising edge (This is the starting state)
    int1_start_time = int0_start_time;
    
    //Input channel 3 (int2)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCON3bits.INT2E = 1; // Enables the INT2 external interrupt
    INTCON3bits.INT2IP = 0; //Low priority
    INTCON2bits.INTEDG1 = 1; //Interrupt on rising edge (This is the starting state)
    int2_start_time = int0_start_time;
}

/*
 * Input channel 1 (int0)
 */
 void int0_isr(void){
    if(INTCON2bits.INTEDG0){
        int0_start_time = timer0_millis();
    }
    else {
        int0_width = timer0_millis()-int0_start_time;
    }
    
    INTCON2bits.INTEDG0 = !INTCON2bits.INTEDG0;
}

long channel_1_get_width(void){
    return int0_width;
}

/*
 * Input channel 2 (int1)
 */
 void int1_isr(void){
    if(INTCON2bits.INTEDG1){
        int1_start_time = timer0_millis();
    }
    else {
        int1_width = timer0_millis()-int1_start_time;
    }
    
    INTCON2bits.INTEDG1 = !INTCON2bits.INTEDG1;
}

long channel_2_get_width(void){
    return int1_width;
}

/*
 * Input channel 3 (int2)
 */
 void int2_isr(void){
    if(INTCON2bits.INTEDG2){
        int2_start_time = timer0_millis();
    }
    else {
        int2_width = timer0_millis()-int2_start_time;
    }
    
    INTCON2bits.INTEDG2 = !INTCON2bits.INTEDG2;
}

long channel_3_get_width(void){
    return int2_width;
}