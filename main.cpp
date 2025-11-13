/* ******************************************
 * File:   main.cpp
 * Author: Jude Donahue
 * Purpose: The implementation for main() which is
 * a simple test script.
 * ******************************************/
#include "main.h"

void rand_string(std::string *str){
    /* ****************************************
    * Generate a random uppercase string.
    *
    * @param str : pointer to std::string where the random string is stored
    * @return na : function modifies the referenced string
    * @exception na : na
    * @note length is in range [1, MAXSTRSIZE-1]
    * @note characters are limited to 'A'–'Z'
    *****************************************/
    // create size 0 to MAXSTRSIZE-1
    int rnum = (rand() % (MAXSTRSIZE - 1)) + 1;
    
    // make buffer to hold rand string
    char *buffer = new char[rnum+1];

    // fill buffer with random characters A to Z
    for (int i = 0; i < rnum; i++){
        buffer[i] = (rand() % ('Z' - 'A' + 1)) + 'A';
    }
    buffer[rnum] = '\0';

    // transfer buffer to passed in string
    *str = buffer;

    // clean up
    delete[] buffer;
}

int main () {
    //seed the rand function
    srand(time(NULL));

    const int testdatasize = BASE + (rand() % OFFSET + 1);
    int ids[testdatasize];
    string strs[testdatasize];
    
    char buffer[BUFFERSIZE];
    for (int i = 0; i < testdatasize; i++) {
        ids[i] = rand() % MAXID + 1;
        for (int j = 0; j < BUFFERSIZE - 1; j++) {
            buffer[j] = 'a' + i;
        }
        buffer[BUFFERSIZE - 1] = '\0';
        strs[i] = buffer;
    }
    ids[testdatasize-1] = - 1;
    strs[testdatasize-1] = "known bad";
    
    std::cout << "Showing Test Data (" << testdatasize << " entries)..." << std::endl;
    for (int i = 0; i < testdatasize; i++) {
        std::cout << ids[i] << " : " << strs[i] << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Creating FIFO Queue..." << std::endl;
    bool fifo = true;
    Queue queueFifo(fifo);
    Data test;
    std::cout << "FIFO Queue created." << std::endl;

    /************************************************
    ******** EMPTY FIFO QUEUE TESTING ********************
    ************************************************/
    std::cout << "\n<==EMPTY FIFO QUEUE TESTING==>" << std::endl;
    std::cout << "the queue should be empty..." <<  std::endl;
    queueFifo.printQueue();
    if (queueFifo.count() == 0) {
        std::cout << "PASS. queue had " << queueFifo.count() << " entries upon creation." << std::endl;
    } else {
        std::cout << "FAIL. queue was not empty." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to pull from empty queue (FIFO)..." << std::endl;
    if (!queueFifo.pull(test)) {
        std::cout << "PASS. pull() safely failed and returned -1 (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to peek from empty queue (FIFO)..." << std::endl;
    if (queueFifo.peek() == -1) {
        std::cout << "PASS. peek() safely failed and returned: " << queueFifo.peek() << " (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    int randInt = rand() % MAXID - 1;
    std::cout << "attempting to see if a random ID: " << randInt << " exists in queue (FIFO)..." << std::endl;
    if (!queueFifo.exists(randInt)) {
        std::cout << "PASS. exists() safely failed (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    randInt = rand() % MAXID - 1;
    std::cout << "attempting to see if a random ID: " << (randInt) << " can be found with a returnable position in queue (FIFO)..." << std::endl;
    if (queueFifo.find(randInt) == -1) {
        std::cout << "PASS. find() safely failed and returned: " << queueFifo.find(randInt) << " (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to push test data to empty queue (FIFO)..." << std::endl;
    for (int i = 0; i < testdatasize; i++) {
        queueFifo.push(ids[i], strs[i]);
    }

    if (queueFifo.count() == testdatasize - 1) {
        std::cout << "PASS. all good data was pushed into the queue. (expected)" << std::endl;
    } else {
        std::cout << "FAIL. not everything was pushed. (unexpected)" << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Printing Queue..." << std::endl;
    queueFifo.printQueue();
    std::cout << std::endl;
    
    std::cout << "Clearing Queue..." << std::endl;
    queueFifo.clear();
    std::cout << "there are " << queueFifo.count() << " entries in the queue." << std::endl;
    std::cout << std::endl;

    /************************************************
    ******** SINGLE ENTRY FIFO QUEUE TESTING ********************
    ************************************************/
    std::cout << "\n<==SINGLE ENTRY FIFO QUEUE TESTING==>" << std::endl;

    std::cout << "Pushing 1 entry (" << ids[testdatasize-2] << " : " << strs[testdatasize-2] << ") to the queue." << std::endl;
    queueFifo.push(ids[testdatasize-2], strs[testdatasize-2]);

    std::cout << "the queue should have only 1 entry..." <<  std::endl;
    if (queueFifo.count() == 1) {
        std::cout << "PASS. queue had " << queueFifo.count() << " entry." << std::endl;
    } else {
        std::cout << "FAIL. queue was more or less than 1 entry." << std::endl;
    }
    queueFifo.printQueue();
    std::cout << std::endl;

    std::cout << "attempting to peek from empty queue (FIFO)..." << std::endl;
    if (queueFifo.peek() == -1) {
        std::cout << "FAIL. peek() returned: " << queueFifo.peek() << " (unexpected)." << std::endl;
    } else {
        std::cout << "PASS. peeked: " << queueFifo.peek() << " (expected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to see if " << ids[testdatasize-2] << " exists in queue (FIFO)..." << std::endl;
    if (queueFifo.exists(ids[testdatasize-2])) {
        std::cout << "PASS. " << ids[testdatasize-2] << " exists in the queue (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to find: " << ids[testdatasize-2] << "'s position in the queue (FIFO)..." << std::endl;
    if (queueFifo.find(ids[testdatasize-2]) == 0) {
        std::cout << "PASS. find() found entry position at: " << queueFifo.find(ids[testdatasize-2]) << " (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "attempting to pull from single entry queue (FIFO)..." << std::endl;
    if (queueFifo.pull(test)) {
        std::cout << "PASS. pulled " << test.id << " : " << test.information << " (expected)." << std::endl;
    } else {
        std::cout << "FAIL. something went wrong (unexpected)." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "there are " << queueFifo.count() << " entries in the queue." << std::endl;
    std::cout << std::endl;

    std::cout << "Pushing 1 entry (" << ids[0] << " : " << strs[0] << ") to the queue." << std::endl;
    queueFifo.push(ids[0], strs[0]);
    std::cout << std::endl;

    std::cout << "(SHOULD CONTAIN 1 DUPLICATE) attempting to push the rest of the test data into single entry queue (FIFO)..." << std::endl;
    for (int i = 0; i < testdatasize - 1; i++) {
        queueFifo.push(ids[i], strs[i]);
    }
    std::cout << std::endl;

    queueFifo.printQueue();

    std::cout << "Clearing Queue..." << std::endl;
    queueFifo.clear();
    std::cout << "there are " << queueFifo.count() << " entries in the queue." << std::endl;
    std::cout << std::endl;
    
    


    return 0;
}