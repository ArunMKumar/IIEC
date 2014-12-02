/*
 * Node.h
 * Header file listing the class Node and the
 * associated attributes and methods
 *  Created on: Nov 25, 2014
 *      Author: kumaar6
 */

#ifndef __NODE_H_
#define __NODE_H_

#include "Arduino.h"
#include "Load.h"
#include "CycBuffer.h"
#include "Project.h"
#include "Command.h"
#include "Comm.h"

typedef struct{
	/* Data that needs to be retrieved from the child
	 * the same format of the data shall be sent to the
	 * parent too. It helps in sending the appropriate set
	 * of data.
	 */
	id_t ID;
	id_t PID;
	prio_t PRIO;
	load_t ASL;
	load_t DCL;
	load_t DL;
}childData_t;

//====================================================================================
//							NODE CLASS
//====================================================================================
/*
 * The purpose of this class is to contain the attributes and methods associated with a given load
 * This class shall contain the communication instances and the methods to extract meaningfull
 * data from the buffers.
 */
class Node{
  private:
      id_t ID;        	// ID of the node
	  id_t PID;			// ID of the parent
      prio_t PRIO;   	// dynamic priority of the connected loads
	  uint8_t childAddr[NUM_CHILDS];	// Address of the child nodes
	  /*
		DPRIO is only meant for the Loads and not for the nodes
	  */
      //prio_t DPRIO;  	// Priority calculated at runtime so, no DPRIO
      load_t ASL;      	// Assigned loads of the connected loads and nodes
      load_t DCL;      	// Runtime load of the connected loads
      load_t DL;	 	// Demanded load
	  status_t Status;	// Current Status of the Load


	  void ProtocolreadChildData(childData_t[], uint8_t);
	  void ProtocolsetChildData(void);
	  void ProtocolsetParentData(void);
	  

  public:
	  /*
		New Implementation, Communication based task are independent of the node
		No need to associate Comm instances with the Node as their will only be only 
		one node so only 2 instances of communication shall be implemented,
		one for the parent and the other for the child.
	  */
	  Comm commParent;	// Communication with parent
	  Comm commChild;	// Communication with child

	  Node();
      Node(id_t, id_t);   // Where to read from and where to act
	  Node(id_t, id_t, deviceAttrib_t*, deviceAttrib_t*, addr_t[]);

      void setNodePRIO(LoadState_t[], childData_t[]);			// Calculate the Priority of the node
	  void setNodeLoadLimit(LoadState_t[], childData_t[]);	// Read all demanded loads and load limit
	
	  status_t nodeInitParent(deviceAttrib_t*);
	  status_t nodeInitChild(deviceAttrib_t*);
	  status_t nodeCommInit(deviceAttrib_t*, deviceAttrib_t*);
	  status_t nodeSetChildAddr(uint8_t[]);

	  status_t nodeInit(void);		// external definition
	  status_t getStatus(void);

	  /*
		These four methods shall do all communication for a given node.
		The buffer is read and is written to. Physical level details are 
		handled by the Comm instance.
	  */
	  status_t ProtocolReadChild(childData_t[]);					// read data from child(s)
	  void ProtocolReadChildData(childData_t[], uint8_t);			// read data for a specific child
	  status_t ProtocolReadParent();								// read command and data from parent
	  status_t ProtocolWriteChild(uint8_t[], uint8_t, uint8_t);		// Write data to the child
	  status_t ProtocolWriteParent();								// write data to parent
	  void ProtocolHandleParentCmd(uint8_t);						// Handles the command received from the parent.
	  void ProtocolReqChildData(void);								// Request data from the child nodes
	  void ProtocolAssignLoads(void);								// Assigns the loads to the children
	 // void ProtocolHandleChildData(uint8_t); Currently not required, let it be for now
	 
	

	  status_t establishCommChild();		//establish communication with child nodes
	  status_t establishCommParent();		// establish communication with parent node
};

#endif /* NODE_H_ */
