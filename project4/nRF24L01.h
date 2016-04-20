/*
 * sRF24L01.h
 *
 * ECEN 5013 Spring 2016
 *
 *  Created on: Apr 20, 2016
 *      Author: Diana Southard
 *
 * Holds all registers, constants, and other structure interface definitions,
 * calls SPI libraries
 */

#ifndef INCLUDES_NRF24L01_H_
#define INCLUDES_NRF24L01_H_


// Create a Nordic library that provides constant and interface information on the Nordic chip itself like the register map and the configuration values that are listed below:
#define NORDIC_STATUS_REG 0x00
#define NORDIC_TXADDR_REG 0x10
#define NORDIC_POWER_UP (1)
#define NORDIC_POWER_DOWN (0)
#define NORDIC_POWER_UP_MASK (0x02)


// Create a high level library that uses this lower level SPI library and applies specific control over it to work with the Nordic Chipset:
void nrf_config();
void nrf_read_register();
void nrf_write_register();
void nrf_transmit_data();
void nrf_flush_tx_fifo();

#endif /* INCLUDES_NRF24L01_H_ */
