/*
 * XbeeS2.c
 *
 * Created: 6/20/2013 1:29:02 PM
 *  Author: Waron
 */ 
#include "Xbee.h"

// Local Functions
void rxISR();
void receive_Msg(RxPacket*);
void send_Msg(char*, int);
void USART_vSendByte(char);
void XbeeUSART_init(void);

#include "XbeeHAL.h"
#include "XbeeConfig.h"

RxPacket rx_pkt;

// Global Variables
char RSSI;
int MY;
int cb;	// callback flag -- set if a callback function for new packets has been specified
void (*cbFunPtr)(void);	// callback function pointer

int XbeeInit()
{
	LED_OUTPUT();	// set LED pin to output
	XbeeUSART_init();	// call USART init function from XbeeHAL file
	XbeeSetup();	// call setup function from XbeeConfig file
	return 1;
}

/* Routine to call USART initialization routine from the HAL
 *
 * This routine configures the USART that the XBee is attached to.
 * Configues for settings 8N1 and 9600 baud.
 */
void XbeeUSART_init()
{
	USART_INIT();
}

/* Routine to send a byte through USART
 *
 * This routine polls the USART data buffer register full flag until it indicates it is ready
 * for a new byte to be transmitted, then loads the new byte into the USART data buffer
 * register for transmission.
 */
void USART_vSendByte(char Data)
{
	// Wait if a byte is being transmitted
	while (TX_BUFFER_IS_FULL()) {}; // Do nothing until UDR is ready for more data to be written to it
	// Transmit data
	XBEE_TDR = Data;
}

/* USART Receive Interrupt
 * 
 * Hardware interrupt routine inside the HAL calls this function. When a new byte is received, it is
 * checked for the start delimeter of a new packet. If it is, then the receive message function is called.
 * Otherwise, nothing happens. After a packet is received, the callback function is called to handle the
 * packet, if one has been configured.
 */
void rxISR()
{
	DIS_INT();
	TOGGLE_LED();
	if(XBEE_RDR == 0x7E)
	{
		RxPacket pkt;
		receive_Msg(&pkt);
		rx_pkt = pkt;
		// Call function for responding to new packet
		if(cb)
		(*cbFunPtr)();
	}
	
	TOGGLE_LED();
	EN_INT();
}

/* Send Message Function
 *
 * This function is passed a character array of an XBee API Packet, along with the
 * length of the packet. The checksum is calculated, then the start delimeter is transmitted,
 * followed by the length of the packet, then the data, and finally the checksum.
 */
void send_Msg(char *data, int len)
{
	//Generate checksum
	char checksum;
	int counter = 0, sum = 0;
	for(counter = 0; counter <= len - 1; counter++)
		sum += data[counter];
	//Checksum is calculated by adding the data values together, and subtracting the 
	//last 8 bits from 0xFF.
	checksum = 0xFF - (sum & 0x00FF); 
	//Transmit data
	USART_vSendByte(0x7E);  //Start delimiter
	USART_vSendByte(8 >> len);  //Length MSB
	USART_vSendByte(len);	//Length LSB
	for(counter = 0; counter <= len - 1; counter++)  //Transmit data
		USART_vSendByte(data[counter]);
	USART_vSendByte(checksum);  //Transmit checksum
}

