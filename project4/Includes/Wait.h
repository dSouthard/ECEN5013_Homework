/*
 * Wait.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Diana Southard
 */

#ifndef INCLUDES_WAIT_H_
#define INCLUDES_WAIT_H_

#define WAIT1_NofCyclesMs(ms, hz)  ((ms)*((hz)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define WAIT1_NofCyclesUs(us, hz)  ((us)*(((hz)/1000)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define CPU_CORE_CLK_HZ                 20971520U /* Initial value of the core/system clock frequency in Hz.  */
#define CPU_BUS_CLK_HZ                  20971520U /* Initial value of the bus clock frequency in Hz */

#define WAIT1_WAIT_C(cycles) \
     ( (cycles)<=10 ? \
          WAIT1_Wait10Cycles() \
        : WAIT1_WaitCycles((uint16_t)cycles) \
      )                                      /*!< wait for some cycles */


void WAIT1_Wait10Cycles(void);
/*
** ===================================================================
**     Method      :  WAIT1_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_Wait100Cycles(void);
/*
** ===================================================================
**     Method      :  WAIT1_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_WaitCycles(uint16_t cycles);
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

void WAIT1_Waitms(uint16_t ms);
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

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT1_Waitus(us)  \
       (  ((WAIT1_NofCyclesUs((us),CPU_BUS_CLK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : WAIT1_Waitms((uint16_t)((us)/1000))) \
          , (WAIT1_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)==0) ? (void)0 : \
            WAIT1_WAIT_C(WAIT1_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)) \
       )
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

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT1_Waitns(ns)  \
       (  ((WAIT1_NofCyclesNs((ns), CPU_BUS_CLK_HZ)==0)||(ns)==0) ? \
          (void)0 : \
          WAIT1_Waitus((ns)/1000) \
          , (WAIT1_NofCyclesNs((ns)%1000, CPU_BUS_CLK_HZ)==0) ? \
              (void)0 : \
              WAIT1_WAIT_C(WAIT1_NofCyclesNs(((ns)%1000), CPU_BUS_CLK_HZ)) \
       )
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

#define WAIT1_WaitOSms(ms) \
  WAIT1_Waitms(ms) /* no RTOS used, so use normal wait */
/*
** ===================================================================
**     Method      :  WAIT1_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


void WAIT1_WaitLongCycles(uint32_t cycles);
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


#endif /* INCLUDES_WAIT_H_ */
