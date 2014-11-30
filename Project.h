/*
 * Project.h
 *	This header file shall contain the global
 *	typedefs and other project related macros.
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

/* 
	Arduyino libraries to be used by the project
*/
#include <Wire.h>


#ifndef __PROJECT_H_
#define __PROJECT_H_

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef float uint32f_t;
typedef uint8_t id_t;
typedef uint8_t device_t;
typedef uint16_t baud_t;	// Arduino specific, other arch may req more data
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


//uint16_t GLOBAL_TICK;


#define TRUE	0x01
#define FALSE	0x00
/********************************************************************************************
						Project Specific Configurations
*********************************************************************************************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    NODES			 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

#define NUMCHILD	2

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    COMMUNICATION	 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/* I2C
	Use address 0x00 for master
	for others prefer 0x01 to 0x06
*/
#define SRC_I2C_ADDRESS			0x01
#define SRC_BLE_ADDRESS			0x00
#define PARENT_I2C_ADDRESS		0x02
#define PARENT_BLE_ADDRESS		0x00

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
