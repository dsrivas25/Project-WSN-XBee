 /*
 * XbeeConfig.h
 *
 * Created: 7/11/2014 4:55:59 PM
 *  Author: Waron
 */ 


#ifndef XBEECONFIG_H_
#define XBEECONFIG_H_
#include "Xbee.h"

//#define XBEES2

#ifdef XBEES1
/***************** Networking & Security********************/
	
	#define CH C /* Set/read the channel number (Uses 802.15.4 channel numbers) */
	#define ID 1234 /* Set the PAN(Personal Aread Network) ID. Set ID = 0xFFFF to send message to all PANs */
	#define DH 0x0000 /* Range: 0x0 to 0xFFFFFFFF */
	#define DL 0xFFFF  /* Lower bits set to FFFF to broadcast for PAN */
	#define MY D /* Set/read 16-bit source address of the modem */
	#define CE 0 /* Set/Read the coordinator setting: 0-End Device, 1-Coordinator.*/
	#define RR 0 /* Set the number of retries the modem will execute in addition to the 3 retries provided by the
	              * 802.15.4 MAC. For each XBee entry, 802.15.4 MAC can execute upto 3 retries */
	#define RN 0 /* Set/read the minimum value of the back-off exponent in the CSMA-CA algorithm that is used for 
	            * collision avoidance. If RN=0, collision avoidance is disabled for the first iteration of the algorithm */
	#define NT 19 /* Set /read Node Discover Time register. This sets the maximum time for the Node Discover command 
	               * Range: 0x1-0xFC(Default: 19)*/
	#define NO 0 /* Enable node discover self-response. Range: 0x0 - 0x1(Default: 0) */
	#define SC 1FFE /* Read/set list of channels to scan for Active and Energy scans as bitfield.
	                 * Range: 0x0-0xFFFF(Default: 1FFE) */
	#define SD 4 /* Set the Scan duration exponent. Set End device SD=BE of beaconing coordinator. Scan time= N*(2^SD)*15.36ms.*/
	
/********************* RF Interfacing************************/

	#define PL 0 /*	Select/Read transmitter output power 
	              * Default: 4(Highest) */
	#define CA 2C /* Set the Clear Channel Assessment(CCA) threshold. If the modem detects energy above the CCA threshold, 
	               * it will not transmit. Unit: -dBm */
	
/************************ Sleep Modes (NonBeacon)***************/	

	#define ST 1388 /* Set the time period of inactivity before activating Sleep Mode. This parameter is used only with the Cyclic 
	            * Sleep settings(SM=4-5). */
	#define SP 0 /* Set Cyclic sleep period for cyclic sleeping remotes. Coordinator will discard indirect messages after a period of 2.5*SP, 
                  * set Coordinator SP=0 to send direct messages. Maximum sleep period: 268 seconds. Range: 0x0-0x68B0*/
	#define DP 3E8 /* Set sleep period for sleeping remotes that are configured for association but that are not associated to 
	                * a Coordinator. Range: 0x1-0x68B0 (Default: 3E8) */
	
	#define SO 0 /* Set sleep options. Bit field options include:
	              * 0x01- Enables/Disables sending a wakeup poll request on devices configured for cyclic sleep sampling.
				  * 0x02- Suppresses sending ADC/DIO samples when waking form cyclic sleep.
				  * All other options bit should be set to 0 */

/*********************** Serial Interfacing ********************/

	#define RO 3 /* Set the number of character times of inter-character delay required before transmission begins. Set to 0 to transmit characters 
                  * as they arrive instead of buffering them into one RF packet. Range: 0x0- 0xFF */
	#define AP 1 /* Enable : 1
	              * Disable : 0 */
	#define BD 9600 /* Set Baud rate for communication between modem serial port and host */
	#define NB 0 /* Configure Parity for the UART 
	               * No Parity:0 Even Parity:1 Odd Parity:2 Mark Parity:3 Space Parity:4 */

