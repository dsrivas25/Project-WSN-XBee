/*
 * XbeeHAL.h
 *
 * Created: 1/15/2014 3:02:11 PM
 *  Author: Waron
 */ 

#ifndef XBEEHAL_H_
#define XBEEHAL_H_

#include "Xbee.h"

//#define ATMEGA2560
#define ATMEGA328P

// Register Names for selected microcontroller
#ifdef ARDUINO_UNO
	#include <avr/io.h>
	#include <avr/interrupt.h>

	// Registers
	#define XBEE_TDR UDR0	
	#define XBEE_RDR UDR0	

	// Macros	
	#define RX_BUFFER_IS_FULL() ((UCSR0A & (1 << RXC0)) == 0)
	#define TX_BUFFER_IS_FULL() ((UCSR0A & (1 << UDRE0)) == 0)
	#define TOGGLE_LED() (PORTD ^= 0x80)
	#define LED_OUTPUT() (DDRD |= 0x80)
	#define EN_INT() sei()	// enable interrupts
	#define DIS_INT() cli()	// disable interrupts
	
	#define RSSI_PIN PIND
	#define RSSI_DDR DDRD
	#define RSSI_PIN_NO PIND3
	
	// Functions
	ISR(USART_RX_vect) { serialEvent(); }

	/* Code to initialize USART
	 *
	 * Eventually, this function should receive a USART number (e.g., 0-X, X being the number of USARTs available
	 * on the chip) and a baud rate. For now, we will use the #define variables to set this.
	 */		
	void USART_INIT(void)
	{
		UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
		UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register

		UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
		UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
		// Enable RX interrupt as well.
	}	
#endif


#ifdef ATMEGA328P
	#include <avr/io.h>
	#include <avr/interrupt.h>

	// USART Definitions
	#ifdef F_CPU
		#pragma message ("F_CPU already defined.")
	#else
		#define F_CPU 16000000	//be sure to adjust for various clock settings
	#endif
	#define USART_BAUDRATE 9600
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

	// Registers
	#define XBEE_TDR UDR0	
	#define XBEE_RDR UDR0	

	// Macros	
	#define RX_BUFFER_IS_FULL() ((UCSR0A & (1 << RXC0)) == 0)
	#define TX_BUFFER_IS_FULL() ((UCSR0A & (1 << UDRE0)) == 0)
	#define TOGGLE_LED() (PORTD ^= 0x80)
	#define LED_OUTPUT() (DDRD |= 0x80)
	#define EN_INT() sei()	// enable interrupts
	#define DIS_INT() cli()	// disable interrupts
	
	#define RSSI_PIN PIND
	#define RSSI_DDR DDRD
	#define RSSI_PIN_NO PIND3
	
	// Functions
	ISR(USART_RX_vect) { rxISR(); }

	/* Code to initialize USART
	 *
	 * Eventually, this function should receive a USART number (e.g., 0-X, X being the number of USARTs available
	 * on the chip) and a baud rate. For now, we will use the #define variables to set this.
	 */		
	void USART_INIT(void)
	{
		UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
		UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register

		UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes
		UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
		// Enable RX interrupt as well.
	}

#endif

#ifdef ATMEGA2560
	#include <avr/io.h>
	#include <avr/interrupt.h>

	// USART Definitions
	#ifdef F_CPU
		#pragma message ("F_CPU already defined.")
	#else
		#define F_CPU 8000000	//be sure to adjust for various clock settings
	#endif
	#define USART_BAUDRATE 9600
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

	// Registers
	#define USART_NO 3
	#define XBEE_TDR UDR3	
	#define XBEE_RDR UDR3	

	// Macros
	#define RX_BUFFER_IS_FULL() ((UCSR3A & (1 << RXC3)) == 0)
	#define TX_BUFFER_IS_FULL() ((UCSR3A & (1 << UDRE3)) == 0)
	#define TOGGLE_LED() (PORTD ^= 0x80)
	#define LED_OUTPUT() (DDRD |= 0x80)
	#define EN_INT() sei()	// enable interrupts
	#define DIS_INT() cli()	// disable interrupts
	
	#define RSSI_PIN PIND
	#define RSSI_DDR DDRD
	#define RSSI_PIN_NO PIND3
	
	// Functions
	ISR(USART3_RX_vect) { rxISR(); }
	
	/* Code to initialize USART
	 *
	 * Eventually, this function should receive a USART number (e.g., 0-X, X being the number of USARTs available
	 * on the chip) and a baud rate. For now, we will use the #define variables to set this.
	 */
	void USART_INIT(void)
	{
		UBRR3L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
		UBRR3H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register

		UCSR3C |= (1 << UCSZ30) | (1 << UCSZ31); // Use 8-bit character sizes
		UCSR3B |= (1 << RXCIE3) | (1 << RXEN3) | (1 << TXEN3);   // Turn on the transmission and reception circuitry
		// Enable RX interrupt as well.
	}
#endif

