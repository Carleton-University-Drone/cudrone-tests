/* 
 * File:   tests.h
 * Author: David
 *
 * Created on June 18, 2016, 2:36 PM
 */

#ifndef TESTS_H
#define	TESTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define Number_of_Tests 3
#define Test_Messages {"Basic Test", "Super Test", "Amazing Test"}
#define Testing_Functions {basicTest, basicTest, basicTest}

    //Helper functions
    void putch(unsigned char data);
    void init_uart(void);
    void dead_loop(void) __attribute__((address(0x1FF0))); //break this
    void run_tests(void);

    int test(const char * name, int (*t)(void) );

    //test
    int basicTest(void);
#ifdef	__cplusplus
}
#endif

#endif	/* TESTS_H */