void receive_Msg(RxPacket *rx_data)
{
	int count;
	char temp;
	rx_data->data_len = 0;
	
	while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
	temp = XBEE_RDR;	//next incoming byte is the MSB of the data size
	while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR

	rx_data->len = (temp << 8) | XBEE_RDR;	//merge LSB and MSB to obtain data length
	while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
	rx_data->api_identifier = XBEE_RDR;
	
	switch(rx_data->api_identifier)	// Select proper sequence for receiving various packet types
	{
		#ifdef XBEES1
		case 0x81:	// RX (Receive) Packet: 16-bit Address	(Series 1 only)
			for(count = 1; count < rx_data->len; count++)
			{
				while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
				if(count == 1)
				rx_data->source_addr_16bit = (XBEE_RDR << 8);
				else if(count == 2)
				rx_data->source_addr_16bit |= XBEE_RDR;
				else if(count == 3)
				rx_data->rssi_byte = XBEE_RDR;
				else if(count == 4)
				rx_data->options = XBEE_RDR;
				else
				{
					rx_data->data[count - 5] = XBEE_RDR;
					rx_data->data_len++;
				}
			}
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum
			break;
		case 0x82:	// RX (Receive) Packet: 64-bit Address IO (Series 1 only)
			for(count = 1; count < rx_data->len; count++)
			{
				while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
				if(count == 1)
				rx_data->DH = ((long)XBEE_RDR << 24);
				else if(count == 2)
				rx_data->DH |= ((long)XBEE_RDR << 16);
				else if(count == 3)
				rx_data->DH |= ((long)XBEE_RDR << 8);
				else if(count == 4)
				rx_data->DH |= (long)XBEE_RDR;
				else if(count == 5)
				rx_data->DL = ((long)XBEE_RDR << 24);
				else if(count == 6)
				rx_data->DL |= ((long)XBEE_RDR << 16);
				else if(count == 7)
				rx_data->DL |= ((long)XBEE_RDR << 8);
				else if(count == 8)
				rx_data->DL |= (long)XBEE_RDR;
				else if(count == 9)
				rx_data->rssi_byte = XBEE_RDR;
				else if(count == 10)
				rx_data->options = XBEE_RDR;
				else
				{
					rx_data->data[count - 11] = XBEE_RDR;
					rx_data->data_len++;
				}
			}
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum
			break;
		#endif
		case 0x88:	// AT Command
			for(count = 1; count < rx_data->len; count++)
			{
				while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
				if(count == 1)
					rx_data->frame_id = XBEE_RDR;
				else if(count == 2)
					rx_data->AT_com[0] = XBEE_RDR;
				else if(count == 3)
					rx_data->AT_com[1] = XBEE_RDR;
				else if(count == 4)
					rx_data->status = XBEE_RDR;
				else
				{
					rx_data->data[count - 5] = XBEE_RDR;
					rx_data->data_len++;
				}
			}
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum			
			break;
		case 0x8A:	// Modem Status
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->data[0] = XBEE_RDR;
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum
			break;
		#ifdef XBEES2
		case 0x90:	// Zigbee Receive Packet (Series 2 only)
			for(count = 1; count < rx_data->len; count++)
			{
				while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
				if(count == 1)
					rx_data->DH = ((long)XBEE_RDR << 24);
				else if(count == 2)
					rx_data->DH |= ((long)XBEE_RDR << 16);
				else if(count == 3)
					rx_data->DH |= ((long)XBEE_RDR << 8);
				else if(count == 4)
					rx_data->DH |= (long)XBEE_RDR;
				else if(count == 5)
					rx_data->DL = ((long)XBEE_RDR << 24);
				else if(count == 6)
					rx_data->DL |= ((long)XBEE_RDR << 16);
				else if(count == 7)
					rx_data->DL |= ((long)XBEE_RDR << 8);
				else if(count == 8)
					rx_data->DL |= (long)XBEE_RDR;
				else if(count == 9)
					rx_data->source_addr_16bit = (int)(XBEE_RDR << 8);
				else if(count == 10)
					rx_data->source_addr_16bit = (int)XBEE_RDR;
				else if(count == 11)
					rx_data->options = XBEE_RDR;
				else
				{
					rx_data->data[count - 12] = XBEE_RDR;
					rx_data->data_len++;
				}				
			}
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum
			break;
		#endif
		default:	// Catch unrecognized packet type
			for(count = 1; count < rx_data->len; count++)
			{
				while (RX_BUFFER_IS_FULL()) {};
			}
			while (RX_BUFFER_IS_FULL()) {}; // Do nothing until data have been received and is ready to be read from UDR
			rx_data->checksum = XBEE_RDR;	//store checksum
			break;
	}
	
}

void AT_Command(char frameid, char command1, char command2, char *options, int len)
{
	char buff[5]; //temporary buffer for transmitting
	int count;
	buff[0] = 0x08;	// API ID for AT Commands
	buff[1] = frameid;	// Frame ID; set to 0 for no response
	buff[2] = command1;
	buff[3] = command2;
	for(count = 1; count <= len; count++)
		buff[3 + count] = options[count - 1];
	send_Msg(buff, 4 + len);
}

void setPANID(int id)
{
	DIS_INT();
	char data[] = {(char)(id>>8), (char)id};	
	int temp;
	//do 
	//{
		AT_Command(0x00, 'I', 'D', data, 2);	// Send MY AT Command
	/*	while (RX_BUFFER_IS_FULL()){};	
		temp = XBEE_RDR;
		if(temp == 0x7E)
			receive_Msg(&rx_pkt);
	} while (rx_pkt.api_identifier != 0x88);	// Catch Reply
	*/			
	#ifdef DEBUG
		printf("Setting ID to %d...\n", id);
	#endif
	EN_INT();
}

