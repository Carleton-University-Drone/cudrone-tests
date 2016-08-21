/* 
 * File:   queue.cpp
 * Author: David
 * 
 * Created on August 13, 2016, 8:19 PM
 * Interesting note:
 * The first version of this using the modulus function instead of the ternary 
 * conditional operator. The device we are using does not have hardware support
 * for modulus so it has to call an external function (the compiler does this 
 * automatically). Switching saved 10 bytes of ram and 268 bytes of memory. For
 * a system this small thats pretty good.
 * 
 */
#include "queue.h"

void inialize_queue(queue * data) {
    data->top = data->bottom = BUFFER_SIZE-1;
}

void enqueue(queue * data, unsigned char in){
    data->data[(++data->top)==BUFFER_SIZE ? data->top=0 : data->top] = in;
}

unsigned char dequeue(queue * data){
    return data->data[(++data->bottom)==BUFFER_SIZE ? data->bottom=0 : data->bottom];
}

int isFull(queue * data){
    return ((data->top+1)==BUFFER_SIZE ? 0 : data->top+1) == data->bottom;
}

int isEmpty(queue * data){
    return data->top==data->bottom;
}