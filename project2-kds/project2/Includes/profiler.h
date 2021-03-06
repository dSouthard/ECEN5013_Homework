/*
 * profiler.h
 *
 *  Created on: Mar 12, 2016
 *      Author: diana
 */

#ifndef INCLUDES_PROFILER_H_
#define INCLUDES_PROFILER_H_

#define MEMMOVE	0
#define MEMZERO	1
#define REVERSE 2
#define MEMSET	1
#define STRCPY	2
#define STRNCPY	3

#define TEST_RESULT_10	0
#define TEST_RESULT_100	1
#define TEST_RESULT_1000	2
#define TEST_RESULT_5000	3
#define TEST_LENGTH_10	10
#define TEST_LENGTH_100	100
#define TEST_LENGTH_100	1000
#define TEST_LENGTH_5000	5000
#define MAX_TEST_LENGTH 5000
#define MAX_COLUMNS 3

#ifdef PART2_BUILTIN
#define MAX_COLUMNS 4
#endif

#ifdef PART2_MYFUNCTIONS
#define MAX_COLUMNS 3
#endif

#ifdef PART3
#define MAX_COLUMNS 2
#endif

#define MAX_ROWS 4
uint8_t* src;
uint8_t* dst;
uint8_t results[MAX_COLUMNS][MAX_ROWS];

// Data for testing printf statements
#define PRINT_STRING 		"This is my test string"
#define PRINT_VAR1		9191
#define PRINT_VAR2		-5.51
#define PRINT_VAR3		1.010101985
#define PRINT_TEST_CASES 13

uint32_t printResults[PRINT_TEST_CASES];
void printTestResults();
void testMemmove();
void testMemzero();
void testReverse();
void testMemset();
void testStrcpy();
void testStrncpy();
uint32_t _testMemmove(uint32_t byteLength);
uint32_t _testMemzero(uint32_t byteLength);
uint32_t _testReverse(uint32_t byteLength) ;
uint32_t _testMemset(uint32_t byteLength);
uint32_t _testStrcpy(uint32_t byteLength);
uint32_t _testStrncpy(uint32_t byteLength);
void testPrint();
uint32_t printNoPrecisionD(uint32_t var1, uint32_t var2, uint32_t var3);
uint32_t printNoPrecisionF(float var1, float var2, float var3);
uint32_t print2fPrecision(float var1, float var2, float var3);
uint32_t print8fPrecision(float var1, float var2, float var3);



#endif /* INCLUDES_PROFILER_H_ */
