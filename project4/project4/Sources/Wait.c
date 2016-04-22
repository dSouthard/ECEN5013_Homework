/*
 * Wait.c
 *
 *  ECEN 5013 Spring 2016
 *  Created on: Apr 21, 2016
 *      Author: Diana Southard
 *
 * Implements busy waiting routines.
 * Based on file created by PE
 *
 */

#include "Wait.h"
#include <stdint.h>

/*
** ===================================================================
**     Method      :  WAIT1_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked)) void WAIT1_Wait10Cycles(void)
{
  /* This function will wait 10 CPU cycles (including call overhead). */
  /* NOTE: Cortex-M0 and M4 have 1 cycle for a NOP */
  /* Compiler is GNUC */
  __asm (
   /* bl Wai10Cycles() to here: [4] */
   "nop   \n\t" /* [1] */
   "nop   \n\t" /* [1] */
   "nop   \n\t" /* [1] */
   "bx lr \n\t" /* [3] */
  );
}

/*
** ===================================================================
**     Method      :  WAIT1_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__attribute__((naked)) void WAIT1_Wait100Cycles(void)
{
  /* This function will spend 100 CPU cycles (including call overhead). */
  __asm (
   /* bl to here:               [4] */
   "movs r0, #0 \n\t"        /* [1] */
   "loop:       \n\t"
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "add r0,#1   \n\t"        /* [1] */
   "cmp r0,#9   \n\t"        /* [1] */
   "bls loop    \n\t"        /* [3] taken, [1] not taken */
   "nop         \n\t"        /* [1] */
   "bx lr       \n\t"        /* [3] */
  );
}

/*
** ===================================================================
**     Method      :  WAIT1_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_WaitCycles(uint16_t cycles)
{
  while(cycles > 100) {
    WAIT1_Wait100Cycles();
    cycles -= 100;
  }
  while(cycles > 10) {
    WAIT1_Wait10Cycles();
    cycles -= 10;
  }
}

/*
** ===================================================================
**     Method      :  WAIT1_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_WaitLongCycles(uint32_t cycles)
{
  while(cycles>60000) {
    WAIT1_WaitCycles(60000);
    cycles -= 60000;
  }
  WAIT1_WaitCycles((uint16_t)cycles);
}

/*
** ===================================================================
**     Method      :  WAIT1_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Waitms(uint16_t ms)
{
  uint32_t msCycles; /* cycles for 1 ms */

  /* static clock/speed configuration */
  msCycles = WAIT1_NofCyclesMs(1, CPU_CORE_CLK_HZ);
  while(ms>0) {
    WAIT1_WaitLongCycles(msCycles);
    ms--;
  }
}
/*
** ===================================================================
**     Method      :  WAIT1_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT1_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
