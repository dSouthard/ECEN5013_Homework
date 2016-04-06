/*
 * log.h
 *
 *  Created on: Apr 4, 2016
 *      Author: 1118648
 */

#ifndef LOG_H_
#define LOG_H_

#define VERBOSE

// Enumeration of possible data types
typedef enum {
	INT8, INT16, INT32, 	// Signed integers
	UINT8, UINT16, UINT32,	// Unsigned integers
	FLOAT					// Floating point
} DataType;

void UARTlog(unit8_t *str, size_t length);
void UARTlogParam(unit8_t *str, size_t length, void* param, size_t dataSize);



#endif /* LOG_H_ */
