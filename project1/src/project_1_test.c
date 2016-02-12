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
#include "project_1_test.h"

#define ARRAY_SIZE 32
#define APTR_2_ADDRESS 8
#define APTR_3_ADDRESS 16
#define APTR_4_ADDRESS 24


#define MEMTEST_SIZE_NOOVERLAP 8
#define MEMTEST_SIZE_OVERLAP 16

#define PRINT_LINE_SIZE 8

void printResults(uint8_t * testArrayPrint) {
	uint8_t index;
	for (index = 0; index < ARRAY_SIZE; index++) {
        printf("%u \t", testArrayPrint[index]);
        // Insert line breaks
        if ( (index+1)%PRINT_LINE_SIZE == 0)
            printf("\n");
    }
    
    printf("\n\n");
}

void initializeData(uint8_t * testArrayInitialize) {
	uint8_t index;
	for (index = 0; index < ARRAY_SIZE; index++) {
       testArrayInitialize[index] = index+1;
    }
}

void project_1_test() {

//    Test array
    uint8_t testArray[ARRAY_SIZE];

//	Array pointers for testing
    uint8_t * aptr_1 = testArray;
    uint8_t * aptr_2 = testArray + APTR_2_ADDRESS;
    uint8_t * aptr_3 = testArray + APTR_3_ADDRESS;
    uint8_t * aptr_4 = testArray + APTR_4_ADDRESS;
    
//  Initialize all memory
    initializeData(testArray);
    
    printf("Initial Array Data: Prepare for memcpy tests\n");
    printResults(testArray);
    
/*  Test memcpy: 
 * Case 1: src < dst, no overlap
 * Case 2: src < dst, overlap
 * Case 3: src > dst, no overlap
 * case 4: src > dst, overlap
 */
 
 // Case 1: src < dst, no overlap
    memcpy(aptr_1, aptr_3, MEMTEST_SIZE_NOOVERLAP);
    
    printf("Case 1: src < dst, no overlap: memcpy test, %d bytes from %d to %d\n", MEMTEST_SIZE_NOOVERLAP, 0, APTR_3_ADDRESS);
    printResults(testArray);

// Case 2: src < dst, overlap
	memcpy(aptr_1, aptr_2, MEMTEST_SIZE_OVERLAP);
	printf("Case 2: src < dst, overlap: memcpy test, %d bytes from %d to %d\n", MEMTEST_SIZE_OVERLAP, 0, APTR_2_ADDRESS);
    printResults(testArray);
    
// Case 3: src > dst, no overlap
	memcpy(aptr_4, aptr_2, MEMTEST_SIZE_NOOVERLAP);
	printf("Case 3: src > dst, no overlap: memcpy test, %d bytes from %d to %d\n", MEMTEST_SIZE_NOOVERLAP, APTR_4_ADDRESS, APTR_2_ADDRESS);
    printResults(testArray);
    
// Case 4: src > dst, overlap
	memcpy(aptr_3, aptr_2, MEMTEST_SIZE_OVERLAP);
	printf("Case 4: src > dst, overlap: memcpy test, %d bytes from %d to %d\n", MEMTEST_SIZE_OVERLAP, APTR_3_ADDRESS, APTR_2_ADDRESS);
    printResults(testArray);
    
//  Initialize all memory
    initializeData(testArray);
    
    printf("Re-initial Array Data: Prepare for memmove tests\n");
    printResults(testArray);
        
/*  Test memmove: 
 * Case 1: src < dst, no overlap
 * Case 2: src < dst, overlap
 * Case 3: src > dst, no overlap
 * Case 4: src > dst, overlap
 */
 
 // Case 1: src < dst, no overlap
    memmove(aptr_1, aptr_3, MEMTEST_SIZE_NOOVERLAP);
    
    printf("Case 1: src < dst, no overlap: memmove test, %d bytes from %d to %d\n", MEMTEST_SIZE_NOOVERLAP, 0, APTR_3_ADDRESS);
    printResults(testArray);

// Case 2: src < dst, overlap
	memmove(aptr_1, aptr_2, MEMTEST_SIZE_OVERLAP);
	printf("Case 2: src < dst, overlap: memmove test, %d bytes from %d to %d\n", MEMTEST_SIZE_OVERLAP, 0, APTR_2_ADDRESS);
    printResults(testArray);
    
// Case 3: src > dst, no overlap
	memmove(aptr_4, aptr_2, MEMTEST_SIZE_NOOVERLAP);
	printf("Case 3: src > dst, no overlap: memmove test, %d bytes from %d to %d\n", MEMTEST_SIZE_NOOVERLAP, APTR_4_ADDRESS, APTR_2_ADDRESS);
    printResults(testArray);
    
// Case 4: src > dst, overlap
	memmove(aptr_3, aptr_2, MEMTEST_SIZE_OVERLAP);
	printf("Case 4: src > dst, overlap: memmove test, %d bytes from %d to %d\n", MEMTEST_SIZE_OVERLAP, APTR_3_ADDRESS, APTR_2_ADDRESS);
    printResults(testArray);
    
    //	Test memzero
    memzero(aptr_3, ARRAY_SIZE-APTR_3_ADDRESS );
    
    printf("Memzero test from %d to %d\n", APTR_3_ADDRESS, ARRAY_SIZE);
    printResults(testArray);
    
//    - Use reverse on aptr_1 to reverse the entire 32 bytes.
    reverse(aptr_1, ARRAY_SIZE);

//    - Use printf to print out the entire 32 byte array in a nicely formatted way.
    printf("Reverse test of entire string\n");
    printResults(testArray);    
    
    printf("Testing complete.\n");
}
