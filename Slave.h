/* header file for the loads and the function that it do
*/


#ifndef __SLAVE_H
#define __SLAVE_H

#include "Arduino.h"
#include "Protocol.h"
#include "Command.h"

typedef struct {
	/* Generic data struct to get the attributes of the current slave*/
	uint8_t ID;
	uint8_t MID;
	float PRIO;
	float DPRIO;
	uint8_t ASL;
	uint8_t DCL;
	uint8_t Status;
} dataset;


/* Generic class for the slaves,
contaims the attrivutes and the methods that
are ssociated with each slave device*/
class Slave{
  private:
      uint8_t _rpin;      // Pin on UNO where to read
      uint8_t _wpin;      // Pin on uno where to write
      uint8_t ID;        // ID of the slave
	  uint8_t MID;		// ID of the master
      float PRIO;   // Fixed priority of the connected loads 
      float DPRIO;  // Dynamic priority of the connected loads
      uint8_t ASL;      // Assigned loads of the connected loads
      uint8_t DCL;      // Runtime load of the connected loads
	  uint8_t Status;	// Current Status of the Load
	  PROTOCOL_BUF inBuf;		// Input message buffer for the slave  --- From Master
	  PROTOCOL_BUF outBuf;	// Output buffer for the slave --- To master

  public:
	  Slave();
      Slave(uint8_t rpin, uint8_t wpin, uint8_t ID);    // Where to read from ans where to act
      char read();        
      void write(uint8_t Logic);	// logic HIGH or LOW
	  uint8_t readSet(dataset* loc);

	  uint8_t TxOutBuf(void);	// transmit data over the I2C bus
};




#endif