/* Function to get the RSSI value of the last received message in dB
 *
 * This function calls the DB AT command. It then waits for the returning packet.
 * if the packet is not the returned DB value, then it is discarded.
 * The returned value is the attenuation of the signal in -dB.
 */
char getRSSI(void)
{
	DIS_INT();
	RxPacket pkt;
	int temp;

	AT_Command(0x01, 'D', 'B', 0, 0);	// Send DB AT Command
	while (RX_BUFFER_IS_FULL()){};	
	temp = XBEE_RDR;	// Probably should add some code to check for start delimeter
	receive_Msg(&pkt);

	if(pkt.api_identifier != 0x88)	
	{
		#ifdef DEBUG
			printf("Failed to retrieve RSSI\n");
		#endif
		// otherwise, handle the packet as usual
		if(cb)
			(*cbFunPtr)();
		EN_INT();
		return 0xFF;
	}	
	else
	{
		#ifdef DEBUG
			printf("RSSI is -%u dB\n", pkt.data[0]);
		#endif
		EN_INT();
		return pkt.data[0];	// Return RSSI value		
	}	

}

/* Callback function for new packets
 *
 * The user passes the name of their designated callback function. The function's address is
 * then set to the callback fuction pointer, cbFunPtr. The callback flag, cb, is set.
 */
void setNewPacketCB(void (*funptr)())
{
	cb = 1;
	cbFunPtr = funptr;
}

/* Get Packet
 *
 * Returns the last received packet.
 */
RxPacket getPacket()
{
	return rx_pkt;
}

/* Function to return the 16 bit Address of the Xbee
 *
 * This function calls the MY AT command and waits until the response frame is 
 * received.
 */
int get16bitAddress()
{
	DIS_INT();
	RxPacket pkt;	
	int temp;
	
	AT_Command(0x01, 'M', 'Y', 0, 0);	// Send DB AT Command
	while (RX_BUFFER_IS_FULL()){};	
	temp = XBEE_RDR;	// Probably should add some code to check for start delimeter
	receive_Msg(&pkt);

	if(pkt.api_identifier != 0x88)	
	{
		#ifdef DEBUG
			printf("Failed to retrieve MY\n");
		#endif
		// otherwise, handle the packet as usual
		if(cb)
			(*cbFunPtr)();
		EN_INT();
		return 0xFFFF;
	}	
	else
	{
		#ifdef DEBUG2
			printf("MY is %u\n", (pkt.data[0]<<8)|pkt.data[1]);
		#endif
		EN_INT();
		return (int)((pkt.data[0]<<8)|pkt.data[1]);	// Return MY		
	}
  /*
	DIS_INT();
	RxPacket pkt;	
	int temp;
	int addr;
	do 
	{
		AT_Command(0x01, 'M', 'Y', 0, 0);	// Send DB AT Command
		while (RX_BUFFER_IS_FULL()){};	
		temp = XBEE_UDR;
		if(temp == 0x7E)
			receive_Msg(&pkt);
	} while (pkt.api_identifier != 0x88);
				
	#ifdef DEBUG			
		printf("MY is %d\n", (pkt.data[0]<<8)|pkt.data[1]);
	#endif
	addr = (int)((pkt.data[0]<<8)|pkt.data[1]);
	EN_INT();
	return addr;	// Return MY
	*/
}

addr64 get64bitAddress()
{
	DIS_INT();
	long SH = 0;
	long SL = 0;
	RxPacket pkt;
	int temp;

	do
	{
		AT_Command(0x01, 'S', 'H', 0, 0);	// Send SH AT Command
		while (RX_BUFFER_IS_FULL()){};
		temp = XBEE_RDR;
		receive_Msg(&pkt);
	} while (pkt.api_identifier != 0x88);	// Waiting for response packet
	SH |= ((long)pkt.data[0]<< 24);
	SH |= ((long)pkt.data[1]<< 16);
	SH |= ((long)pkt.data[2]<< 8);
	SH |= ((long)pkt.data[3]);

	/* SH has the higher 32 bit address*/
	#ifdef DEBUG
	printf("\nSH is %lx\n", SH);
	#endif
	
	do
	{
		AT_Command(0x01, 'S', 'L', 0, 0);	// Send SL AT Command
		
		while (RX_BUFFER_IS_FULL()){};
		temp = XBEE_RDR;
		receive_Msg(&pkt);
	} while (pkt.api_identifier != 0x88);	// Waiting for response packet
	SL |= ((long)pkt.data[0]<< 24);
	SL |= ((long)pkt.data[1]<< 16);
	SL |= ((long)pkt.data[2]<< 8);
	SL |= ((long)pkt.data[3]);
	/* SL has the higher 32 bit address*/

	#ifdef DEBUG
	printf("\nSL is %lx\n", SL);
	#endif
	
	addr64 address_64;
	address_64.sh = SH;
	address_64.sl = SL;

	EN_INT();
	return address_64; // Return 64 bit address structure adr664
}

