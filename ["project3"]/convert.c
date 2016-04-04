/*
 * convert.c
 *
 *  Created on: Mar 25, 2016
 *      Author: Diana Southard
 *
 */

#include<stdio.h>
#include<math.h>
#include<string.h>

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
int itoa(int data, char* returnBuffer, int bufferSize){
	// size = at least 2: 1 for data, 1 for terminating character
	int size = 2, isNegative = 0;

	// Check if we need to put in a negative sign
	if (data < 0) {
		isNegative = 1;
		data *= -1;
		size++; 	// Reserved a place for the negative sign
	}

	// Check for 0
	if (data == 0)
		returnBuffer[0] = '0';

	// Find size of return string
	int dataCopy = data;
	while (dataCopy > 10) {
		dataCopy /= 10;
		size++;
	}

	if (size > bufferSize)
		return -1;

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
	return 0;
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

int ftoa(float data, unsigned int precision, char* returnBuffer, int bufferSize){
	char * startPointer = returnBuffer;
	char * tmpPointer;
	char tmpChar;
	long intPart, size = 3;

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
	if (data < 0)
	{
		data = -data;
		*returnBuffer++ = '-';
		size++;
	}

	// Round value according the precision
	if (precision)
		data += rounders[precision];

	// Separate integer and decimal parts
	intPart = data;		// Integer Part
	data -= intPart;	// Leftover = decimal part

	// Check for buffer overflow.
	long intCopy = intPart;

	// Check integer digits for required size
	while (intCopy > 10) {
		intCopy /= 10;
		size++;
	}

	// Add desired precision digits to required size
	size += precision;

	if (size > bufferSize)
		return -1;

	// Check if integer part == 0
	if (!intPart)
		*returnBuffer++ = '0';

	else
	{
		// save start pointer
		startPointer = returnBuffer;

		// convert (reverse order)
		while (intPart)
		{
			*startPointer++ = '0' + intPart % 10;
			intPart /= 10;
		}

		// save end position
		tmpPointer = startPointer;

		// reverse result
		while (startPointer > returnBuffer)
		{
			tmpChar = *--startPointer;
			*startPointer = *returnBuffer;
			*returnBuffer++ = tmpChar;
		}

		// restore end position
		returnBuffer = tmpPointer;
	}

	// decimal part
	if (precision)
	{
		// place decimal point
		*returnBuffer++ = '.';

		// convert
		while (precision--)
		{
			data *= 10.0;
			tmpChar = data;
			*returnBuffer++ = '0' + tmpChar;
			data -= tmpChar;
		}
	}

	// terminating character
	*returnBuffer = '\0';

	return returnBuffer;

}



