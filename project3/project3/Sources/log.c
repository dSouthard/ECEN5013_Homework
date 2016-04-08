/*
 * log.c
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 *
 *      Hold wrapper functions for the UART module to print data to the terminal.
 */
#include "log.h"
#include "uart.h"
#include "convert.h"
#include <stdint.h>
#include <stddef.h>

#ifdef VERBOSE

// Function to log just a simple string
void UARTlog(uint8_t *string, size_t length){
	// Iterate through string, sending characters individually
	size_t index = 0;

	for ( ; string[index] == '\0'; index++) {
		UARTsendChar(string[index]);
	}

	// Add new line for readability
	UARTsendChar('\n');
}


// Function to log just a simple string with a parameter
void UARTlogParam(uint8_t *string, size_t length, void * param, DataType dataType){
	// Iterate through string, sending characters individually
	size_t index = 0;

	for (; string[index] != '\0'; index++) {
		UARTsendChar(string[index]);
	}

	// Add parameter
	UARTsendChar(':');
	UARTsendChar(' ');

	char* secondString;		// Used to accept the converted string

	// Determine which conversion function to use
	switch (dataType) {
	case INT8: {
		int data = *(int8_t *)param;
		secondString = itoa(data);
		break;
	}
	case INT16: {
		int data = *(int16_t *)param;
		secondString = itoa(data);
		break;
	}
	case INT32: {
		int data = *((int32_t *)param);
		secondString = itoa(data);
		break;
	}
	case UINT8: {
		unsigned int udata = *((uint8_t *)param);
		secondString = uitoa(udata);
		break;
	}
	case UINT16:{
		unsigned int udata = *((uint16_t *)param);
		secondString = uitoa(udata);
		break;
	}
	case UINT32:{
		unsigned int udata = *((uint32_t *)param);
		secondString = uitoa(udata);
		break;
	}
	default:{
		secondString = ftoa(*(float *)param, -1);
		break;
	}
	}

	// Send second converted string
	index = 0;

	while( *secondString != '\0') {
		UARTsendChar(secondString);
		secondString++;
	}

	// Add new line for readability
	UARTsendChar('\n');
}

#else

void UARTlog(unit8_t *string, size_t length){
	// Empty
}

void UARTlogParam(unit8_t *string, size_t length, void* param, DataType dataType){
	// Empty
}

#endif