// XBee Series 2 only functions
#ifdef XBEES2

void ZigBee_TX_Request(char Frame_ID, long DH, long DL, int _16bitAddr, char Hops, char Options, char *RF_Data, int len )
{
	int i; // counting variable
	char buff[14 + len];	//temporary buffer for transmitting
	// ZigBee Transmit Request API Identifier
	buff[0] = 0x10;
	// Identifies the UART data frame for the host to correlate with a 
	// subsequent ACK (acknowledgment). Setting Frame ID to ‘0' will disable response frame.
	buff[1] = Frame_ID;	
	// MSB first, LSB last. Broadcast = 0x000000000000FFFF
	buff[2] = (DH >> 24);
	buff[3] = (DH >> 16);
	buff[4] = (DH >> 8);
	buff[5] = DH;
	buff[6] = (DL >> 24);
	buff[7] = (DL >> 16);
	buff[8] = (DL >> 8);
	buff[9] = DL;
	// 16 bit address
	buff[10] = (_16bitAddr >> 8);
	buff[11] = _16bitAddr;
	// Number of hops for message to take
	buff[12] = Hops;
	// Options
	buff[13] = Options;
	for(i = 0; i < len; i++)
		buff[14+i] = RF_Data[i];
	send_Msg(buff, 14+len);	
}
#endif

// XBee Series 1 only functions
#ifdef XBEES1

void TX_Request_16bit(char frameID, int addr, char options, char *data, int len)
{
	int i; // counting variable
	//char buff[5 + len];	//temporary buffer for transmitting
	char buff[5 + DATA_MAX];
	// Transmit Request 16-bit API Identifier
	buff[0] = 0x01;
	// Identifies the UART data frame for the host to correlate with a
	// subsequent ACK (acknowledgment). Setting Frame ID to ?0' will disable response frame.
	buff[1] = frameID;
	// MSB first, LSB last.
	buff[2] = (addr >> 8);
	buff[3] = addr;
	// Options
	buff[4] = options;
	for(i = 0; i < len; i++)
		buff[5+i] = data[i];
	send_Msg(buff, 5+len);
}

void TX_Request_64bit(char frameID, long DH, long DL, char options, char *data, int len)
{
	int i; // counting variable
	//char buff[11 + len];	//temporary buffer for transmitting
	char buff[11 + DATA_MAX];
	// Transmit Request 16-bit API Identifier
	buff[0] = 0x01;
	// Identifies the UART data frame for the host to correlate with a
	// subsequent ACK (acknowledgment). Setting Frame ID to ?0' will disable response frame.
	buff[1] = frameID;
	// MSB first, LSB last.
	buff[2] = (DH >> 24);
	buff[3] = (DH >> 16);
	buff[4] = (DH >> 8);
	buff[5] = DH;
	buff[6] = (DL >> 24);
	buff[7] = (DL >> 16);
	buff[8] = (DL >> 8);
	buff[9] = DL;
	// Options
	buff[10] = options;
	for(i = 0; i < len; i++)
	buff[11+i] = data[i];
	send_Msg(buff, 5+len);
}

/* Function to set the 16 bit Address of the Xbee
 *
 * This function calls the MY AT command and waits until the response frame is 
 * received.
 */
void set16bitAddress(int addr)
{
	DIS_INT();
	char data[] = {(char)(addr>>8), (char)addr};	
	int temp = addr;
	#ifdef DEBUG
		printf("Setting MY to %u...\n", addr);
	#endif
	AT_Command(0x00, 'M', 'Y', data, 2);	// Send MY AT Command
	EN_INT();
}
#endif
