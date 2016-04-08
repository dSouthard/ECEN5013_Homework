/*
 * buffer.c
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "buffer.h"


/*
 * Initialize the circular buffer
 */
uint8_t InitCircBuff(CircBuff * buffer, size_t itemSize, size_t capacity) {
	// Check for non-null pointer
	if (buffer == NULL)
		return -1;

	// Set up buffer
	buffer->itemSize = itemSize;
	buffer->capacity = capacity;
	buffer->size = itemSize*capacity;
	buffer->itemCount = 0;

	// Allocate space for the buffer
	buffer->beginning = malloc(buffer->size);

	// Check that memory was properly allocated
	if (buffer->beginning == NULL)
		return -1;

	// Setup end/head/tail pointers
	buffer->end = (char*)buffer->beginning + buffer->capacity;
	buffer->head = buffer->beginning;
	buffer->tail = buffer->beginning;

	return 0;
}


/*
 * Add item to buffer
 */
uint8_t CircBuffInsert(CircBuff * buffer, void* item) {
	// Check for non-null pointer
	if (buffer == NULL)
		return -1;

	// Check if buffer is full
	if (buffer->itemCount < buffer->capacity) {
		// Buffer is not full, add item
		memcpy(buffer->head, item, buffer->itemSize);
		buffer->itemCount++;

		// Increment head pointer
		buffer->head = (char*)buffer->head + buffer->itemSize;

		// Check if head pointer needs to wrap around
		if (buffer->head >= buffer->end)
			buffer->head = buffer->beginning;
	}

	else {
		// Buffer is full
		return -1;
	}
}

/*
 * Remove item from buffer
 */
uint8_t CircBuffRemove(CircBuff * buffer, void *item){
	// Check for non-null pointer
	if (buffer == NULL)
		return -1;

	// Check if buffer is empty
	if (buffer->itemCount == 0)
		return -1;

	// Copy from tail to item
	memcpy(item, buffer->tail, buffer->itemSize);
	buffer->itemCount--;

	// Increment tail pointer
	buffer->tail = (char*)buffer->tail + buffer->itemSize;

	// Check if tail needs to wrap-around
	if (buffer->tail >= buffer->end)
		buffer->tail = buffer->beginning;

	return 0;
}

/*
 * Reset buffer -- all items are dropped
 */
uint8_t CircBuffReset(CircBuff * buffer){
	// Check for non-null pointer
	if (buffer == NULL)
		return -1;

	// Set head/tail pointers to beginning
	buffer->head = buffer->beginning;
	buffer->tail = buffer->beginning;

	// Reset item counter
	buffer->itemCount = 0;

	return 0;
}

/*
 * Free memory allocated for buffer
 */
uint8_t CircBuffFree(CircBuff * buffer){
	free(buffer->beginning);
	return 0;
}
