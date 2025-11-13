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

int Queue::peek() {
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
    int count = 0;
    Node* current = head;

    while(current) {
        current = current->next;
        count++;
    }

    return count;
}

bool Queue::exists(int id) {
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
            head = target->next;  // target was head

        if (target->next != NULL)
            target->next->prev = target->prev;
        else
            tail = target->prev;  // target was tail

        delete target;
    }

    return (handler.id != -1);
}

void Queue::clear() {
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
    Node* current = head;

    while(current) {
        std::cout << current->data.id << " : " << current->data.information << std::endl;
        current = current->next;
    }
}