/*
Source file for the Project
Contains the task structure and the tasks that need to be completed.

Do all that you would do in the sketch here, then just use this call
in the sketch.

Arun M Kumar						30 Nov 2014
*/


#include "Project.h"
#include "Load.h"
#include "Node.h"
#include "Comm.h"


//====================================================================================
//							Load Data
//====================================================================================
/*
	First we need to initialize the loads.
	For the time being we use 4 loads and work with them

		Initializing the Loads instances here
*/
Load Load1(LOAD_0R, LOAD_0W, LOAD_ID0, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);		// A0,A1 etc. will work with Arduino IDE, ignore error here
Load Load2(LOAD_1R, LOAD_1W, LOAD_ID1, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load3(LOAD_2R, LOAD_2W, LOAD_ID2, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);
Load Load4(LOAD_3R, LOAD_3W, LOAD_ID3, LOAD_PRIO_DEFAULT, LOAD_CLASS_DEFAULT);

LoadState_t Loads[NUM_LOADS];

void fillLoadState(void){
	/*
		This fills the data from each load into a structure that can be used well by
		the node task, instead of calling load class member functions again and again
		this keeps the flow clean as it acts as a central holding are for data about
		all nodes and loads.
		Call this cyclically
	*/
	for (int i = 0; i < NUM_LOADS; i++){
		Load1.getLoadState(&Loads[i]);
	}
	
}

//====================================================================================
//							Node Data
//====================================================================================
/*
	child data structure to store the data
*/
childData_t childs[NUM_CHILDS]; // Change as per project

/*
	This array contains the I2C addresses of the childs that we need to ocmmunicate with
*/
addr_t childAddr[NUM_CHILDS] = { CHILD1_I2C_ADDR, CHILD2_I2C_ADDR };

/*
	Creating data structure for parent and child comm
*/
deviceAttrib_t parentDevice = {0x00, 000, 0x00};
deviceAttrib_t childDevice = { COMM_TYPE_I2C, 0x00, SRC_I2C_ADDRESS };


/*
Creating Node instance here
*/
Node thisNode(NODE_ID, NODE_PID, &childDevice, &parentDevice, childAddr);

status_t Node::nodeInit(void){
	/*
		This shall initialize all data structures and comm
		parameters for the node instance and also do the communication
		part too.
	*/

	for (int i = 0; i < NUM_CHILDS; i++){
		thisNode.TxChildByte(SEND_DATA, childAddr[i]); // ask every child to send data
	}

}

status_t Node::Task(void){
	/*
	This function shall be executed cyclically everytime.
	This shall perform the periodic tasks that needs to be done for the
	node, eg. Calculating the Priorities and the Load allowance.

	We shall perform the algorith here, but do need to remember that
	we should use modular functions to allow for improvements later.

	Tasks to be performed here are:
	Task 1: Get priority from child nodes and loads
	Task 2: calculate the values and decide which loads to switch off
	Task 3: Communicate the info back to parent
	*/

	//Task 1:




	return Status;

}


/*
Now lets create the basic functions Init and Task
*/

void Init(){
	/*
	Do what we normally keep for Setup function in the sketches
	*/
	thisNode.nodeCommInit();
}

void TaskMain(void){

}


