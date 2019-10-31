/*
 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#include "UART.h"

static void (*UART_Callback_RX)() = NULL_PTR;
static void (*UART_Callback_TX)() = NULL_PTR;

Std_Func_t UART_init() {

	//UCSRA = (1<<U2X); /* U2X = 1 for double transmission speed */
	    	 SREG |= (1u<< 7 ) ; // ENABLE GLOBAL INTERRUPT

			UCSRB = (1<<RXEN) | (1<<TXEN);

			UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

			/* baud rate=9600 & Fosc=1MHz -->  UBBR=( Fosc / (8 * baud rate) ) - 1 = 12 */
			UBRRH = 0;
			UBRRL = 51;

	UCSRB |= (1 << RXCIE);
	UCSRB |= (1 << TXCIE);

	return OK;

/*	Std_Func_t retval = OK;

	//Enabling receiver and transmitter
	UCSRB |= (1 << RXEN);
	UCSRB |= (1 << TXEN);

	//Setting URSEL bit to write to UCSRC
	UCSRC |= (1 << URSEL);

	//Configure No of data bits
	switch (UART_cnfg_struct.No_of_data_bits) {
	case 5:
		//No of data bits = 5 UCSZ0 = 0 UCSZ1 = 0 UCSZ2 = 0

		break;
	case 6:
		//No of data bits = 6 UCSZ0 = 1 UCSZ1 = 0 UCSZ2 = 0
		UCSRC |= (1 << UCSZ0);
		break;
	case 7:
		//No of data bits = 7 UCSZ0 = 0 UCSZ1 = 1 UCSZ2 = 0
		UCSRC |= (1 << UCSZ1);
		break;
	case 8:
		//No of data bits = 8 UCSZ0 = 1 UCSZ1 = 1 UCSZ2 = 0
		UCSRC |= (1 << UCSZ0);
		UCSRC |= (1 << UCSZ1);
		break;
	case 9:
		//No of data bits = 9 UCSZ0 = 1 UCSZ1 = 1 UCSZ2 = 1
		UCSRC |= (1 << UCSZ0);
		UCSRC |= (1 << UCSZ1);
		UCSRB |= (1 << UCSZ2);
		break;
	default:
		retval = NOK;
	}

	//Setting Baudrate
	if (UART_cnfg_struct.Baudrate == B_9600) {
		UBRRH &= ~(1 << URSEL); //The URSEL must be zero when writing the UBRRH.

		// baud rate=9600 & Fosc=8MHz -->  UBBR=( Fosc / (16 * baud rate) ) - 1 = 51
		UBRRH = 0;
		UBRRL = 51;

	} else {
		retval = NOK;
	}

	//Configure UART Parity
	switch (UART_cnfg_struct.Parity) {
	case NO_Parity:
		//No parity UPM1&UPM0 = 0
		break;
	case Even:
		//Even parity UPM1 = 1 & UPM0 = 0
		UCSRC |= (1 << UPM1);
		break;
	case Odd:
		//Odd parity UPM1 = 1 & UPM0 = 1
		UCSRC |= (1 << UPM0);
		UCSRC |= (1 << UPM1);
		break;
	default:
		retval = NOK;
	}

	//Configure No of stop bits USBS = 0 (1 stop bit )/USBS = 1 (2 stop bits )
	if (UART_cnfg_struct.No_of_stop_bits == 1) {
		}
	else if (UART_cnfg_struct.No_of_stop_bits == 2) {
		UCSRC |= (1 << USBS);
	} else {
		retval = NOK;
	}

	//Interrupt

	if (UART_cnfg_struct.Interrupt == Interrupt) {
		UCSRB |= (1 << RXCIE);
		UCSRB |= (1 << TXCIE);
		sei();
	}

	return retval;*/

}

Std_Func_t UART_send(const uint8 Data_to_sent) {

 if (UART_cnfg_struct.Interrupt != Interrupt) {

 while (!(UCSRA & (1 << UDRE))) {
 }
 }
 UDR = Data_to_sent;

 return OK;

 }

Std_Func_t UART_recieve(uint8 *Data_recieved) {

	if (UART_cnfg_struct.Interrupt == No_Interrupt) {
		while (!(UCSRA & (1 << RXC))) {
		}
	}
	*Data_recieved = UDR;

	return OK;
}

 Std_Func_t UART_Set_Callback_RX(void (*ptr)()) {

 UART_Callback_RX = ptr;

 return OK;
 }

 Std_Func_t UART_Set_Callback_TX(void (*ptr)()) {

 UART_Callback_TX = ptr;

 return OK;
 }

ISR(USART_RXC_vect) {

	 if (UART_Callback_RX != NULL_PTR) {
	 UART_Callback_RX();
	 }

}

ISR(USART_TXC_vect) {

	if (UART_Callback_TX != NULL_PTR) {
		UART_Callback_TX();
	}

}

