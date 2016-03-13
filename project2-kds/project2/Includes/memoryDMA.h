/*
* ***** memory.h *****
* Diana Southard
* ECEN 5013 Spring 2016
* Project 2
*
* Contains some basic memory movement options.
* Adjusted to use DMA Operation for data transfer.
* The only operations being tested with the DMA
* controller are memmove and memzero.
*
*/

#ifndef INCLUDES_MEMORYDMA_H_
#define INCLUDES_MEMORYDMA_H_

#include <stdint.h>
#include "MKL25Z4.h"

#define DMA_CH0				0
#define TRANSFER_8BIT	 	3
#define INCREMENT_SIZE		1

void dmaSetup();
void srcIncrement();
void srcNoIncrement();
void dstIncrement();
void loadSrc(uint8_t * src);
void loadDst(uint8_t * dst);
void loadByteSize(uint32_t size);


void transferData();


/*
* memmove
* Implementation of memmove: Moves a length of bytes from source location to
* destination location. This checks overlapped areas between the two memory
* blocks. Returns an error if the move failed.
*
* @param src - source location for memory move
* @param dst - destination location for memory move
* @param length - length of memory desired to move
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t memmove(uint8_t * src, uint8_t * dst, uint32_t length);


/*
* Implementation of memzero: Takes a pointer to a memory location and a length
* in bytes and zeros out all of the memory. Returns an error if the move failed.
*
* @param src - source location for memory to be zeroed out
* @param length - length of memory to be zeroed out
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t memzero(uint8_t * src, uint32_t length);


#endif /* INCLUDES_MEMORYDMA_H_ */
