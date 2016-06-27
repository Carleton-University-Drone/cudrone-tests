#include <xc.h>
void setup(){
    setup_clock();
    enable_interrupts();
    enable_timer0();
    setup_pulse_in();
    
    #ifdef DEBUG
    run_tests();
    #endif
}

void setup_clock(void){
    OSCCONbits.IRCF = 0b111; // Internal Oscillator Frequency Select bits : 16 MHz
}
