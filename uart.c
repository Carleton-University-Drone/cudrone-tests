#include <xc.h>
#include "uart.h"
#include "queue.h"
void setup_uart(void){
    //setup queue's
    inialize_queue(&transmit_queue);
    inialize_queue(&recive_queue);
    //Set tris registers
    TRISBbits.RB7 = 1;
    TRISBbits.RB5 = 1;
    
    //Set the baud rate generator
    //set baud rate
    SPBRGH = 0;
    SPBRG = 103;
    //BAUD RATE CONTROL REGISTER
    BAUDCONbits.DTRXP = 0; //Not inverted
    BAUDCONbits.CKTXP = 0; //Idle state for transmit is high
    BAUDCONbits.BRG16 = 0; //8 bit baud rate generater
    BAUDCONbits.WUE   = 0;
    BAUDCONbits.ABDEN = 0; //Automatic baud rate detection disabled
    
    
    //Setup transmit status and control register
    TXSTAbits.TX9 = 0; //Select 8-bit transmission
    TXSTAbits.TXEN = 1; //Enable transmit
    TXSTAbits.SYNC = 0; //ASYNC mode
    TXSTAbits.SENDB = 0; //Sync Break transmission completed
    TXSTAbits.BRGH = 0; //low speed
    
    //RECEIVE STATUS AND CONTROL REGISTER 
    RCSTAbits.SPEN = 1; //Serial port enabled
    
    RCSTAbits.RX9 = 0; //eight bit reception
    RCSTAbits.CREN = 1; //Enable reciver
    ANSELHbits.ANS11 = 0; //Digital input buffer of RB5 (RX) is enabled)
    
    //Enable uart interruts

    IPR1bits.RCIP = 0; //EUSART receive low priority
    IPR1bits.TXIP = 0; //EUSART transmit low priority

    //Clear flags
    PIR1bits.RCIF = 0; //Receive
    // 1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
    // 0 = The EUSART receive buffer is empty
    PIR1bits.TXIF = 0; //Transmit
    // 1 = The EUSART transmit buffer, TXREG, is empty (cleared when TXREG is written)
    // 0 = The EUSART transmit buffer is 
    
    PIE1bits.RCIE = 1; //Enables the EUSART receive interrupt
    PIE1bits.TXIE = 1; //Enables the EUSART transmit interrupt
}

void uart_transmit_complete(void){
    if (!isEmpty(&transmit_queue)){
        TXREG = dequeue(&transmit_queue);
    }
    else { //if the transmit buffer is empty, turn off module
        TXSTAbits.TXEN = 0; //Turn off transmission
        PIE1bits.TXIE = 0; //turn off transmit interrupts for good measure
    }
    // while (!PIR1bits.TXIF);
}

void uart_received(void){
    //while (!PIR1bits.RCIF);
    enqueue(&recive_queue, RCREG);
}

void uart_send(unsigned char c){
    enqueue(&transmit_queue,c);
    //Enable interrupts and transmission again
    TXSTAbits.TXEN = 1; //Turn on transmission
    PIE1bits.TXIE  = 1; //Turn on interrupts
}

unsigned char uart_read(void){
    return dequeue(&recive_queue);
}

int uart_avalible (){
    return !isEmpty(&recive_queue);
}

#ifdef DEBUG

void putch(unsigned char data) {
    uart_send(data);
}

#endif