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
	char * ptr = returnBuffer;
		char * p = ptr;
		char * p1;
		char c;
		long intPart;

		// check precision bounds
		if (precision > MAX_PRECISION)
			precision = MAX_PRECISION;

		// sign stuff
		if (data < 0)
		{
			data = -data;
			*ptr++ = '-';
		}

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

		// round value according the precision
		if (precision)
			data += rounders[precision];

		// integer parst...
		intPart = data;
		data -= intPart;

		if (!intPart)
			*ptr++ = '0';
		else
		{
			// save start pointer
			p = ptr;

			// convert (reverse order)
			while (intPart)
			{
				*p++ = '0' + intPart % 10;
				intPart /= 10;
			}

			// save end position
			p1 = p;

			// reverse result
			while (p > ptr)
			{
				c = *--p;
				*p = *ptr;
				*ptr++ = c;
			}

			// restore end position
			ptr = p1;
		}

		// decimal part
		if (precision)
		{
			// place decimal point
			*ptr++ = '.';

			// convert
			while (precision--)
			{
				data *= 10.0;
				c = data;
				*ptr++ = '0' + c;
				data -= c;
			}
		}

		// terminating zero
		*ptr = 0;

		return returnBuffer;

}


int main () {

	float test1 = 123.45567;
	float test2 = -0.0344;
	float test3 = 123512.3523;

	char test1Print[40];
	ftoa(test1,4,test1Print,40);

	char test2Print[40];
	ftoa(test2,4,test2Print,40);
	char test3Print[40];
	ftoa(test3,4,test3Print,40);

	printf("1: %s \n", test1Print);
	printf("2: %s \n", test2Print);
	printf("3: %s \n", test3Print);

	float test1i = 123;
	float test2i = -344;
	float test3i = 12356875;

	char print1i[20];
	itoa(test1i, print1i, 20);
	printf("1: %s \n", print1i);

	char print2i[10];
	itoa(test2i, print2i, 10);
	printf("2: %s \n", print2i);

	char print3i [20];
	itoa(test3i, print3i, 20);
	printf("3: %s \n", print3i);

	printf("1: %s \n", print1i);
	printf("2: %s \n", print2i);

	return 0;
}
