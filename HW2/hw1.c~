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

char reverse_string(char * str, int length){
    // Check input
    if (str == NULL || !(length>0)){
        return 'a'; // Invalid input
    }
    
    int i;
    // Double-check input
    for (i = 0; i<length-1;i++) {
        if (str[i] == '\0')
            break;
    }
    
    if (i != (length-1))
        return 'b'; // incorrectly specified length
            
    char reverse[length+1]; // Reversed string
    
    int j;
    for (i = length-1, j = 0; i >= 0; i--, j++) {    // Manually cut off string terminator
        reverse[j] = str[i];
    }

    reverse[length] = '\0';  // Manually add the string terminator
    
    // put reversed string back in place
    for (i = 0; i <= length; i++) {
    	str[i] = reverse[i];
    }

    return 0;
}

