/* ******************************************
 * File:   queue.cpp
 * Author: Jude Donahue
 * The implementation for the Queue class.
 * This class provides a doubly-linked list 
 * based queue structure supporting FIFO or 
 * LIFO behavior depending on configuration.
 * ******************************************/
#include "queue.h"

Queue::Queue(bool fifo) {
    /* ****************************************
    constructor

    @param fifo : true for FIFO behavior, false for LIFO behavior
    @return na : na
    @exception na : na
    @note initializes an empty queue by setting head and tail to NULL
    *********************************************/
    isFifo = fifo;
    head = NULL;
    tail = NULL;
}

Queue::~Queue() {
    /* ****************************************
    destructor

    @param na : na
    @return na : na
    @exception na : na
    @note releases all dynamically allocated memory by calling clear()
    *********************************************/
    clear();
}

int Queue::peek() {
    /* ****************************************
    retrieves the id at the next removal position
    without modifying the queue

    @param na : na
    @return (int) : id of next element, or -1 if empty
    @exception na : na
    @note FIFO returns tail->id, LIFO returns head->id
    *********************************************/
    int outVal = 0;

    if (head == NULL) {
        outVal = -1;
    } else {
        if (isFifo) {
            outVal = tail->data.id;
        } else {
            outVal = head->data.id;
        }
    }

    return outVal;
}

int Queue::count() {
    /* ****************************************
    dynamically counts the nodes currently stored
    in the queue

    @param na : na
    @return (int) : total number of nodes
    @exception na : na
    *********************************************/
    int count = 0;
    Node* current = head;

    while(current) {
        current = current->next;
        count++;
    }

    return count;
}

bool Queue::exists(int id) {
    /* ****************************************
    checks if a node with a given id exists 
    anywhere in the queue

    @param id : id to search for
    @return (bool) : true if found, otherwise false
    @exception na : na
    *********************************************/
    bool exists = false;
    Node* current = head;

    while (current) {
        if (current->data.id == id) {
            exists = true;
        }
        current = current->next;
    }

    return exists;
}

int Queue::find(int id) {
    /* ****************************************
    finds the position of a node with a given id

    @param id : id to locate within the queue
    @return (int) : position index, or -1 if not found
    @exception na : na
    @note for LIFO, returned index is reversed relative 
          to internal list representation
    *********************************************/
    Node* current = head;
    int position = -1;
    int index = 0;

    while (current != NULL) {
        if (current->data.id == id) {
            if (position == -1) {
                position = index;
            }
        }
        current = current->next;
        index++;
    }

    if (position != -1 && !isFifo) {
        position = (count() - 1) - position;
    }

    return position;
}

bool Queue::push(int id, string &info) {
    /* ****************************************
    inserts a new node into the queue

    @param id : positive integer id of the new node
    @param info : non-empty string stored with the node
    @return (bool) : true if successfully added
    @exception na : na
    @note duplicates are not allowed; new nodes are always
          inserted at the head for both FIFO and LIFO modes
    *********************************************/
    bool pushed = false;

    if (id > 0 && !exists(id) && info != "") {
        Node* node = new Node;
        node->data.id = id;
        node->data.information = info;
        node->next = NULL;
        node->prev = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        pushed = true;
    }

    return pushed;
}

bool Queue::pull(Data &handler) {
    /* ****************************************
    removes the next node from the queue and copies
    its data into the handler

    @param handler : reference to Data struct receiving removed node data
    @return (bool) : true if a node was removed, false if queue empty
    @exception na : na
    @note FIFO removes from tail, LIFO removes from head
    *********************************************/
    Node* target = nullptr;

    if (head == NULL) {
        handler.id = -1;
        handler.information = "";
    } else {
        if (isFifo) {
            target = tail;
        } else {
            target = head;
        }

        handler.id = target->data.id;
        handler.information = target->data.information;

        if (target->prev != NULL)
            target->prev->next = target->next;
        else
            head = target->next;

        if (target->next != NULL)
            target->next->prev = target->prev;
        else
            tail = target->prev;

        delete target;
    }

    return (handler.id != -1);
}

void Queue::clear() {
    /* ****************************************
    deletes all nodes from the queue and frees memory

    @param na : na
    @return na : na
    @exception na : na
    @note sets head and tail back to NULL
    *********************************************/
    Node* current = head;

    while (current) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = NULL;
    tail = NULL;
}

void Queue::printQueue() {
    /* ****************************************
    prints the contents of the queue in head-to-tail order

    @param na : na
    @return na : na
    @exception na : na
    @note prints ID and information for each node
    *********************************************/
    Node* current = head;

    while(current) {
        std::cout << current->data.id << " : " << current->data.information << std::endl;
        current = current->next;
    }
}