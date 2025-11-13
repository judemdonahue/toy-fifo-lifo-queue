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
    clear();
}

bool Queue::push(int id, string &info) {
    bool pushed = false;

    if (id > 0 && info != "") {
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