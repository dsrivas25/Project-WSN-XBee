/*
 * XbeeS2.h
 *
 * Created: 6/20/2013 1:29:15 PM
 *  Author: Waron
 */ 


#ifndef XBEE_H_
#define XBEE_H_

#define XBEES1

#include <stdio.h>
#include <stdlib.h>

#define DATA_MAX 80	// Maximum packet data size

#ifdef XBEES2
	typedef struct{
		int len;
		char api_identifier;
		long DH;
		long DL;
		int source_addr_16bit;
		char options;
		char frame_id;
		char AT_com[2];
		char status;
		int data_len;	// stores the length of the data
		char data[20];	// also stores the "value" for at command response	
		char checksum;
		} RxPacket;
#endif

#ifdef XBEES1
	typedef struct{
		int len;
		char api_identifier;
		long DH;
		long DL;
		int source_addr_16bit;
		char rssi_byte;
		char options;
		char frame_id;
		char AT_com[2];
		char status;
		char data[20];	// also stores the "value" for at command response
		int data_len;	// stores the length of the data
		char checksum;
	} RxPacket;
#endif

typedef struct {
	long sl;
	long sh;
}addr64;

// Public Functions
char getRSSI(void);
void setPANID(int);

/* XbeeInit()
 * ==========
 * Used to initialize Xbee settings and microcontroller USART configuration.
 * This function must be called before any others.
 */
int XbeeInit(void);

/* getPacket()
 * ===========
 * Returns the last received Xbee packet in the form of an RxPacket structure.
 */
RxPacket getPacket(void);

/* setNewPacketCB()
 * ================
 * This function sets another function to be called when a new packet arrives.
 * It utilizes the USART Rx interrupt defined in the XbeeHAL.h.
 */
void setNewPacketCB(void (*funptr)(void));

/* AT_Command()
 * ============
 * This function is used to send AT commands to the Xbee module. The AT command is passed as a string.
 */
void AT_Command(char, char, char, char*, int);

/* get16bitAddress()
 * =================
 * This function calls the MY AT command and waits until the response frame is 
 * received.
 */
int get16bitAddress(void);

/* get64bitAddress()
 * =================
 * This function calls the MY AT command and waits until the response frame is 
 * received.
 */
addr64 get64bitAddress(void);

#ifdef XBEES2	// Series 2 only commands

	/* Zigbee_TX_Request()
	 * ===================
	 * Used to create a Zigbee transmit request packet.
	 * See XBee documentation for parameter values.
	 */
	void ZigBee_TX_Request(char, long, long, int, char, char, char*, int);
	
#endif

#ifdef XBEES1	// Series 1 only commands

	void TX_Request_16bit(char, int, char, char*, int);
	void TX_Request_64bit(char, long, long, char, char*, int);
	void set16bitAddress(int);

#endif

#endif /* XBEE_H_ */
