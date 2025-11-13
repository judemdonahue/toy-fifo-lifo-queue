/* ******************************************
 * File:   queue.cpp
 * Author: Jude Donahue
 * 
 * ******************************************/
#include "queue.h"

Queue::Queue(bool fifo) {
    isFifo = fifo;
    head = NULL;
    tail = NULL;
}

Queue::~Queue() {
    
}