/************************ I/O Settings ******************************/
	
	#define PR FF /* Set bitfield to configure internal pull-up resistors status for I/O lines.
	               * 1= internal pull-up enabled
				   * 0= no internal pull-up  
				   * Range: 0x0- 0xFF
				   * Bitfield map: Bit 7-DIN(P3), Bit 6-DI8/SLEEP_RQ(P9), Bit 5-DIO6/RTS(P16), Bit 4-DIO0(P20), Bit 3-DIO1(P19), 
				   * Bit 2-DIO2(P18), Bit 1-DIO3(P17), Bit 0-DIO4(P11). */
	#define IU 1 /* Enables I/O data received to be sent out UART. The data is sent using an API frame regardless of the current ATAP mode. Default: 1 */
	#define IT 1 /* Set number of samples to collect before transmission. The maximum number of samples is dependent on the number of enabled I/O lines.
	              * Range: 0x1-0xFF (Default: 1). */
	#define IC 0 /* Set values for change detect monitoring. Each bit enables monitoring of DIO0-DIO7 for changes. If detected, data is transmitted 
	              * with DIO data only. Any samples queued waiting for transmission will be sent first.
				  * Range: 0x0-0xFF (Default: 0) */
	#define IR 0 /* Set sample rate. When set, this parameter causes the modem to sample all enabled DIO and ADC at a specified interval. 
	              * Range: 0x0-0xFFFF (Default: 0)*/
	#define PO 1 /* Select/Read function for PWM0. Disabled:0 RSSI:1 PWM Output:2 */
	#define P1 0 /* Select/Read function for PWM1. Disabled:0 RSSI:1 PWM Output:2 */
	#define PT FF /* Set output timeout value for both PWM outputs. Range: 0x0-0xFF(Default:FF)*/
	#define RP 28 /*Set PWM time register. Set duration of PWM signal output on the RSSI pin(P6).
                  * Range: 0x0-0xFF (Default:28) */

/********************************* I/O Line Passing**********************************/

	#define IA FFFFFFFFFFFFFFFF /* Set/read addresses of module to which outputs are bound. Range: 0-16 hexadecimal characters. */
	#define T0 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when 
	               * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T1 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T2 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T3 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T4 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T5 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T6 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	#define T7 FF /* Set/read output timeout value. When output is set, due to I/O line passing to a non-default level a timer is started which when
				   * expired will set output to its default level. Range: 0x0-0xFF(Default:FF)*/
	
	
/************************************ Diagnoistics****************************/

	#define DD 10000 /* Read the device type identifier value. Range: 0x0= 0xFFFFFFFF*/


/**************************************	AT Command Options*************************************/

	#define CT 64 /* Set command mode timeout parameter. If no valid commands have been received 
                   * within this time period, modem returns to Idle Mode from AT Command Mode.
				   * Range: 0x2-0x1770(Deafult:64) */
	#define GT 3E8 /* Set required period of silence before, after and between the Command Mode Characters 
	                * of the Command Mode Sequence (GT + CC + GT). The period of silence is used to prevent inadvertent entrance into AT Command Mode.*/
					* Range: 0x2-0xCE4(Default:3E8)*/
	#define CC 2B /* Set/read character value to be used to break from data mode to command mode. The default value <2Bh> is the ASCII code for the plus ('+') character.
	                * Range: 0x0-0xFF(Default: 2B). */
	
	#define 
	



#endif


#ifdef XBEES2

