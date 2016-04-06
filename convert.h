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
