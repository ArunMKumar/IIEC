/* The header file contains the definitions of the 
various commands and macros that may be used

Arun M Kumar				24 Nov 2014*/

#ifndef __COMMAND_H
#define __COMMAND_H




//====================================================================================
//							NODE COMMANDS
//====================================================================================
#define NODE_NO_ID		0xFA

#define NODE_NOT_INIT	0x00
#define NODE_INIT		0x03
//====================================================================================
//							PROTOCOL COMMANDS
//====================================================================================

#define FRAME_LEN		0x0A
#define FRAME_HEADER1	0xFF
#define FRAME_HEADER2	0xAA
#define SEND_DATA		0xFA

//====================================================================================
//							TASK COMMANDS
//====================================================================================

#define TASK_NO_ERROR	0x00
#define TASK_FAILED		0x01

#endif
