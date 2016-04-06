/*
 * unitTest.h
 *
 *  Created on: Apr 5, 2016
 *      Author: Diana Southard
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_


#define ITEM_SIZE	sizeof(char)
#define BUFFER_CAPACITY 8
#define NUMBER_OF_TESTS	5

#define BUFFER_SIZE_STRING "The buffer's size is"
#define TEST_PASS "PASS"
#define TEST_FAIL "FAIL"

// Run unit tests on the circular buffer

// Test 1: Completely fill buffer
uint8_t runFillTest(CircBuff *testBuff);

// Test 2: Completely fill and empty buffer
uint8_t runEmptyTest(CircBuff *testBuff);

// Test 3: Attempt to over-fill the buffer
uint8_t runEmptyTest(CircBuff *testBuff);

// Test 4: Attempt to over-empty the buffer
uint8_t runOverEmptyTest(CircBuff *testBuff);

// Test 5: Boundary Test: Fill over the boundary
uint8_t runBoundaryTest(CircBuff *testBuff);

// Run all tests
void runAllTests();

#endif /* UNITTEST_H_ */