/**************************************** Networking ******************************************/

	#define ID 1234 /* Set the PAN (Personal Area Network) ID the device should join. 
	                 * Range: 0 - 0xFFFFFFFFFFFFFFFF 
					 * Set ID=0 (default) for the device to join any PAN ID. */
	#define SC FFFF /* Set/read list of channels to scan (active and energy scans) when forming a PAN as bitfield. Scans are initiated during coordinator
	                 * startup: Bit 15 = Chan 0x1A . . . Bit 0 = Chan 0x0B
					 * Range: 0x1-0xFFFF (Default:FFFF) */
	#define SD 3 /* Set/read the Scan Duration exponent. The exponent configures the duration of the active scan (PAN scan) on each channel in the SC 
				  *	channel mask when attempting to join a PAN. Scan Time = SC * (2 ^ SD) * 15.36ms. (SC=# channels) */
				  * Range: 0x0-0x07(Default:3) */
	#define ZS 0 /* Set/read the ZigBee stack profile setting. 0=Network Specific, 1=ZigBee-2006, 2=ZigBee-PRO
				  * Range: 0x0-0x2(Default:0) */
	#define NJ FF /* Set/read the Node Join time. The value of NJ determines the time (in seconds) that the device will allow other devices to join to it. 
	               * If set to 0xFF, the device will always allow joining.
				   * Range: 0x0-0xFF(Default:FF) */
	#define NW 0 /* Set/read the network watchdog timeout. If set to a non-zero value, the network watchdog timer is enabled on a router. The router will leave 
	              * the network if is does not receive valid communication within (3 * NW) minutes. The timer is reset each time data is received from or sent to a coordinator, 
				  * or if a many-to-one broadcast is received.
				  * Range: 0x0-0x64FF(Default:0) */
	#define  JV 1 /* Set the channel verification setting. If enabled, a router will verify a coordinator exists on the same channel after joining or power cycling to 
	               * ensure it is operating on a valid channel, and will leave if a coordinator cannot be found (if NJ=0xFF). If disabled, the router will remain on the same channel 
				   * through power cycles. Default: 0 */
	#define JN 0 /* Set the join notification setting. If enabled, the module will transmit a broadcast node identification frame on power up and when joining. 
	              * This action blinks the Assoc LED rapidly on all devices that receive the data, and sends an API frame out the UART of API devices. This function should be disabled 
				  * for large networks. Default: 0 */
	
/************************************************** Addressing *************************************************************/

	#define DH 0 /* Set the upper 32 bits of the 64 bit destination extended address. 0x000000000000FFFF is the broadcast address for the PAN. 0x0000000000000000 can be used 
				  * to address the Pan Coordinator.	
				  * Range: 0x0-0xFFFFFFFF(Default:0) */
	#define DL 0 /* Set the lower 32 bits of the 64 bit destination extended address. 0x000000000000FFFF is the broadcast address for the PAN. 0x0000000000000000 can be used to 
	              * address the Pan Coordinator.
				  * Range: 0x0-0xFFFFFFFF(Default:0) */
	#define NI 0 /* Set Node Identifier string. 0-20 ASCII characters. Default: '' */	              
	#define NH 1E /* Set the maximum hops limit. This limit sets the maximum number of broadcast hops (BH) and determines the unicast timeout (unicast timeout = (50 * NH) + 100). 
	               * A unicast timeout of 1.6 seconds (NH=30) is enough time for the data and acknowledgment to traverse about 8 hops.
				   * Range:0x0-0xFF(Default:1E) */
	#define BH 0 /* Set the transmission radius for broadcast data transmissions. Set to 0 for maximum radius.*/
				  * Range:0x0-0x1E(Default:0) */
	#define AR FF /* Set/read the time between aggregation route broadcast times. An aggregation route broadcast creates a route on all devices in the network back to the device 
	               * that sends the aggregation broadcast. Setting AR to 0xFF disables aggregation route broadcasting. Setting AR to 0 sends one broadcast.
				   * Range:0x0-0xFF(Default:FF) */
	#define DD 30000 /* Set the device type identifier value. This can be used to differentiate multiple XBee-based products.
	                  * Range:0x0-0xFFFFFFFF(Default:30000) */
	#define NT 3C /* Set Node Discovery backoff register. This sets the maximum delay for Node Discovery responses to be sent (ND, DN).
	               * Range:0x20-0xFF(Default:3C) */
	#define NO 0 /* Sets the node discovery options register. Options include 0x01 - Append DD value to end of node discovery, 0x02 - Return devices own ND response first.
                  * Range:0x0-0x3(Default:0) */
	#define CR 3 /* Set/read threshold for the number of PAN id conflict reports that must be received by the network manager within one minute to trigger a PAN id change.
                  * Range:0x1-0x3F(Default:3) */
	
	
/************************************************** RF Interfacing ******************************************************/

	#define PL 4 /* Select/Read transmitter output power. Power levels relative to PP: 0=-10dB, 1=-6dB, 2=-4dB, 3=-2dB, 4=0dB. Default: 4 */
	#define PM 1 /* Select/Read module boost mode setting. If enabled, boost mode improves sensitivity by 1dB and increases output power by 2dB, improving 
	              * the link margin and range. Default: 1 */
	

/*********************************************** Security ****************************************************************/

	#define EE 0 /* Enable or disable ZigBee encryption. Default:0 */
	#define EO 0 /* Set the ZigBee Encryption options: Bit0 = Acquire / Transmit network security key unencrypted during joining.
	              * Range: 0x0-0x1(Default: 0) */	
	#define KY 0 /* Sets key used for encryption and decryption (ZigBee trust center link key). This register can not be read. 0-32 hexadecimal characters. Default:'' */
	
/********************************************* Serial Interfacing **********************************************************/

	#define BD 9600 /* Set Baud rate for communication between modem serial port and host */
	#define NB 0 /* Configure Parity for the UART 
	               * No Parity:0 Even Parity:1 Odd Parity:2 Mark Parity:3 Space Parity:4 */
	#define SB 0 /* Configure the number of stop bits for the UART. This setting is only valid for no parity, even parity, or odd parity. */
	#define D7 1 /* Configure options for the DIO7 line of the module. Options include: CTS flow control, Digital Input and Output, or RS-485 enable control. */
	#define D6 0 /* Configure options for the DIO6 line of the module. Options include: RTS flow control, and Digital Input and Output. */
	#define AP 1 /* Enables API mode. 
			      * Range: 0x1-0x2 */
	#define AO 0 /* Set the API output mode register value. 0 - Received Data formatted as native API frame format. 1 - Received RF data formatted as Explicit Rx-Indicator. 
	              * 3 - Same as 1, plus received ZDO requests are passed out the UART. */
	

/************************************************** Sleep Modes ****************************************************************/	
	
	#define SM 0 /* Set/read sleep mode: Pin Hibernate is lowest power, Cyclic Sleep wakes on timer expiration, Cyclic Sleep Pin-Wake wakes on timer expiration or when 
	              * Sleep_Rq (module pin 9) transitions from a high to a low state. If SM is set to 0, the XBee is a router, otherwise it is an end device. */
	#define SN 1 /* Set/read the number of cyclic sleep periods used to calculate end device poll timeout. If an end device does not send a poll request to its parent coordinator
	              * or router within the poll timeout, the end device is removed from the child table. The poll timeout is calculated in milliseconds as (3 * SN * (SP * 10ms)), 
				  * minimum of 5 seconds. i.e. if SN=15, SP=0x64, the timeout is 45 seconds. 
	              * Range: 0x1-0xFFFF */
	#define SO 0 /* Set/read sleep options. Bitfield options include: 0x02 - Wake for ST time on each cyclic wake (after sleeping for SN sleep periods), 0x04 - Enable extended cyclic 
	              * sleep (sleep for entire SN*SP time - possible data loss). All other option bits should be set to 0.
				  * Range: 0x1-0xFF */
	#define SP 20 /* Set/read Cyclic sleep period for cyclic sleeping remotes. Set SP on parent (Coordinator) to match the largest SP of its end device children. On a router or coordinator, 
	               * SP determines the transmission timeout when sending to a sleeping end device. SP also determines how long the parent will buffer a message for a sleeping child.
                   * Range: 0x20-0xAF0 (Default:20) */
	#define ST 1388 /* Set/read time period of inactivity (no serial or RF data is sent or received) before activating Sleep Mode. The ST parameter is used only with Cyclic Sleep settings (SM=4-5).
	                 * Range: 0x1-0xFFFE (Default:1388) */
	#define PO 0 /* Set/read the poll rate in 10 msec units when set as a sleepy end device. Setting this to 0 (default) enables polling at 100ms (default rate). Adaptive polling may allow the end device 
	              * to poll more rapidly for a short time when receiving RF data.
	              * Range: 0x0-0x3E8 (Default:0) */
	
	
/******************************************************* I/O Settings ******************************************************************/

	#define D0 1 /* Configure options for the AD0/DIO0 line of the module. Options include: Enabling commissioning button functionality[1], Analog to Digital converter[2],Digital Input[3], Digital Output, Low[4] 
	              * and Digital Output, High[5]. Default: 1 */
	#define D1 0 /* Configure options for the AD1/DIO1 line of the module. Options include: Analog to Digital converter,Digital Input and Output. Default: 0 */
	#define D2 0 /* Configure options for the AD2/DIO2 line of the module. Options include: Analog to Digital converter,Digital Input and Output. Default: 0 */
	#define D3 0 /* Configure options for the AD3/DIO3 line of the module. Options include: Analog to Digital converter,Digital Input and Output. Default: 0 */
	#define D4 0 /* Configure options for the DIO4 line of the module. Options include: Digital Input and Output. Default: 0 */
	#define D5 1 /* Configure options for the DIO5/Assoc line of the module. Options include: Associated LED indicator (blinks when associated),Digital Input and Output. Default: 1 */
	#define P0 1 /* Configure options for the DIO10 line of the module. Options include: RSSI PWM Output, Digital Input and Output. Default: 1 */
	#define P1 0 /* Configure options for the DIO11 line of the module. Options include: Digital Input and Output. Default: 0 */
	#define P2 0 /* Configure options for the DIO12 line of the module. Options include: Digital Input and Output. Default: 0 */
	#define PR 1FFF /* Set/read bitfield to configure internal pullup resistors status for I/O lines. 1=internal pullup enabled, 0=no internal pullup. Bitfield map: (13)DIO7/CTS, (12)-DIO11, (11)-DIO10/PWM0, 
	                 * (10)-DIO12, (9)-On/Sleep, (8)Associate, (7)-DIN/Config, (6)-Sleep_Rq, (5)-RTS, (4)-AD0/DIO0, (3)-AD1/DIO1, (2)-AD2/DIO2, (1)-AD3/DIO3, (0)-DIO4
					 * Range: 0x0-0x3FFF (Default: 1FFF) */
	#define LT 0 /* Set/read the Associate LED blink rate. This value determines the blink rate of the Associate/DIO5 pin if D5=1 and the module has started a network. Setting LT to 0 will use the default blink time (250ms).
                  * Range: 0x0A-0xFF (Default: 0) */
	#define RP 28 /* Set/read PWM timer register. Set duration of PWM (pulse width modulation) signal output on the RSSI pin (P6). The signal duty cycle is updated with each received packet or APS acknowledgment and is 
	               * shut off when the timer expires. 
				   * Range: 0x0-0xFF (Default: 28) */
	#define DO 1 /* Bit0 - Reserved. Bit1 - Reserved. Bit2 - 0/1 = First or Best Response. Bit3 - Reserved.
	              * Range: 0x0-0xFF (Default: 1) */
	
	
/*********************************************************** I/O Sampling *************************************************************/
	
	
	#define IR 0 /* Set the IO sampling rate to enable periodic sampling. If set >0, all enabled digital IO and analog inputs will be sampled and transmitted every IR milliseconds. IO Samples are transmitted to the address
	              * specified by DH+DL.
				  * Range: 0x32-0xFFFF (Default: 0) */
	#define IC 0 /* Bitfield that configures which digital IO pins should be monitored for change detection. If a change is detected on an enabled digital IO pin, a digital IO sample is immediately transmitted to the address
	              * specified by DH+DL.	
				  * Range: 0x0-0xFFFF (Default: 0) */
	#define V+ 0 /* Configure the supply voltage high threshold. If the supply voltage measurement equals or drops below this threshold, the supply voltage will be appended to an IO sample transmission. Since the operating Vcc 
	              * range for the XBee is 2100-3600 mV, after scaling by 1024/1200, the useful range for this parameter is 0,0x0700-0x0c00.
				  * Range: 0x0-0xFFFF (Default:0) */
	
	

	#define 



	
#endif





int XbeeSetup()
{
	char d;
	printf("+++\n");
	#ifdef XBEES1
		#ifdef ID
			printf("ATID%d",ID);
			// wait for 'OK'
			d= receive_Msg(&pkt);
			printf("%x \t", d);
			//setPANID(ID);	// Set PAN ID
		#endif
		#ifdef CH
			printf("Channel%d", CH);
			// wait for 'OK'
			
		#endif
		#ifdef DH
			printf("DestinationHigh%d", DH);
			//wait for 'OK'
		#endif
		#ifdef DL
			printf("DestinationLow%d", DL);
		#endif
		#ifdef MY
			printf("Source Address%d", MY);
		#endif
		#ifdef MM
			setMacMode(MM);
		#endif
		#ifdef RR
			printf("Retries%d", RR);
		#endif
		#ifdef NO
			enNodeDisc(NO);
		#endif
		#ifdef CE
			setDevice(CE);
		#endif
		#ifdef SC
			setChScan(SC);
		#endif
		#ifdef SD
			setScanTime(SD);
		#endif
		#ifdef A1
			setAssoc(A1);
		#endif
		
		
		
		
		
		
		
		
	
#endif
	
	return 1;
}


#endif /* XBEECONFIG_H_ */
