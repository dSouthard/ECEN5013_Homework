# Project 1

ECEN 5013 Spring 2016

Diana Southard

## Folder Containing Required Files for Project 1

__Requirements:__
We are required to make the following software:
* **memory.c/memory.h**-This file should have some basic memory movement options. You will need to support a few functions. These need to be written on your own. As we will use them in follow up assignments and compare them with the library versions.
	a. int8\_t memmove(uint8\_t* src, uint8\_t * dst, uint32_t length)
		i. This should take two pointers(one source and one destination)and a lengthof bytes to move from one location to the other.
		ii. This will need to make sure it correctly checks overlapped areas between the two memory blocks.
		iii. Should return an error if the move failed.
	b. int8\_t memcpy(uint8\_t* src, uint8\_t * dst, uint32_t length)
		i.This should take two pointers(one source and one destination)and a lengthof bytes to copyfrom one location to the other.
		ii.This will need to make sure it correctly checks overlapped areas between the two memory blocks.
		iii.Should return an error if the move failed.
	c. int8\_t memzero(uint8\_t* src,uint32_t length)
		i.This should take a pointer to a memory locationand a length in bytes and zero out all of the memory.
		ii.Should return an error if the move failed.
	d. int8\_t reverse(uint8\_t* src, uint32_t length)
		i.This should take a pointer to a memory location and a length in bytes and reverse the order of all of the bytes
		ii.This should be the same function from homework 2, but let us remove the conceptual dependency on the term string. 
	e. All Functions should return a non-zero return code for any error that might occur in the process of the function. A zero should be returned if successful
* **project_1.c/project_1.h** -This file should have a few functions that relate to the higher level tasks within this project.One function in particular needs to be provided:
	a.void project\_1_report();
		i.Create 1 array of 32 bytes(unsigned).
		ii.Create threepointers to two various points in this array:
			1.aptr_1: Initialize this pointeraddress to bethe beginning of the array
			2.aptr_2: Initialize this second pointer to be the address of the 8thelement in the array.
			3.aptr_3: Initialize this thirdpointer to be the address of the 16thelement in the array.
		iii.Initializememory at twoof thepointers:
			1.aptr_1: Initialize16 bytes starting at this aptr_1to thenumbers from 1-16.Do not modify the pointer address.
			2.aptr_3: Initialize the contents from this pointer to the end of the array to zeros using memzero. Do not modify the pointer address
		iv.Use memcpyto move 8 bytes from aptr_1 to aptr_3
		v. Use memmove to move 16bytesfromaptr_2to aptr_1. 
		vi.Use reverse on aptr_1to reverse the entire 32 bytes.
		vii.Use printf to print out the entire 32 byte array in a nicely formatted way.
* **main.c** -Your final executable main function. This needs to have a single line in the code that calls the project\_1_report function


