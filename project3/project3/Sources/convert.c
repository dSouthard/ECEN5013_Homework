/*
 * convert.c
 *
 *  Created on: Mar 25, 2016
 *      Author: Diana Southard
 *
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "convert.h"

#define MAX_PRECISION 		10 	// The highest precision to display purely decimal digits


/* Helper function to return ASCII character of desired digit
 *
 * @param digit 	Desired integer digit to be returned as ASCII char
 *
 */
char getCharacter(int digit) {
	if (digit < 0 || digit > 9)
		return '0';	// default behavior if number is out of range
	char numberString [] = "0123456789";
	return numberString[digit];
}


static const double rounders[MAX_PRECISION + 1] =
{
		0.5,			// 0
		0.05,			// 1
		0.005,			// 2
		0.0005,			// 3
		0.00005,		// 4
		0.000005, 		// 5
		0.0000005,		// 6
		0.00000005, 	// 7
		0.000000005,	// 8
		0.0000000005,	// 9
		0.00000000005	// 10
};

/*
 * itoa(): integer to ASCII
 *
 * Take integer data and convert it to ASCII string. The string then
 * needs to represent integer types of data in 1,2, or 4 byte types
 * for each individual conversion of variables.
 */
char * itoa(int data){
	// Check for 0
	if (data == 0) {
		return "0";
	}

	// size = at least 2: 1 for data, 1 for terminating character
	int size = 2, isNegative = 0;

	// Check if we need to put in a negative sign
	if (data < 0) {
		isNegative = 1;
		data *= -1;
		size++; 	// Reserved a place for the negative sign
	}

	// Find size of return string
	int dataCopy = data;
	while (dataCopy > 10) {
		dataCopy /= 10;
		size++;
	}

	char returnBuffer[size];

	int index = size-1;

	// Add terminating character
	returnBuffer[index] = '\0';
	index--;

	int digit;	// Used to track individual digit conversion

	// Start filling the returnBuffer from the back (LSB)
	while (data != 0 && index >= 0) {
		digit = data%10;
		data -= digit;
		data /= 10;
		returnBuffer[index] = getCharacter(digit);
		index-- ;
	}

	if (isNegative > 0)
		returnBuffer[index] = '-';

	// Return ASCII string
	char* returnPnt = returnBuffer;
	return returnPnt;
}

/*
 * uitoa(): unsigned integer to ASCII
 *
 * Take unsigned integer data and convert it to ASCII string. The string then
 * needs to represent integer types of data in 1,2, or 4 byte types
 * for each individual conversion of variables.
 */
char * uitoa(unsigned int data){
	// Check for 0
	if (data == 0) {
		return "0";
	}

	// size = at least 2: 1 for data, 1 for terminating character
	int size = 2;

	// Find size of return string
	int dataCopy = data;
	while (dataCopy > 10) {
		dataCopy /= 10;
		size++;
	}

	char returnBuffer[size];

	int index = size-1;

	// Add terminating character
	returnBuffer[index] = '\0';
	index--;

	int digit;	// Used to track individual digit conversion

	// Start filling the returnBuffer from the back (LSB)
	while (data != 0 && index >= 0) {
		digit = data%10;
		data -= digit;
		data /= 10;
		returnBuffer[index] = getCharacter(digit);
		index-- ;
	}

	// Return ASCII string
	char* returnPointer = returnBuffer;
	return returnPointer;
}

/*
 * ftoa(): float to ASCII
 *
 * Take floating point numbers and convert them to string version with
 * a decimal point splitting the integral and fractional part of the
 * string. Must take into account the sign bit, may decide on how to
 * control the precision of display.
 *
 * Converts a float to a string.
 *
 * @param strBuff		Pointer to the string containing converted float
 * @param data			The float to be converted
 * @param precision 	The desired precision
 *
 * NOTE: Based on code from https://raw.githubusercontent.com/antongus/stm32tpl/master/ftoa.c
 *
 */

char * ftoa(float data, int precision){
	// Check for special cases
	if (isnan(data))
		return "NAN";
	if (isinf(data))
		return "INF";
	if (data == 0)
		return "0.0";

	long intPart, size = 2; // Size spots: decimal termination
	int isNegative = 0;

	// check precision bounds
	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;

	if (precision < 0)  // negative precision == automatic precision guess
	{
		if (data < 1.0) precision = 6;
		else if (data < 10.0) precision = 5;
		else if (data < 100.0) precision = 4;
		else if (data < 1000.0) precision = 3;
		else if (data < 10000.0) precision = 2;
		else if (data < 100000.0) precision = 1;
		else precision = 0;
	}

	// Check for negative value
	if (data < 0) {
		data = -data;
		isNegative = 1;
		size++; // Reserve a spot for '-' sign
	}

	// Round value according the precision
	if (precision)
		data += rounders[precision];

	// Separate integer and decimal parts
	intPart = data;		// Integer Part
	data -= intPart;	// Leftover = decimal part

	// Determine buffer size.
	long intCopy = intPart;
	int exponent = 0;

	// Check integer digits for required size
	while (intCopy > 10) {
		intCopy /= 10;
		size++;
	}

	// Add desired precision digits to required size
	if (precision)
		size += precision + 1;	// Add 1 to account for decimal point

	if (size > FLOAT_STRING_LENGTH) {
		// Convert using scientific notation
		// re-add data
		data += intPart;
		// Normalize the data
		while (data > 10) {
			data /= 10;
			exponent++;
		}

		/* reset size due to normalizing data:
		 *  +/- 1.pppppppppp * 10^eee /0
		 *  size =
		 */
		int exponentDigits = 1;
		if (exponent > 10) exponentDigits = 2;

		size = isNegative + 2 + precision + 7 + exponentDigits;

		// split decimal portions again
		intPart = data;
		data -= intPart;
	}

	char returnBuffer[size];

	// Pointers to help with arithmetic later
	char * bufferPointer = returnBuffer; // Point to start of buffer

	// Add '-' if necessary
	if (isNegative) {
		*bufferPointer = '-';
		bufferPointer++;
	}

	// Check if integer part == 0
	if (!intPart) {
		*bufferPointer = '0';	// Put 0 in buffer
		bufferPointer++;
	}

	else
	{
		char *tmpPointer;
		// Convert integer part and copy to buffer
		tmpPointer = itoa(intPart);
		strcpy(bufferPointer, tmpPointer);
		bufferPointer += strlen(tmpPointer);
	}


	// decimal part
	if (precision) 	// Desired to show decimal portion
	{
		// place decimal point
		*bufferPointer = '.';
		bufferPointer++;

		// convert
		int digit;
		while (precision > 0 && bufferPointer < &returnBuffer[size-1]){
			if (data == 0.0) {
				*bufferPointer = '0';
			}
			else {
				data *= 10.0;					// Bring next digit out
				digit = data;					// Grab integer part
				*bufferPointer = getCharacter(digit);	// Convert to character
				data -= digit;					// Delete part that was just converted
			}
			bufferPointer++;					// Increment pointer
			precision--;
		}
	}

	if (exponent) {
		// Using scientific notation
		// add space
		*bufferPointer = ' ';
		bufferPointer++;

		// Add exponent string
		char * tmpChar = "* 10^";
		strcpy(bufferPointer, tmpChar);
		bufferPointer += strlen(tmpChar);

		// Add exponents
		tmpChar = itoa(exponent);
		strcpy(bufferPointer, tmpChar);
		bufferPointer += strlen(tmpChar);
	}

	// terminating character
	returnBuffer[size-1] = '\0';

	bufferPointer = returnBuffer;
	return bufferPointer;
}



