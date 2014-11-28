/*
 * Project.h
 *	This header file shall contain the global
 *	typedefs and other project related macros.
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#ifndef __PROJECT_H_
#define __PROJECT_H_

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef float uint32f_t;
typedef uint8_t id_t;
typedef uint16_t load_t;
typedef uint16_t time_t;
typedef uint8_t state_t;
typedef uint8_t status_t;
typedef uint8_t pin_t;
typedef uint8_t comm_t;
typedef float prio_t;
typedef uint8_t cmd_t;


// For converting Float to bytes and bytes to float
typedef union {
	uint32f_t val_float;
	uint32_t val_long;
}float_long_Buffer;



uint16_t GLOBAL_TICK;
/********************************************************************************************
						Project Specific Configurations
*********************************************************************************************/

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    COMMUNICATION	 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/* I2C
	Use address 0x00 for master
	for others prefer 0x01 to 0x06
*/
#define SRC_I2C_ADDRESS		0x01
#define DEST_I2C_ADDRESS	0x02

/* UART
	specify the baud rates here
*/
#define UART_BAUD_RATE	9600

/* BLE
	Specify BLE related settings here
*/

/*	SPI
	Specify SPI related settings here
*/

#endif /* PROJECT_H_ */