#ifdef RX63N
	// This code is compatible with the Renesas RX63N and the Renesas Compiler. Code written in HEW IDE.
	#include "platform.h"
	
	// USART Definitions
	#define USART_BAUDRATE 9600

	// Registers
	#define USART_NO 6
	#define XBEE_TDR SCI6.TDR	
	#define XBEE_RDR SCI6.RDR

	// Macros
	#define RX_BUFFER_IS_FULL() !(SCI6.SSR.BYTE & 0x40)
	#define TX_BUFFER_IS_FULL() (!SCI6.SSR.BIT.TEND)
	#define TOGGLE_LED() (PORTD.PODR.BIT.B0 ^= 1)
	#define LED_OUTPUT() (PORTD.PDR.BIT.B0 = 1)
	#define EN_INT() {IEN(SCI6, RXI6) = 1;}	// enable interrupts
	#define DIS_INT()    {IEN(SCI6, RXI6) = 0; if(IEN(SCI6, RXI6)) /* Wait for pipelining. See manual about writing I/O registers. */{}} 	// disable interrupts
	
	#define RSSI_PIN PIND
	#define RSSI_DDR DDRD
	#define RSSI_PIN_NO PIND3
	
	// Functions
	//#pragma interrupt SCI2_RXI2_isr(vect = VECT_SCI2_RXI2, enable)
	//static void SCI2_RXI2_isr(void)
	
	#pragma interrupt SCI6_RXI6_isr(vect = VECT_SCI6_RXI6, enable)
	static void SCI6_RXI6_isr(void) 
	{ 
		//DIS_INT();
		rxISR();
		while(SCI6.SSR.BIT.ORER)   // Check for overrun error.
		{
			SCI6.SSR.BIT.ORER = 0; // Clear overrun error. Repeats until condition cleared.                          
		} 
	}
	
	/* Code to initialize USART
	 *
	 * Eventually, this function should receive a USART number (e.g., 0-X, X being the number of USARTs available
	 * on the chip) and a baud rate. For now, we will use the #define variables to set this.
	 */
	void USART_INIT(void)
	{
		// Initializes USART Communications on SCI6
		uint16_t i; /* for delay counter */


	    #ifdef PLATFORM_BOARD_RDKRX63N
		SYSTEM.PRCR.WORD = 0xA50B; /* Protect off */
	    #endif
    
		/* clear ACSE Bit (All-Module Clock Stop Mode Enable) */	
		SYSTEM.MSTPCRA.BIT.ACSE = 0;  
	  
		/* Cancel stop state of SCI2 Peripheral to enable writing to it*/	
	    MSTP(SCI6) = 0;	
    
	    #ifdef PLATFORM_BOARD_RDKRX63N
		SYSTEM.PRCR.WORD = 0xA500; /* Protect on  */
	    #endif     
    
	    /* Clear bits TIE, RIE, RE, and TEIE in SCR to 0. Set CKE to internal. */
		SCI6.SCR.BYTE = 0x00;

	    /* Set up the UART I/O port and pins. */
	    MPC.P32PFS.BYTE  = 0x4A ; /* P50 is TxD6 */
	    MPC.P33PFS.BYTE  = 0x4A ; /* P52 is RxD6 */
	
	    PORT3.PDR.BIT.B2 = 1;    /* TxD6 is output. */
	    PORT3.PDR.BIT.B3 = 0;    /* RxD6 is input. */
	
	    PORT3.PMR.BIT.B2 = 1;    /* TxD6 is peripheral. */
	    PORT3.PMR.BIT.B3 = 1;    /* RxD6 is peripheral. */

		/* Set data transfer format in Serial Mode Register (SMR)*/ 
		/*  -Asynchronous Mode`
		    -8 bits
		    -no parity
		    -1 stop bit
		    -PCLK clock (n = 0) */
		SCI6.SMR.BYTE = 0x00;
    
	    SCI6.SCMR.BIT.SMIF = 0; /* Set to 0 for serial communications interface mode. */
    
		/* Set bit rate register.
	       Example: set to 115200 baud
		        N = (PCLK Frequency) / (64 * 2^(2*n - 1) * Bit Rate) - 1
		        N = (48,000,000)     / (64 * 2^(2*0 - 1) * 115200)   - 1
		        N = 12 */
		SCI6.BRR = 48000000 / ((64/2) * USART_BAUDRATE) - 1; /* SCI2.BRR = 12; 12 is for 115200 */

		/* Wait at least one bit interval */
	    /* TODO: check this for sufficient delay */
		for (i = 0; i < 200; i++) /* assume minimum of 2 instructions at 98MHz? */
		{
		}
	    
	    /* Enable RXI and TXI interrupts in SCI peripheral */
		SCI6.SCR.BIT.RIE  = 1;   /* Set Receive Interrupt (RX buffer full) enable. */
		SCI6.SCR.BIT.TIE  = 1;   /* Set Transmit Interrupt (TX data register empty) enable. */
	    SCI6.SCR.BIT.TEIE = 1;   /* Set Transmit End interrupt enable */
	
	    /* Clear IR bits for TIE and RIE */
	    IR(SCI6, RXI6) = 0;
	    IR(SCI6, TXI6) = 0;
    
	    /* RXI and TXI interrupts in ICU. */
	    /* Designer option--handle ICU interrupt enables at application level */
	    //IEN(SCI6, RXI6) = 1;
	    /* IEN(SCI2, TXI2) = 1; */
    
		/* Set interrupt prio for SCI. */
		IPR(SCI6, TXI6) = 1;
		IPR(SCI6, RXI6) = 1;

		/* Enable Tx/Rx */
	    /* Note: A 1 can only be written to these bits when TE = 0 and RE = 0. */
	    /* After setting TE or RE to 1, only 0 can be written in TE and RE.    */
	    /* So to enable both, write them simultaneously.                       */
		SCI6.SCR.BYTE |= 0x30;
		SCI6.RDR = 0;
	}


#endif


#endif /* XBEEHAL_H_ */
