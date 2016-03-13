/*
 * ECEN 5013 Spring 2016
 * Diana Southard
 * Project 2: LED Fader
 *
 * Part 1: Write a simple set of timer routines that can cycle through the various color schemes of the RGB LED to
 * produce a colorful LED Fader that cycles through all the colors of a rainbow.
 *
 * Part 2: Profile memory functions written in Project 1
 *
 * Part 3: Profile memory functions using DMA
 */

#include "MKL25Z4.h"	// TPM_Type structure is declared in MKL25Z4.h
#include <math.h>
#include "timer.h"
#include "profiler.h"

// Split work into sections so that the program knows which memory functions to include and test
// NOTE: ONLY ENABLE ONE OF THE FOLLOWING DEFINITIONS AT A TIME
#define PART2_MYFUNCTIONS		// Part 2: profiling memory functions from project 1
//#define PART2_BUILTIN			// Part 2: profiling memory functions from library
//#define PART3					// Part 3: profiling memory functions using DMA operations


#ifdef PART3
#include "memoryDMA.h"
#endif



int main()
{
// Setup system clock
	initializeClock();	// Will need the clock for all parts

// Part 1: KDS Timer Interrupts and RGB PWM
	// Setup timers
	setupTPM();

#ifdef PART3
	dmaSetup();	// If doing Part 3, setup DMA Controller
#endif
	// Run profiler on memory functions
	testMemory();

	// Run profiler on printf functions
	testPrint();


    return 0;
}


