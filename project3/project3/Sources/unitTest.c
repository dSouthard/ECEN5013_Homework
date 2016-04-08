/*
 * unitTest.c
 *
 *  Created on: Apr 5, 2016
 *      Author: Diana Southard
 */


#include "unitTest.h"
#include "buffer.h"
#include "log.h"
#include <string.h>

// Use characters == 1-byte each
static char testItems [BUFFER_CAPACITY] = {'E', 'C', 'E', 'N', '5', '0', '1', '3'};

uint8_t runFillTest(CircBuff *testBuff) {
	// Ensure buffer is reset
	CircBuffReset(testBuff);

	uint8_t result;
	// Fill  buffer
	int index;
	for (index = 0; index < BUFFER_CAPACITY; index++) {
		result = CircBuffInsert(testBuff, &testItems[index]);
		// Test failure, couldn't fill buffer
		if (result)
			return -1;
	}

	// Show that buffer is full
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	// Test success!
	return 0;
}

uint8_t runEmptyTest(CircBuff *testBuff) {
	// Ensure buffer is reset
	CircBuffReset(testBuff);

	uint8_t result;
	// Fill  buffer
	int index;
	for (index = 0; index < BUFFER_CAPACITY; index++) {
		CircBuffInsert(testBuff, &testItems[index]);
	}

	// Empty buffer
	char testItemsRemove;
	for (index = 0; index < BUFFER_CAPACITY; index++){
		result = CircBuffRemove(testBuff, &testItemsRemove);
		// Test failure, couldn't empty buffer
		if (result)
			return -1;
	}

	// Show that buffer is empty
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	// Test success!
	return 0;
}

uint8_t runOverFillTest(CircBuff *testBuff) {
	// Ensure buffer is reset
	CircBuffReset(testBuff);

	uint8_t result;
	// Fill  buffer
	int index;
	for (index = 0; index < BUFFER_CAPACITY; index++) {
		CircBuffInsert(testBuff, &testItems[index]);
	}

	// Show that buffer is full
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	// Attempt to fill one more
	result = CircBuffInsert(testBuff, &testItems[index]);

	if (result == 0)
		// Should have error flag set, attempted to over-fill buffer
		return 1;

	// Test success!
	return 0;
}

uint8_t runOverEmptyTest(CircBuff *testBuff) {
	// Ensure buffer is reset
	CircBuffReset(testBuff);

	uint8_t result;

	// Fill  buffer
	int index;
	for (index = 0; index < BUFFER_CAPACITY; index++) {
		CircBuffInsert(testBuff, &testItems[index]);
	}

	// Show that buffer is full
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	char testItemsRemove;

	// Empty buffer
	for (index = 0; index < BUFFER_CAPACITY; index++){
		CircBuffRemove(testBuff, &testItemsRemove);
	}

	// Show that buffer is empty
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	// Attempt to empty one more
	result = CircBuffRemove(testBuff, &testItemsRemove);

	if (result == 0)
		// Should have error flag set, attempted to over-fill buffer
		return 1;

	// Test success!
	return 0;
}

uint8_t runBoundaryTest(CircBuff *testBuff) {
	// Ensure buffer is reset
	CircBuffReset(testBuff);

	uint8_t result;

	// Fill  buffer
	int index;
	for (index = 0; index < BUFFER_CAPACITY; index++) {
		CircBuffInsert(testBuff, &testItems[index]);
	}

	// Show that buffer is full
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	char testItemsRemove;
	// Partly empty the buffer
	for (index = 0; index < BUFFER_CAPACITY*0.5; index++) {
		CircBuffRemove(testBuff, &testItemsRemove);
	}

	// Show that buffer is partly-full
	UARTlogParam(BUFFER_SIZE_STRING, strlen(BUFFER_SIZE_STRING), &testBuff->itemCount, UINT32);

	// Continue to fill the buffer
	result = CircBuffInsert(testBuff, &testItems[index]);

	// Check that item was able to be inserted
	if (result != 0)
		return 1;

	// Check that head pointer has wrapped around
	if (testBuff->head > testBuff->tail)
		return 1;

	// Test success!
	return 0;
}

// Function to run all the tests
void runAllTests() {

	// Create buffer
	CircBuff *testBuff;
	InitCircBuff(testBuff, ITEM_SIZE, BUFFER_CAPACITY);

	uint8_t results[NUMBER_OF_TESTS];
	uint8_t index = 0;
	char* message;

	// Test 1: Completely fill buffer
	results[index] = runFillTest(testBuff);
	if (results[index]) // Return a failure sign
		message = "CB UNIT TEST: 1/5 - runFillTest() .... FAIL";
	else
		message = "CB UNIT TEST: 1/5 - runFillTest() .... PASS!";

	UARTlog(message, strlen(message));
	index++;

	// Test 2: Completely fill and empty buffer
	results[index] = runEmptyTest(testBuff);
	if (results[index]) // Return a failure sign
		message = "CB UNIT TEST: 2/5 - runEmptyTest() .... FAIL";
	else
		message = "CB UNIT TEST: 2/5 - runEmptyTest() .... PASS!";

	UARTlog(message, strlen(message));
	index++;

	// Test 3: Attempt to over-fill the buffer
	results[index] = runEmptyTest(testBuff);
	if (results[index]) // Return a failure sign
		message = "CB UNIT TEST: 3/5 - runFillTest() .... FAIL";
	else
		message = "CB UNIT TEST: 3/5 - runFillTest() .... PASS!";

	UARTlog(message, strlen(message));
	index++;

	// Test 4: Attempt to over-empty the buffer
	results[index] = runOverEmptyTest(testBuff);
	if (results[index]) // Return a failure sign
		message = "CB UNIT TEST: 1/3 - runFillTest() .... FAIL";
	else
		message = "CB UNIT TEST: 1/3 - runFillTest() .... PASS!";

	UARTlog(message, strlen(message));
	index++;

	// Test 5: Boundary Test: Fill over the boundary
	results[index] = runBoundaryTest(testBuff);
	if (results[index]) // Return a failure sign
		message = "CB UNIT TEST: 3/5 - runFillTest() .... FAIL";
	else
		message = "CB UNIT TEST: 3/5 - runFillTest() .... PASS!";

	UARTlog(message, strlen(message));
	index++;

	/* Setup in case more tests need to be added, add below:
	 * ...
	 * ...
	 */

	// Print out final tally
	uint8_t tally = 0;
	for (; index >= 0; index--)
		tally += results[index]; // Add up results from test

	message = "CIRCBUFF UNIT TEST SUITE: Total Tests: " + NUMBER_OF_TESTS;
	UARTlog(message, strlen(message));
	// If there were a failure
	if (tally > 0) {
		message = "FAIL! Number of failed tests";
		UARTlogParam(message, strlen(message), &tally, UINT8);
	}
	else {
		message = "PASS! Passed all tests:";
		UARTlog(message, strlen(message));
	}
}

