/* ******************************************
 * File:   queue.h
 * Author: Jude Donahue
 * Header file for the Queue class.
 * Defines the Node structure and public 
 * interface for the FIFO/LIFO queue ADT.
 * ******************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using std::string;
#include <iostream>

struct Data {
    int id;
    string information;
};

struct Node {
    Data data;
    Node* prev;
    Node* next;
};

class Queue {

public:
     /**********************
     * Constructors/Destructor
     **********************/
    Queue(bool);
    ~Queue();

    /**********************
     * Getters/Accessors
     **********************/
    int peek();
    int count();
    bool exists(int);
    int find(int);

    /**********************
    * Setters/Mutators
    **********************/
    bool push(int, string&);
    bool pull(Data&);
    void clear();

    /**********************
    * Printing
    **********************/
    void printQueue();

private:

    /**********************
    * Methods
    **********************/

    // none

    /**********************
    * Attributes
    **********************/
    bool isFifo;
    Node* head;
    Node* tail;
};

#endif /* QUEUE_H */