/* The header file contains the definitions of the 
various commands and macros that may be used

Arun M Kumar				24 Nov 2014*/

#ifndef __COMMAND_H
#define __COMMAND_H


//====================================================================================
//							LOAD COMMANDS
//====================================================================================

#define LOAD_NOT_INIT 	0x00
#define LOAD_INIT		0x010
#define LOAD_DATA_READY	0x02

#define STATE_NOT_INIT	0x00
#define STATE_ON		0x01
#define STATE_OFF		0x03

#define TIME_NOT_INIT	0x00
#define ID_NOT_INIT		0x00

#define PRIO_MIN		1.0f
#define PRIO_MAX		6.0f
#define PRIO_NOT_INIT	(PRIO_MAX)	// currently the least priority

#define PIN_LOW				0x00
#define PIN_HIGH			0x01
#define PIN_INPUT			0x00
#define PIN_OUTPUT			0x01
#define PIN_INPUT_PULLUP 	0x02

// Project dependent Load Read Pins
// currently supporting only UNO and clones

#define LOAD_1R  A0  //where to read
#define LOAD_2R  A1  //where to read
#define LOAD_3R  A2  //where to read
#define LOAD_4R  A3  //where to read
#define LOAD_5R  A4  //where to read
#define LOAD_6R  A5  //where to read

// Project dependent Load Write Pin s : IMP: Leave 0 and 1 for Serial
#define LOAD_1W  0x02  // Which pin to write to
#define LOAD_2W  0x03  // Which pin to write to
#define LOAD_3W  0x04  // Which pin to write to
#define LOAD_4W  0x05  // Which pin to write to
#define LOAD_5W  0x06  // Which pin to write to
#define LOAD_6W  0x07  // Which pin to write to

#define LOAD_DATA_LEN	0x10	// 16 bytes of data
#define LOAD_NO_ID		0xFF

//defining the commands
#define LOAD_OFF   0x00
#define LOAD_ON    0x01
#define LOAD_READ  0x02


//====================================================================================
//							NODE COMMANDS
//====================================================================================
#define NODE_NO_ID		0xFA

#define NODE_NOT_INIT	0x00
#define NODE_INIT		0x03



//====================================================================================
//							COMM COMMANDS
//====================================================================================

#define COMM_NOT_DEFINED	0x00	// No Communication defined
#define COMM_TYPE_I2C		0x01	// Communicatio over I2C
#define COMM_TYPE_UART		0x02	// Communication over UART
#define COMM_TYPE_BLE		0x03	// Communication over BLE
#define COMM_TYPE_SPI		0x04	// Communication over SPI


#define COMM_NOT_INIT		0x00
#define COMM_INIT			0x01
#define COMM_ERROR			0x02

#define COMM_DATA_AVAIL		0x01

#define COMM_TX_SUCCESS		0x00
#define COMM_TX_FAIL		0x01

//====================================================================================
//							PROTOCOL COMMANDS
//====================================================================================

#define FRAME_LEN		0x0A

//====================================================================================
//							BUFFER COMMANDS
//====================================================================================
// defining parameters
#define BUFFER_LEN		100U


// Defining the error codes
#define BUF_NOERROR		0x00
#define BUF_UNDERFLOW	0x01
#define BUF_OVERFLOW	0x02


//====================================================================================
//							TASK COMMANDS
//====================================================================================

#define TASK_NO_ERROR	0x00
#define TASK_FAILED		0x01

#endif
