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

void Node::nodeSetChildAddr(addr_t childAddr[]){
	/*
		Sets the address of the child 
	*/

	for (int i = 0; i < NUM_CHILDS; i++){
		this->childAddr[i] = childAddr[i];
	}
}

status_t Node::nodeInitChild(deviceAttrib_t* data){
	
	return commChild.commSetDevice(data);
}

status_t Node::nodeInitParent(deviceAttrib_t* data){

	return commParent.commSetDevice(data);
}

void Node::nodeSetChildAddr(uint8_t addr[NUM_CHILDS]){
	/*
		This methods sets the addresses of the childs with which
		we need to communciate
	*/

	for (int i = 0; i < NUM_CHILDS; i++){
		childAddr[i] = addr[i];
	}

}

status_t Node::nodeCommInit(deviceAttrib_t* childComm, deviceAttrib_t* parentComm){
	/*
		Initializes the comm module for the In and out device
	*/
	commInitChild(childComm);
	commInitChild(parentComm);
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

void Node::readChilds(childData_t childs[]){
	/*
	This method will ping each child module to  send its data 
	and then read it from the in buffer to updat the values
	*/
	
}

status_t Node::TxParentByte(uint8_t data){
	
	/*
		No issuess in the current project as both
		Parent and child nodes are in different comm instace
		so we can safely use one particular instance for this 
		task.
	*/

	commParent.commWriteBuffer(data);
	commParent.commSetTxStatus(TRUE);	// Set to false after transmitting

	commParent.Transmit(PARENT_ADDRESS);
	commParent.commSetTxStatus(FALSE);

	return Status;
}

status_t Node::TxChildByte(uint8_t data, uint8_t addr){

	/*
	No issuess in the current project as both
	Parent and child nodes are in different comm instace
	so we can safely use one particular instance for this
	task.
	*/

	commChild.commWriteBuffer(data);
	commChild.commSetTxStatus(TRUE);

	commChild.Transmit(addr);
	commChild.commSetTxStatus(FALSE);

	return Status;
}





