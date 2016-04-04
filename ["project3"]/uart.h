/*
 * uart.h
 *
 *  Created on: Apr 4, 2016
 *      Author: Diana Southard
 *
 */

#ifndef UART_H_
#define UART_H_

/*
 * Configure the UART interface of the Freedom Freescale board to have a method to print data
 * off the board without the use of printf and the debug console. Use the same USB connector
 * labeled as for the debug interface.
 *
 * Suggested UART configuration:
 * - LSB first (on by default)
 * - 1 Start/1 Stop bits
 * - 8-bit data transfers
 * - No parity
 * - 115200 Baud. Selecting high baud rates will be better for speed but BAUD rate is dependent
 * on the UART clock and BAUD prescaler registers. Sometimes getting a strange combo of BAUD and
 * UART clock will not give you an exact BAUD clock rate, but rather produce some timing errors.
 *
 * You will need to write code that can receive and transmit UART characters. Transmission can
 * easily be done with a pointer to some data and a length. You can interate over the data sending
 * each byte until you have finished. Receiving data requires the use of RX UART interrupts. However,
 * you need to store each received UART character into some larger data structure for processing.
 *
 * After you have written your transmit and receive functions (that can transmit a sequence of
 * characters) you will need to create a wrapper function that can take a string of characters in addition
 * and a parameter. You will need to use your ftoa/itoa functions to transmit your variable data through
 * your UART. You will need to write this code inside of some wrapper functions called LOG() in which you
 * will use to send data on your serial terminal. This log function will take a string of ascii charaters
 * to reprsent on the serial terminal. This can be used for debugging or general I/O. However, Logging
 * can cause a lot of overhead for your processing. So you will need to extend the LOG functionality
 * to five it a compile time switch to turn on or off this feature. Meaning providing some type of
 * preprocessor directive to Enable/Disable logging functionality. Call this macro DEBUG, VERBOSE, or DPRINT.
 *
 *
 */

// Macros, definitions
#define UART_115200 115200	// UART in 115200 BAUD
#define VERBOSE

// Macros for better readability
#define SIM 	SIM_BASE_PTR
#define UART0	UART0_BASE_PTR
#define PORTA	PORTA_BASE_PTR

// Initialize UART
void InitUart();

// Transmit a character via UART
void sendUART(char sendChar);

// Receive a character via UART
// This function will be called by Rx Interrupt
char receiveUART();

#endif /* UART_H_ */
