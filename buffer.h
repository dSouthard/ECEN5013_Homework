/*
 * buffer.h
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 */

#ifndef BUFFER_H_
#define BUFFER_H_

/*
 * Design a circular buffer data structure that will track a sequence of Transmit characters as well as
 * sequence of receive characters into a holding buffer. It should hold data needed to write/read data
 * from the serial terminal and also have something to receive data from the serial terminal.
 *
 * Note: CircBuff will be implemented as a FIFO buffer
 */

typedef struct stCircBuff {
	void * beginning;	// Beginning of buffer in memory
	void * end;			// End of buffer in memory
	void * head;		// Pointer to next spot in buffer
	void * tail;		// Pointer to oldest spot in buffer
	size_t size;		// Size of buffer
	size_t itemSize;	// Size of each item (bytes)
	size_t capacity;	// Desired capacity of buffer
	uint_32 itemCount;	// Current number of items in buffer
} CircBuff;

/*
 * Initialize the circular buffer
 */
uint8_t InitCircBuff(CircBuff * buffer, size_t itemSize, size_t itemNumber);


/*
 * Add item to buffer
 */
uint8_t CircBuffInsert(CircBuff * buffer, void* item);

/*
 * Remove item from buffer
 */
uint8_t CircBuffRemove(CircBuff * buffer);

/*
 * Reset buffer -- all items are dropped
 */
uint8_t CircBuffReset(CircBuff * buffer);

/*
 * Free memory allocated for buffer
 */
uint8_t CircBuffFree(CircBuff * buffer);

#endif /* BUFFER_H_ */
