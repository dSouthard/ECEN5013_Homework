/*
* ***** project_1.c *****
* Diana Southard
* ECEN 5013 Spring 2016
* Project 1
*
* Contains functions that relate to the higher level tasks within this project.
*
*/ 

#include <stdio.h>
#include "memory.h"
#include "project_1.h"

#define ARRAY_SIZE 32
#define APTR_2_ADDRESS 8
#define APTR_3_ADDRESS 16

#define INITIALIZE_SIZE 16
#define MEMCPY_SIZE 8
#define MEMOVE_SIZE 16

#define PRINT_LINE_SIZE 8

void project_1_report() {

//    Create 1 array of 32 bytes (unsigned)
    uint8_t reportArray[ARRAY_SIZE];
    
/* Create three pointers to two various points in this array:
*    1. aptr_1: Initialize this pointer address to be the beginning of the array
*    2. aptr_2: Initialize this second pointer to be the address of the 9th 
* element in the array (e.g. array[8]).
*    3. aptr_3: Initialize this third pointer to be the address of the 17th 
* element in the array (e.g. array[16]).
*/
    uint8_t * aptr_1 = reportArray;
    uint8_t * aptr_2 = reportArray + APTR_2_ADDRESS;
    uint8_t * aptr_3 = reportArray + APTR_3_ADDRESS;
    
/* - Initialize memory at two of the pointers:
*    1. aptr_1: Initialize 16 bytes starting at this aptr_1 to the numbers from 
* 1-16. Do not modify the pointer address. 
*/
    uint8_t index;
    for (index = 0; index < INITIALIZE_SIZE; index++) {
        *(aptr_1 + index) = index+1; 
    }
    
/*  2. aptr_3: Initialize the contents from this pointer to the end of the 
* array to zeros using memzero. Do not modify the pointer address
*/
    memzero(aptr_3, ARRAY_SIZE-APTR_3_ADDRESS );
    
//    - Use memcpy to move 8 bytes from aptr_1 to aptr_3
    memcpy(aptr_1, aptr_3, MEMCPY_SIZE);

//    - Use memmove to move 16 bytes from aptr_2 to aptr_1.
    memmove(aptr_2, aptr_1, MEMOVE_SIZE);
    
//    - Use reverse on aptr_1 to reverse the entire 32 bytes.
    reverse(aptr_1, ARRAY_SIZE);

//    - Use printf to print out the entire 32 byte array in a nicely formatted way.
    printf("Final Array Data:\n");
    
    for (index = 0; index < ARRAY_SIZE; index++) {
        printf("%u \t", reportArray[index]);
        // Insert line breaks
        if ( (index+1)%PRINT_LINE_SIZE == 0)
            printf("\n");
    }
    
    printf("\n\n");
}
