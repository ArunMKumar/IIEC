/*
Source file for the class described in Protocol.h

Arun M Kumar			26 Oct 2014
*/

#include "Protocol.h"


status_t getVal(Node* node){
	
	uint8_t loc;
	
	if (BUF_UNDERFLOW == node->commChild.readInBuffer(&loc)){
		return BUF_UNDERFLOW;						// if nothing in buffer, then return immedieately
	}

	else{
		while (FRAME_HEADER != loc){
			node->commChild.readInBuffer(&loc);		// read till you find the header
		}

		// we have read the frame header, now lets put the data in place.
	}

}

status_t setVal(Node* node){

}