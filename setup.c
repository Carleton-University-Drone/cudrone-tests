#include <xc.h>
void setup_clock(void){
    OSCCONbits.IRCF = 0b111; // Internal Oscillator Frequency Select bits : 16 MHz
}
