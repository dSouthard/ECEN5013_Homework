/*
* ***** memory.h *****
* Diana Southard
* ECEN 5013 Spring 2016
* Project 1
*
* Contains some basic memory movement options.
*
*/
#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdint.h>

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
* Implementation of memcpy:
* Copies a length of bytes from source location to destination location.
* This checks overlapped areas between the two memory blocks. Returns an error
* if the move failed.
*
* @param src - source location for memory move
* @param dst - destination location for memory move
* @param length - length of memory desired to move
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t memcpy(uint8_t * src, uint8_t * dst, uint32_t length);



/*
* Implementation of memzero: Takes a pointer to a memory location and a length
* in bytes and zeros out all of the memory. Returns an error if the move failed.
*
* @param src - source location for memory to be zeroed out
* @param length - length of memory to be zeroed out
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t memzero(uint8_t * src, uint32_t length);



/*
* Implementation of reverse: Takes a pointer to a memory location and a length
* in bytes and reverse the order of all of the bytes. Returns an error if the
* move failed.
*
* @param src - source location for memory reversal
* @param length - length of memory desired to be reversed
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t reverse(uint8_t * src, uint32_t length);


#endif

