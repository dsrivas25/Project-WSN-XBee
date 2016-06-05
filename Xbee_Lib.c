/*
 * Xbee_Lib.c
 *
 * Created: 7/11/2014 4:50:33 PM
 *  Author: Waron
 */ 

#include "Xbee.h"
#include <util/delay.h>


char test[] = {'T', 'E', 'S', 'T'};

void cb()
{
	//printf("Interrupt Received\n\r");
	//ZigBee_TX_Request(0x00, 0, 0x00FFFF, 0, 0x01, 0x01, test, 4);
	
	RxPacket rx_data = getPacket();
	// Echo packet back
	int i;
	char buff[rx_data.data_len];
	char temp;
	for(i=0;i<rx_data.data_len;i++)
	{
		temp = (rx_data.data[i]);
		//buff[i] = temp;
		buff[i] = temp;	// Cipher Code
	}
	TX_Request_16bit(0x01, rx_data.source_addr_16bit, 0, buff, rx_data.data_len);
	//ZigBee_TX_Request(0,0,0xFFFF,rx_data.source_addr_16bit, 1, 0, buff, rx_data.data_len);
	
}

int main(void)
{
	XbeeInit();
	setNewPacketCB(cb);
	//printf("Hello World\n");
	
	/*
	addr64 addr;
	addr = get64bitAddress();
	printf("64 bit address is: %lu %lu\n", addr.sh, addr.sl);
		addr = get64bitAddress();
	printf("64 bit address is: %lu %lu\n", addr.sh, addr.sl);
	*/
	
    while(1)
    { 
		//_delay_ms(4000);
		//ZigBee_TX_Request(0x00, 0, 0x00FFFF, 0, 0x01, 0x01, test, 4);
		//TX_Request_16bit(0,0xFFFF,0,test,4);
		
		get16bitAddress();
		_delay_ms(2000);
		set16bitAddress(6);
		_delay_ms(2000);
		get16bitAddress();
		_delay_ms(2000);
		get16bitAddress();
		_delay_ms(2000);
		set16bitAddress(13);
		_delay_ms(2000);
		get16bitAddress();
		_delay_ms(2000);
		AT_Command(0x00,'W','R',0,0);
		_delay_ms(2000);
		
		
    }
}
