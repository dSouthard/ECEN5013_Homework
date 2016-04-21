/*
 * main.c
 *
 *  Created on: Apr 20, 2016
 *      Author: Diana Southard
 */


#include "spi.h"
#include "nRF24L01.h"
#include "uart.h"
#include "log.h"

static const uint8_t TADDR[5] = {0x11, 0x22, 0x33, 0x44, 0x55}; /* device address */

int main() {
	// Initialize board clocks
	SystemInit();

	// Initialize the Nordic module
	WAIT1_Waitms(100); 	/* give device time to power up */
	RF_Init(); 			/* set CE and CSN to initialization value */

	// Initialize SPI Modules
	SPI_init();

	/* Things to show:
	 * CONFIG register (read/write)
	 * STATUS register (read) using the NOP command
	 * TX_ADDR: Set this value and be able to validate the address was configured
	 * RF_SETUP register (read/write) specifically what the transmit power is
	 * FIFO_STATUS register (Read)
	 */
	// Set TX_ADDR value
	/* Set RADDR and TADDR as the transmit address since we also enable auto acknowledgment */
	nRFWriteRegisterBuffer(RF24_TX_ADDR, (uint8_t*)TADDR, sizeof(TADDR));
	RF_WriteRegisterData(RF24_RX_ADDR_P0, (uint8_t*)TADDR, sizeof(TADDR));

	nRFWriteRegister(RF24_EN_AA, RF24_EN_AA_ENAA_P0); /* enable auto acknowledge. RX_ADDR_P0 needs to be equal to TX_ADDR! */
	nRFWriteRegister(RF24_SETUP_RETR, RF24_SETUP_RETR_ARD_750|RF24_SETUP_RETR_ARC_15); /* Important: need 750 us delay between every retry */
	TX_POWERUP();  /* Power up in transmitting mode */
	CE_ClrVal();   /* Will pulse this later to send data */

	// Read back value to validate
	uint8_t TADDR_test[5];
	nRFReadRegisterBuffer(RF24_TX_ADDR, (uint8_t*)TADDR_test, sizeof(TADDR_test));
	UARTlog(TADDR_test, sizeof(TADDR_test));

	uint8_t regBuffertest[8];	// Used for reading back from registers
	// Read the CONFIG register
	nRFReadRegisterBuffer(RF24_CONFIG,(uint8_t*)regBuffertest, sizeof(regBuffertest));
	UARTlog(regBuffertest, sizeof(regBuffertest));

	// Read the Status register
	nRFReadRegisterBuffer(RF24_STATUS,(uint8_t*)regBuffertest, sizeof(regBuffertest));
	UARTlog(regBuffertest, sizeof(regBuffertest));

	// Read back value of RF_Setup register to validate setting written during nRFConfig
	nRFReadRegisterBuffer(RF24_RF_SETUP, (uint8_t*)regBuffertest, sizeof(regBuffertest));
	UARTlog(regBuffertest, sizeof(regBuffertest));

	// Read the value of the FIFO_STATUS register
	nRFReadRegisterBuffer(RF24_FIFO_STATUS, (uint8_t*)regBuffertest, sizeof(regBuffertest));
	UARTlog(regBuffertest, sizeof(regBuffertest));

	return 0;

}
