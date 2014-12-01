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

#define DATA_FRAME_LEN	20U			// 20 bytes for one frame
#define DATA_FRAME_HEADER1	0xFF
#define DATA_FRAME_HEADER2	0xAA

// Command sent bythe parent to the child
#define CMD_FRAME_LEN	
#define SEND_DATA		0xFA
#define	SET_ASL			0x

//====================================================================================
//							TASK COMMANDS
//====================================================================================

#define TASK_NO_ERROR	0x00
#define TASK_FAILED		0x01

#endif
