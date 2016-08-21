/* 
 * File:   queue.h
 * Author: David
 *
 * Created on August 13, 2016, 8:19 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif
#define BUFFER_SIZE 5
typedef struct{
    unsigned char data[BUFFER_SIZE];
    unsigned char top;
    unsigned char bottom;
} queue;
void            inialize_queue(queue * data);
void            enqueue(queue * data, unsigned char in);
unsigned char   dequeue(queue * data);
int             isFull(queue * data);
int             isEmpty(queue * data);

#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */

