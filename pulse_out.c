#include <xc.h>
#include "pulse_out.h"

void setup_pulse_out(void){
    channel=0;//it starts on the all low cycle
    //Setup Ports
    //M1-RC5
    TRISCbits.RC5 = 0; //pin configured as an output
    PORTCbits.RC5 = 0; //pin set low for initalization
    M1_width=0; //pulse width starts at zero
    
    //M2-RC4
    TRISCbits.RC4 = 0; //pin configured as an output
    PORTCbits.RC4 = 0; //pin set low for initalization
    M2_width=0; //pulse width starts at zero
    
    //M3-RC3
    TRISCbits.RC3 = 0; //pin configured as an output
    PORTCbits.RC3 = 0; //pin set low for initalization
    M3_width=0; //pulse width starts at zero
    ANSELbits.ANS7 = 0; //Digital input buffer of RC3 is enabled
    
    //M4-RC2
    TRISCbits.RC2 = 0; //pin configured as an output
    PORTCbits.RC2 = 0; //pin set low for initalization
    M4_width=0; //pulse width starts at zero
    ANSELbits.ANS6 = 0; //Digital input buffer of RC2 is enabled
    
    //set timer1
    T1CONbits.RD16 = 1; //Enables register read/write of TImer1 in one 16-bit operation
    T1CONbits.T1RUN = 0; //Main system clock is derived from another source
    T1CONbits.T1CKPS = 0b11; //1:8 Prescale value
    T1CONbits.T1OSCEN = 0; //Timer1 oscillator is shut off
    T1CONbits.T1SYNC = 0; //This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
    T1CONbits.TMR1CS = 0; //Internal clock (FOSC/4)
    T1CONbits.TMR1ON = 1; //Enables Timer1
    
    //Setup interrupts
    PIR1bits.TMR1IF = 0; //Clear overflow flag
    IPR1bits.TMR1IP = 1; //High priority
    PIE1bits.TMR1IE = 1; //Enable interrupts
    
    //Pre-load register. It starts on the all off cycle
    load_timer1(DUTY_CYCLE-M1_width-M2_width-M3_width-M4_width);
}

void timer1_isr(void){
    int toLoad;
    switch (channel){
        case 0: //none
            toLoad = DUTY_CYCLE-M1_width-M2_width-M3_width-M4_width;
            LATCbits.LATC2 = 0; //turn off the pin used on the last cycle
            break;
        case 1: //RC5
            toLoad = M1_width;
            LATCbits.LATC5 = 1; //turn on the pin used on the this cycle
            break;
        case 2: //RC4
            toLoad = M2_width;
            LATCbits.LATC4 = 1; //turn on the pin used on the this cycle
            LATCbits.LATC5 = 0; //turn off the pin used on the last cycle
            break;
        case 3: //RC3
            toLoad = M3_width;
            LATCbits.LATC3 = 1; //turn on the pin used on the this cycle
            LATCbits.LATC4 = 0; //turn off the pin used on the last cycle
            break;
        case 4: //RC2
            toLoad = M4_width;
            LATCbits.LATC2 = 1; //turn on the pin used on the this cycle
            LATCbits.LATC3 = 0; //turn off the pin used on the last cycle
            break;
    }
    load_timer1(toLoad); //Load whatever the width of this channel is
    channel=(channel++)%5; //The channel increments by one each time before rolling back to zero
}