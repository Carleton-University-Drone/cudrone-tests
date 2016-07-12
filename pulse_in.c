#include <xc.h>
#include "pulse_in.h"
#include "timer0.h"
void setup_pulse_in(void){
    //Input channel 1 (int0)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCONbits.INT0IE = 1; //Enables the INT0 external interrupt
    INTCON2bits.INTEDG0 = 1; //Interrupt on rising edge (This is the starting state)
    ANSELbits.ANS0 = 0; //Digital input buffer of RA0 is enabled
    int0_start_time = timer0_millis();
    
    //Input channel 2 (int1)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCON3bits.INT1E = 1; //Enables the INT1 external interrupt
    INTCON3bits.INT1IP = 1; //High priority
    INTCON2bits.INTEDG1 = 1; //Interrupt on rising edge (This is the starting state)
    ANSELbits.ANS1 = 0; //Digital input buffer of RA1 is enabled
    int1_start_time = int0_start_time;
    
    //Input channel 3 (int2)
    TRISAbits.RA0 = 1; //Set io port to input
    INTCON3bits.INT2E = 1; // Enables the INT2 external interrupt
    INTCON3bits.INT2IP = 1; //High priority
    INTCON2bits.INTEDG1 = 1; //Interrupt on rising edge (This is the starting state)
    ANSELbits.ANS2 = 0; //Digital input buffer of RA2 is enabled
    int2_start_time = int0_start_time;
    
    //Input channel 4 (CMR1)
        //Setup voltage reference
    VREFCON0bits.FVR1EN = 1; //Fixed Voltage reference is enabled
    VREFCON0bits.FVR1S0 = 1; VREFCON0bits.FVR1S1 = 0; //Fixed Voltage level is 2.048 V
     //Fixed Voltage level is 2.048 V
        //Setup Comparator
    ANSELbits.ANS5 = 1; // Digital input buffer of RC1 is disabled
    TRISCbits.RC1 = 1; // pin configured as an input (tri-stated)
    CM1CON0bits.C1ON = 1; //Comparator C1 is enabled
    CM1CON0bits.C1OE = 0; //C1OUT is internal only
    CM1CON0bits.C1POL = 1; //C1OUT logic is inverted (Thus a 1 on out corresponds to a high value)
    CM1CON0bits.C1SP = 1; //C1 operates in normal power, higher speed mode
    CM1CON0bits.C1R = 1; //C1V IN + connects to C1V REF output
    CM1CON0bits.C1CH = 0b01; //C12IN1- pin of C1 connects to C1V IN -
        //Setup interrupts
    PIE2bits.C1IE = 1; //Comparator C1 Interrupt Enable bit (Enabled))
    IPR2bits.C1IP = 1; //High priority
    PIR2bits.C1IF = 0; //Clear interrupt flag
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

unsigned int pitch_get_width(void){
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

unsigned int roll_get_width(void){
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

unsigned int yaw_get_width(void){
    return int2_width;
}

/*
 * Input channel 4 (cmr1)
 */
void cmr1_isr(void){
    if (CM1CON0bits.C1OUT) { //Comparator C1 Output bit
        //case high output (rising edge)
        cmr1_start_time = timer0_millis();
    }
    else {
        //case low output (falling edge)
        cmr1_width = timer0_millis()-cmr1_start_time;
    }
}

unsigned int throttle_get_width(void){
    return cmr1_width;
}