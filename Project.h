/*
 * Project.h
 *	This header file shall contain the global
 *	typedefs and other project related macros.
 COnfigure this file as per requirement
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

/* 
	Arduyino libraries to be used by the project
*/


#ifndef __PROJECT_H_
#define __PROJECT_H_

#include "Arduino.h"

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef float uint32f_t;
typedef uint8_t id_t;
typedef uint8_t device_t;
typedef uint16_t baud_t;	// Arduino specific, other arch may req more data
typedef uint32_t load_t;
typedef uint32_t time_t;
typedef uint8_t state_t;
typedef uint8_t status_t;
typedef uint8_t pin_t;
typedef uint8_t comm_t;
typedef float prio_t;
typedef uint8_t cmd_t;
typedef uint8_t addr_t;

#define TIME_MAX 	0xFFFFFFFF	// uint32MAX

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

#define NUM_CHILDS	2U
#define NUM_LOADS	4U
#define NODE_ID		23U	// test
#define NODE_PID	32U	// test

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    COMMUNICATION	 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/* I2C
	Use address 0x00 for master
	for others prefer 0x01 to 0x06
*/

//Address independent of the medium
#define SRC_ADDRESS				0x00
#define PARENT_ADDRESS			0x02


#define CHILD1_ID				0x01
#define CHILD2_ID				0x02
#define CHILD3_ID				0x03
#define CHILD4_ID				0x04	// define more if necessary


#define CHILD1_I2C_ADDR			0x01
#define CHILD2_I2C_ADDR			0x02
#define CHILD3_I2C_ADDR			0x03
#define CHILD4_I2C_ADDR			0x04 // define more if necessary


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


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    METHODS	 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

void Setup(void);
void Loop(void);

#endif /* PROJECT_H_ */
