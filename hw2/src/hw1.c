/* 
 * File:   hw1.h
 * Author: Diana Southard
 * ECEN 5013 Spring 2013
 *
 * Source File for HW1 Assignment: 
 * Given a c-string, 
 * program a routine/function that takes a pointer to 
 * the string and the length of the string and reverses
 * the string provided.
 *
 * Created on January 18, 2016, 8:57 PM
 */
#include<stddef.h>
#include "hw1.h"
#include <stdio.h>

char reverse_string(char * src, int length){
    // Check input
    if (src == NULL || !(length>0)){
        return 'a'; // Invalid input
    }
    
	char temp;
	length--;
	int index;
    for (index = 0; index < length; index++, length--){
        temp = src[index];           // Grab character at start
        src[index]= src[length];    // Swap with character at end
        src[length]= temp;           // Change character at end
    }
    
    printf("String: %s\n", src);
    return 0;
}

