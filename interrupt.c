#include <xc.h>
#include "interrupt.h"
#include "timer0.h"
#include "pulse_in.h"
#include "pulse_out.h"
#include "controller.h"
#include "uart.h"
void enable_interrupts(void){
    RCONbits.IPEN=1;        //Enable low and high priority interrupts
    INTCONbits.PEIE=1;      //Enable low priority interrupts
    INTCONbits.GIE=1;       //Global Interrupt enable
}

void interrupt low_priority low_priority_isr(void){
    if (PIR1bits.TMR2IF){
        controller_step(); // timer2 isr, pid controller step
        PIR1bits.TMR2IF=0;
    }
    else if (PIR1bits.RCIF && PIE1bits.RCIE){
        uart_received();
        PIR1bits.RCIF = 0;
    }
    else if (PIR1bits.TXIF && PIE1bits.TXIE){
        uart_transmit_complete();
        PIR1bits.TXIF = 0;
    }
}

void interrupt high_priority high_priority_isr(void){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        timer0_isr();
        INTCONbits.TMR0IF = 0;
    }
    if (PIR1bits.TMR1IF){
        timer1_isr();
        PIR1bits.TMR1IF = 0;
    }
    if (INTCONbits.INT0IF){ //This should be low priority but int0 is only high priority
        int0_isr();
        INTCONbits.INT0IF=0;
    }
    if (INTCONbits.INT0IF){
        int0_isr();
        INTCONbits.INT0IF=0;
    }
    if (INTCON3bits.INT1F){
        int1_isr();
        INTCON3bits.INT1F=0;
    }
    if (INTCON3bits.INT2F){
        int2_isr();
        INTCON3bits.INT2F=0;
    }
    if (PIR2bits.C1IF){
        cmr1_isr();
        PIR2bits.C1IF = 0;
    }
}