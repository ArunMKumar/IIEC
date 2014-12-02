/*
 * Node.cpp
 *	Source file for the Nodes,
 *	contaisn the definition of the methods for
 *	Node class
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#include "Node.h"


Node::Node(){
	//Default constructor for the Node
	this->ID  = NODE_NO_ID;
	this->PID = NODE_NO_ID;
}

Node::Node(id_t ID, id_t PID){
	// Parameterized constructor for the Node
	this->ID = ID;
	this->PID = PID;
}

Node::Node(id_t ID, id_t PID, deviceAttrib_t* child, deviceAttrib_t* parent, addr_t childAddr[]){
	/*
		Overloaded constructor for initializing everything
	*/
	this->ID = ID;
	this->PID = PID;
	nodeCommInit(child, parent);
	nodeSetChildAddr(childAddr);
}

status_t Node::nodeSetChildAddr(addr_t childAddr[]){
	/*
		Sets the address of the child 
	*/

	for (int i = 0; i < NUM_CHILDS; i++){
		this->childAddr[i] = childAddr[i];
	}

	return NODE_INIT;
}

status_t Node::nodeInitChild(deviceAttrib_t* data){
	
	return commChild.commSetDevice(data);
}

status_t Node::nodeInitParent(deviceAttrib_t* data){

	return commParent.commSetDevice(data);
}

status_t Node::nodeCommInit(deviceAttrib_t* childComm, deviceAttrib_t* parentComm){
	/*
		Initializes the comm module for the In and out device
	*/
	nodeInitChild(childComm);
	nodeInitChild(parentComm);
}

void Node::setNodePRIO(LoadState_t loads[], childData_t childs[]){
	/*
	 * This method calculates the cumulative
	 * priority of the node
	 */
	prio_t nodePRIO = 0.0f;
	prio_t product= 1.0f;
	prio_t sum = 0.0f;

	for(int i=0; i < NUM_LOADS; i++){
		product *= loads[i].DPRIO;
		sum 	+= loads[i].DPRIO;
	}
	this-> PRIO = prio_t(product/sum);
}

void Node::setNodeLoadLimit(LoadState_t loads[], childData_t childs[]){
	/* This method calculates the various
	load parameters for the node*/
	load_t totalDLoad 	= 0x00;
	load_t totalDCL		= 0x00;

	for(int i=0; i < NUM_LOADS; i++){
		totalDL 	+= loads[i].DL;
		totalDCL	+= loads[i].DCL;
	}

	for(int i=0; i < NUM_CHILDS; i++){
		totalDLoad 	+= childs[i].DL;
		totalDCL	+= childs[i].DCL;
	}

	this->DLoad = totalLoad;
}


//====================================================================================
//							Comm protocol handling
//====================================================================================

status_t Node::ProtocolReadChild(childData_t child[]){
	/*
	This module parses the dat received on the In buffer
	to extract the relevant info from them
	we do not know where the data for the child will be so 
	we read all the buffer and place the read data at appropriate
	place in the childadata place holder
	*/

	uint8_t temp;

	if (commChild.commInDataAvail() > DATA_FRAME_LEN){		// if any Frame available in the Input buffer
			commChild.commReadBuffer(&temp);

		if (DATA_FRAME_HEADER1 == temp){
				commChild.commReadBuffer(&temp);	// read the second byte

			if (DATA_FRAME_HEADER2 == temp){	// Verify that we have received both the headers
				/*
					Now we shall read the ID provided and based on the ID place the
					child nodes accordingly
				*/
				commChild.commReadBuffer(&temp);	// read the ID.
				ProtocolReadChildData(child, temp);
			}
			else
				return TASK_FAILED;
		}
	}
	return TASK_NO_ERROR;
	
}

status_t Node::ProtocolReadParent(){
	/*
		Here we read the data and/or command from the parent
		run these on an interrupt
	*/
	uint8_t temp;

	if (commParent.commInDataAvail()){		// if any Frame available in the Input buffer
		commParent.commReadBuffer(&temp);
		// has parent requested data?
		if (CMD_FRAME_HEADER1 == temp){			// header 1 match
			commParent.commReadBuffer(&temp);	// read header 2
			if (CMD_FRAME_HEADER2 == temp){		//header 2 match : definitely a frame
				commParent.commReadBuffer(&temp); // get the command

				ProtocolHandleParentCmd(temp);		// handle the command
			
			}
		}
	}
}

status_t Node::ProtocolWriteChild(uint8_t Command[], uint8_t len, addr_t address){
	/*
		cyclic task to get data from child
	*/
	commChild.commWriteBuffer(CMD_FRAME_HEADER1);
	commChild.commWriteBuffer(CMD_FRAME_HEADER2);
	for(int i=0; i< len; i++){
		commChild.commWriteBuffer(Command[i]);
	}
	commChild.commSetTxStatus(TRUE);
	commChild.Transmit(address);

	return TX_SUCCESS;

}

status_t Node::ProtocolWriteParent(){
	/* Cyclic task to write data to parent */
	ProtocolsetParentData();
	commParent.commSetTxStatus(TRUE);
	commParent.Transmit(PARENT_ADDRESS);
	return TX_SUCCESS;
}

void Node::ProtocolsetParentData(void){
	/*
	Here we write data to the parent on the buffer and
	transmit it.
	*/

	commParent.commWriteBuffer(DATA_FRAME_HEADER1);	// write frame heade1 to buffer
	commParent.commWriteBuffer(DATA_FRAME_HEADER2);	// write frame heade1 to buffer
	commParent.commWriteBuffer(ID);					// write frame heade1 to buffer
	commParent.commWriteBuffer(PID);				// write frame heade1 to buffer
	commParent.commWriteBufferFloat(PRIO);			// write frame heade1 to buffer
	commParent.commWriteBufferWord(ASL);			// write frame heade1 to buffer
	commParent.commWriteBufferWord(DCL);			// write frame heade1 to buffer
	commParent.commWriteBufferWord(DL);				// write frame heade1 to buffer
}

void Node::ProtocolreadChildData(childData_t childs[], uint8_t index){
	commChild.commReadBuffer(&childs[index].PID);	// get the PID
	commChild.commReadBufferFloat(&childs[index].PRIO);
	commChild.commReadBufferWord(&childs[index].ASL);
	commChild.commReadBufferWord(&childs[index].DL);
	commChild.commReadBufferWord(&childs[index].DCL);
}

void Node::ProtocolHandleParentCmd(uint8_t Command){
	/*
		This method prepares the response to the various commands that are issued by the 
		Parent.
	*/
	switch (Command){

	case CMD_SEND_DATA:
		/* 
			The parent has requested the data of the child
		*/
		ProtocolsetParentData();
		commParent.commSetTxStatus(TRUE);
		commParent.Transmit(PARENT_ADDRESS);
		break;

	case CMD_SEND_ACK:
		/*
			Parent has requested an Acknowledgement. This means parent 
			is connected so we can safely set the COMM_ESTABLISHED_PARENT
			to TRUE.
		*/
		COMM_ESTABLISHED_PARENT = TRUE; 
		commParent.commWriteBuffer(CMD_FRAME_HEADER1);
		commParent.commWriteBuffer(CMD_FRAME_HEADER2);
		commParent.commWriteBuffer(CMD_ACK);
		commParent.commSetTxStatus(TRUE);
		commParent.Transmit(PARENT_ADDRESS);
		break;

	}

	/*
		Add response to more commnads as needed
	*/
}




