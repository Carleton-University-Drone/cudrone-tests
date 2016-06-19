#include "tests.h"
#include <stdio.h>
#include <xc.h>

//Colors
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void putch(unsigned char data) {
    while( ! PIR1bits.TXIF)          // wait until the transmitter is ready
        continue;
    TXREG = data;                     // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1;               // enable transmitter
    RCSTAbits.SPEN = 1;               // enable serial port
}

void dead_loop(void) __attribute__((address(0x1FF0))){
    while(1);
}

void run_tests(void){
    
    char * names[Number_of_Tests] = Test_Messages;
    int (*tests[Number_of_Tests])(void) = Testing_Functions;
    
    init_uart();
    
    int failedTests = 0;
    for (int i = 0; i<Number_of_Tests; i++){
        failedTests += !test(names[i],tests[i]);
    }
    
    if(failedTests == 0){
        printf (KGRN"All %d tests passed\n"KNRM,Number_of_Tests);
    }
    else {
        printf (KRED"%d of %d tests failed\n"KNRM, failedTests, Number_of_Tests);
    }
    dead_loop();
}

int test(const char * name, int (*t)(void)){
    if (!t()){
        printf(KRED"Test %s failed \n"KNRM,name);
        return 0;
    }
    return 1;
}

int basicTest(void){
    return 5>2;
}