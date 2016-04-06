/*
 * main.c
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 *
 *      Holds all unit tests for implemented code
 */

#include "unitTest.h"
#include "convert.c"
#include "log.c"
#include "uart.h"

int main() {

	// Logger compile-time switch
#ifndef DONT_DEFINE_VERBOSE
#define VERBOSE
#endif

	// Unit Test compile-time switch
#ifndef DONT_DEFINE_UNIT_TEST
#define UNIT_TEST
#endif

	// Attempt to run the UART Printing test
	UARTtestPrinting();

	// Perform Unit test on circular buffer
#ifdef UNIT_TEST
	runAllTests();
#endif

	return 0;
}


