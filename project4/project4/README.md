# Project 4: SPI with External Peripherals and Code Abstraction

## ECEN 5013 Spring 2016
Diana Southard

#### Part 1: Serial Peripheral Interface
The SPI of the two boards involved very different setups. For the Freedom Freescale board, low level firmware needed to be correctly configured. The BeagleBone, however, includes an onboard SPI driver so there was no low level setup required. The specific steps of the two boards setups are discussed in this part.


#### Part 2: Extend Interface to Stream Transceiver Data
To configure the devices to stream data between each other, one device had to be set up as the transmitter and the other had to be set up as the receiver. This part details the process involved in setting up that wireless communication.
