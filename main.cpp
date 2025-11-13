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
    ids[testdatasize-2] = ids[testdatasize-3];
    strs[testdatasize-2] = "known duplicate";
    ids[testdatasize-1] = - 1;
    strs[testdatasize-1] = "known bad";
    
    std::cout << "Showing Test Data (" << testdatasize << " entries)..." << std::endl;
    for (int i = 0; i < testdatasize; i++) {
        std::cout << ids[i] << " : " << strs[i] << std::endl;
    }
    std::cout << std::endl;

    
    
    return 0;
}