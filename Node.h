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
	prio_t DPRIO;
	load_t ASL;
	load_t DCL;
	load_t Dload;
}childData;

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
      prio_t PRIO;   	// Fixed priority of the connected loads
	  uint8_t childAddr[NUMCHILD];	// Address of the child nodes
	  /*
		DPRIO is only meant for the Loads and not for the nodes
	  */
      //prio_t DPRIO;  	// Priority calculated at runtime so, no DPRIO
      load_t ASL;      	// Assigned loads of the connected loads and nodes
      load_t DCL;      	// Runtime load of the connected loads
      load_t DLoad;	 	// Demanded load
	  status_t Status;	// Current Status of the Load
	  

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

      void setNodePRIO(prio_t);			// Calculate the Priority of the node
	  void setNodeLoads(load_t, load_t, load_t);

	  void getLoadPrio(Load[]);			// get priority from the loads	
	  void setLoadPrio(Load[]);			// set priroity of the loads
	  void getLoadlimit(Load[]);			// get the load limit of the loads, all of them
	  void setLoadlimit(Load[]);			// set the load limit of the loads
	  void readLoads(Load[]);				//  Read the current rating of the loads

	  status_t commInitParent(deviceAttrib_t*);
	  status_t commInitChild(deviceAttrib_t*);

	  status_t getStatus(void);
      status_t TxParent();	// Transmit the Parent buffer
      status_t TxChild();	// Transmit the child buffer
      status_t Task(void);	// cyclic task for every node


	  
};




#endif /* NODE_H_ */
