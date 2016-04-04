/*
 * uart.c
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 *
 *      Holds all UART initialization and setup code
 */

#include "uart.h"
#include "MKL25Z4.h" /* include peripheral declarations */
#include <stddef.h>
#include <stdint.h>

// Initialize UART
void InitUART0(){

#ifdef VERBOSE
	printf("Configuring UART at 115200 BAUD\n");
#endif

	/* 115200 baud: serialBaudRate 13, overSampleRate 15 is known to work */
	static const uint16_t serialBaudRate = 13U;
	static const uint8_t overSampleRate = 15U;

	/* enable clock gating to UART0 module */
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

	/* disable RX and TX */
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	/* set UART clock to PLL/2 clock */
	SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b01U) | SIM_SOPT2_PLLFLLSEL_MASK;

	/* enable clock gating to port A */
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /* enable clock to port A (PTA1=rx, PTA2=tx) */

	/* set pins to UART0 RX/TX */
	/* not using |= assignment here due to some of the flags being undefined at reset */
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	/* alternative 2: RX */
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	/* alternative 2: TX */

	/* configure the UART */
	UART0->BDH =  (0 << UART_BDH_LBKDIE_SHIFT) 		/* disable line break detect interrupt */
			| (0 << UART_BDH_RXEDGIE_SHIFT) 		/* disable RX input active edge interrupt */
			| (0 << UART_BDH_SBNS_SHIFT) 			/* use one stop bit */
			| UART_BDH_SBR((serialBaudRate & 0x1F00) >> 8); 	/* set high bits of scaler */

	UART0->BDL = UART_BDL_SBR(serialBaudRate & 0x00FF);		/* set low bits of scaler */

	/* set over-sampling ratio */
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(overSampleRate);

	/* set over-sampling ratio when over-sampling is between 4 and 7
	 * (it is optional for higher over-sampling ratios) */
	UART0->C5 = 0;

	/* keep default settings for parity and loop-back */
	UART0->C1 = 0;

	UART0->C3 = 0;

	/* clear flags to avoid unexpected behavior */
	UART0->MA1 = 0;
	UART0->MA2 = 0;
	UART0->S1 |= UART0_S1_IDLE_MASK
			| UART0_S1_OR_MASK
			| UART0_S1_NF_MASK
			| UART0_S1_FE_MASK
			| UART0_S1_PF_MASK;

	UART0->S2 = (UART0_S2_LBKDIF_MASK | UART0_S2_RXEDGIF_MASK);

	/* enable RX and TX */
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK;
}

// Transmit a character via UART
void UARTsendChar(char sendChar){

	// Check if UART is busy, and wait until free.
	while(!(UART0->S1 & UART_S1_TC_MASK));
	UART0->D = sendChar;

}

// Receive a character via UART
// This function will be called by RX Interrupt
char UARTreceiveChar(){

	// Check if finished and wait until byte received
	while(!(UART0->S1 & UART_S1_RDRF_MASK)); //Wait until full
	return UART0->D;
}
