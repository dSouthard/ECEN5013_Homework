/*
 * nRF24L01.c
 *
 * ECEN 5013 Spring 2016
 *
 *  Created on: Apr 20, 2016
 *      Author: Diana Southard
 *
 * Holds all registers, constants, and other structure interface definitions,
 * calls SPI libraries
 */
#include "nRF24L01.h"
#include "SPI.h"
#include "MKL25Z4.h"
#include <stdint.h>
#include <stddef.h>

// Configure the initialization values for the Nordic module
void nRFConfig() {
	// Initialize pins to desired value
	// CE: Low means 'Not sending/listening', set initial value = 0
	RF_CE_LOW();   	/* CE low: do not send or receive data */

	// CSN: configured as output pin with initial HIGH value. CSN is pulled LOW to send commands to the transceiver
	// --> Set initial value = 1
	RF_CSN_HIGH(); 	/* CSN high: not sending commands to the device */

	// Configure the output power (RF24_RF_SETUP_RF_PWR_0) and the data rate (250 kbit, RF24_RF_SETUP_RF_DR_250)
	nRFWriteRegister(RF24_RF_SETUP, RF24_RF_SETUP_RF_PWR_0|RF24_RF_SETUP_RF_DR_250);
}


/* nRFWriteRegister
 * @brief 		Write a register value to the transceiver
 * @param reg 	Register to write
 * @param value Value of the register to write
 */
void nRFWriteRegister(uint8_t reg, uint8_t value) {
	// Check for valid input
	if (reg < 0 || reg > LAST_REG)
		return;

	RF_CSN_LOW(); 					/* initiate command sequence */
	SPIwrite(RF24_W_REGISTER|reg); 	/* write register command */
	SPIwrite(value); 			/* write value */

	// Wait for SPI Transmit Data Buffer Empty flag (SPTEF) to set -- data transmitted
	while (!(SPI0->S & SPI_S_SPTEF_MASK));
	RF_CSN_HIGH(); 					/* end command sequence */
	RF_WAIT_US(10); 				/* insert a delay until next command */
}


/* nRFReadRegister
 * @brief 		Read and return the value of desired reg
 * @param reg 	Register to read
 * @return 		Value of register
 */
uint8_t nRFReadRegister(uint8_t reg) {
	// Check for valid input
	if (reg < 0 || reg > LAST_REG)
		return NULL;

	RF_CSN_LOW(); 			/* initiate command sequence */
	// Clear the data register after command is sent
	SPIwrite(RF24_R_REGISTER|reg); 	/* read register command */

	// Retrieve data
	uint8_t data = SPIread();

	RF_CSN_HIGH(); 			/* end command sequence */
	RF_WAIT_US(10); 		/* insert a delay until next command */
	return data;
}

/* nRFWriteRegisterBuffer
 * @brief Write multiple bytes from the bus.
 * @param reg Register address
 * @param buf Buffer of what to write
 * @param bufSize Buffer size in bytes
 */
void nRFWriteRegisterBuffer(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
	// Check for valid input
	if (reg < 0 || reg > LAST_REG || buf == NULL)
		return;

	RF_CSN_LOW(); 		/* initiate command sequence */
	SPIwrite(RF24_W_REGISTER|reg); /* read register command */

	uint8_t index;
	for (index = 0; index < bufSize; index++) {
		SPIwrite(buf[index]);
	}
	RF_CSN_HIGH(); 		/* end command sequence */
	RF_WAIT_US(10);		/* insert a delay until next command */
}

/* nRFReadRegisterBuffer
 * @brief Read multiple bytes from the bus.
 * @param reg Register address
 * @param buf Buffer where to write the data
 * @param bufSize Buffer size in bytes
 */
void nRFReadRegisterBuffer(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
	// Check for valid input
	if (reg < 0 || reg > LAST_REG || buf == NULL)
		return;

	RF_CSN_LOW(); 						/* initiate command sequence */
	SPIwrite(RF24_R_REGISTER|reg); 		/* read register command */

	uint8_t * bufferPointer = buf;	// Start of return data

	uint8_t index;
	for (index = 0; index < bufSize; index++) {
		SPIwrite(RF24_NOP);	// Send RF24_NOP to get data
		*bufferPointer = SPIread(); 	// Get the next byte
		bufferPointer++;
	}

	RF_CSN_HIGH(); 						/* end command sequence */
	RF_WAIT_US(10);						/* insert a delay until next command */
}


/* nRFWriteFIFO
 * @brief 		Send the buffer to the Tx FIFO and send it
 * @param buf 	Buffer with data to send
 * @param buf	Size Size of buffer to send
 */
void nRFWriteFIFO(uint8_t *buf, uint8_t bufSize) {
  SPIwrite(RF24_FLUSH_TX); /* flush old data */
  nRFWriteRegisterBuffer(RF24_W_TX_PAYLOAD, buf, bufSize); /* write payload */
  RF_CE_HIGH(); /* start transmission */
  RF_WAIT_US(15); /* keep signal high for 15 micro-seconds */
  RF_CE_LOW();  /* back to normal */
}

/* nRFReadFIFO
 * @brief 		Receive the Rx payload from the FIFO and stores it in a buffer.
 * @param buf 	Pointer to the received buffer
 * @param buf	Size Size of the received buffer
 */
void nRFReadFIFO(uint8_t *buf, uint8_t bufSize) {
  RF_CE_LOW(); /* need to disable rx mode during reading RX data */
  nRFReadRegisterBuffer(RF24_R_RX_PAYLOAD, buf, bufSize); /* rx payload */
  RF_CE_HIGH(); /* re-enable rx mode */
}



