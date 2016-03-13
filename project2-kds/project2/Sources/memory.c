/*
 * memory.c
 *
 *  Created on: Mar 9, 2016
 *      Author: 1118648
 */


/*
* ***** memory.c *****
* Diana Southard
* ECEN 5013 Spring 2016
* Project 1
*
* Contains some basic memory movement options.
*
*/

#include <stdint.h>
#include <stddef.h>
#include "memory.h"

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
int8_t memmove(uint8_t * src, uint8_t * dst, uint32_t length) {
    // Check for invalid input
	if (src == NULL || dst == NULL || !(length > 0))
		return -1;

	// Check for duplicate input
	if ( dst == src)
		return 0;

	// memmove must check for overlap
	uint32_t index;


        if ((src < dst) && ((src + length) > dst))
        	/* < -- src -- >
        	 *        < -- dst -- > Overlap
        	 * Copy from end of src to end of dst
        	 */
            for (index = length; index > 0; index--)
                 dst[index-1] = src[index-1];
        else
            /* All other cases: Same Resulting Action
             * ** Case 1: **
             * < -- src -- >
        	 *               < -- dst -- > No Overlap
        	 * Copy from start of src to start of dst
        	 *
        	 * ** Case 2: **
             * < -- dst -- >
             *        < -- src -- > Overlap
             * Copy from start of src to start of dst
             *
             * ** Case 3: **
             * < -- dst -- >
             *                < -- src -- > No overlap
             * Copy from start of src to start of dst
             */
             for (index = 0; index < length; index ++ )
                 dst[index] = src[index];
        return 0;
}

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
int8_t memcpy(uint8_t * src, uint8_t * dst, uint32_t length) {
	// Check for invalid input
	if (src == NULL || dst == NULL || !(length > 0))
		return -1;

	// Check for duplicate input
	if ( dst == src)
		return 0;

	// memcpy does not check for overlap
	uint32_t index;
	for (index = 0; index < length; index ++ ) {
		dst[index] = src[index];
	}

        return 0;
}

/*
* Implementation of memzero: Takes a pointer to a memory location and a length
* in bytes and zeros out all of the memory. Returns an error if the move failed.
*
* @param src - source location for memory to be zeroed out
* @param length - length of memory to be zeroed out
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t memzero(uint8_t * src, uint32_t length){
    // Check for invalid input
    if (src == NULL || !(length > 0))
        return -1;

    uint32_t index;
    for (index = 0; index < length; index ++)
        src[index] = 0;

    return 0;
}


/*
* Implementation of reverse: Takes a pointer to a memory location and a length
* in bytes and reverse the order of all of the bytes. Returns an error if the
* move failed.
*
* @param src - source location for memory reversal
* @param length - length of memory desired to be reversed
* @return - returns 0 if move is successful, error code if otherwise
*/
int8_t reverse(uint8_t * src, uint32_t length){
    // Check for valid input
    if (src == NULL || !(length > 0))
        return -1;

    uint8_t temp;   // Used for swapping
    length--;   // Set to a 0-base count
    uint32_t index;
    for (index = 0; index < length; index++, length--){
        temp = src[index];           // Grab character at start
        src[index]= src[length];     // Swap with character at end
        src[length]= temp;           // Change character at end
    }

    return 0;
}

