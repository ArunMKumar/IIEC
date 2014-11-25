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
#include "CycBuffer.h"
#include "Project.h"
#include "Command.h"
#include "Comm.h"

typedef struct{
	/* Data that needs to be retrieved from the child
	 * the same format of the data shall be sent to the
	 * parent too
	 */
	id_t ID;
	id_t PID;
	prio_t PRIO;
	prio_t DPRIO;
	load_t ASL;
	load_t DCL;
	load_t Dload;
}childData;


class Node{
  private:
      id_t ID;        	// ID of the node
	  id_t PID;			// ID of the parent
      prio_t PRIO;   	// Fixed priority of the connected loads
      //prio_t DPRIO;  	// Priority calculated at runtime so, no DPRIO
      load_t ASL;      	// Assigned loads of the connected loads and nodes
      load_t DCL;      	// Runtime load of the connected loads
      load_t DLoad;	 	// Demanded load
	  status_t Status;	// Current Status of the Load
	  Comm commParent;	// Communication with parent
	  Comm commChild;	// Communication with child

  public:
	  Node();
      Node(id_t ID, id_t PID);    // Where to read from answer where to act
      void nodePRIO();		// Calculate the Priority of the node
      void nodeLoadCalc();	//calculate all 3 loads
      void fillParentBuf();	// fill Parent Out buffer with data
      void fillChildBuf();	// fill Child Out buffer with data
      void TxParentBuf();	// Transmit the Parent buffer
      void TxChildBuf();	// Transmit the child buffer
      void Task();			// cyclic task for every node
};




#endif /* NODE_H_ */
