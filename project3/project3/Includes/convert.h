/*
 * convert.h
 *
 *  Created on: Mar 25, 2016
 *      Author: Diana Southard
 *      ECEN 5013
 *      Project 3: UART and Logger
 */

#ifndef CONVERT_H_
#define CONVERT_H_

/* Maximum float number: ~3.4 * 10^38
 * --> Anything over 10^10 or under 10^-10 should be represented in scientific notation
 * 10 -- max precision allowed
 * --> Max float string length: INTEGER_STRING_LENGTH+MAX_PRECISION_ALLOWED
 * = 11 + 10 = 23 (+ string terminator, possible negative sign)
 */
#define FLOAT_STRING_LENGTH  23

// Implement the functions itoa() and ftoa()

/*
 * itoa(): integer to ASCII
 *
 * Take integer data and convert it to ASCII string. The string then
 * needs to represent integer types of data in 1,2, or 4 byte types
 * for each individual conversion of variables.
 */

char* itoa(int data);

// uitoa: itoa for unsigned integers
char* uitoa(unsigned data);

/*
 * ftoa(): float to ASCII
 *
 * Take floating point numbers and convert them to string version with
 * a decimal point splitting the integral and fractional part of the
 * string. Must take into account the sign bit, may decide on how to
 * control the precision of display.
 */
char* ftoa(float data, int precision);

// Helper function
char getCharacter(int digit);



#endif /* CONVERT_H_ */
