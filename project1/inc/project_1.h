/*
* ***** project_1.h *****
* Diana Southard
* ECEN 5013 Spring 2016
* Project 1
*
* Contains functions that relate to the higher level tasks within this project.
*
*/ 

#ifndef _PROJECT_1_H
#define _PROJECT_1_H

/*
* Performs the following operations:
* - Create 1 array of 32 bytes (unsigned).
* - Create three pointers to two various points in this array:
*    1. aptr_1: Initialize this pointer address to be the beginning of the array
*    2. aptr_2: Initialize this second pointer to be the address of the 9th 
* element in the array (e.g. array[8]).
*    3. aptr_3: Initialize this third pointer tobe the address of the 17th 
* element in the array (e.g. array[16]).
* - Initialize memory at two of the pointers:
*    1. aptr_1: Initialize 16 bytes starting at this aptr_1 to the numbers from 
* 1-16. Do not modify the pointer address. 
*    2. aptr_3: Initialize the contents from this pointer to the end of the 
* array to zeros using memzero. Do not modify the pointer address
* - Use memcpy to move 8 bytes from aptr_1 to aptr_3
* - Use memmove to move 16 bytes from aptr_2to aptr_1.
* - Use reverse on aptr_1 to reverse the entire 32 bytes.
* - Use printf to print out the entire 32 byte array in a nicely formatted way.
*/
void project_1_report();

#endif
