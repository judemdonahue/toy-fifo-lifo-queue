/* ******************************************
 * File:   queue.h
 * Author: Jude Donahue
 * 
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
    Queue();
    ~Queue();

    /**********************
     * Getters/Accessors
     **********************/
    bool peek();
    int count();
    bool exists();
    bool find();


    /**********************
    * Setters/Mutators
    **********************/
    bool push();
    bool pull();

    /**********************
    * Printing
    **********************/

private:

    /**********************
    * Methods
    **********************/

    // none

    /**********************
    * Attributes
    **********************/
};

#endif /* QUEUE_H */