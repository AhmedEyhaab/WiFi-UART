/*
 * Wifi.c
 *
 * Created: 10/30/2019 1:23:41 PM
 * Author : Ahmed Ehab and Peter Kleber
 */

#include "std_types.h"
#include <util/delay.h>
#include <avr/io.h>
#include "UART.h"
#include "motor.h"
#include "PWM.h"

uint8 Received_Character = 0;

uint8 AT[]="AT";			//AT - Test AT startup
uint8 ATE0[]="ATE0";		//Disable echo (Doesn’t send back received command)
uint8 AT_MODE[]="AT+CWMODE=2";	//WIFI mode (host)
uint8 AT_MUX[]="AT+CIPMUX=1";	//AT+CIPMUX - Enable multiple connections
uint8 AT_CWSAP[]="AT+CWSAP=\"Ehab\",\"123456789\",1,3";	//Configuration of softAP mode  "SSID" , "Password" (no longer than 64 characters) , ch: channel id , ecn: 3 = WPA2_PSK
uint8 AT4[]="AT+CWJAP=";		//AT+CWJAP - Connect to AP 	(SSID,Password)
uint8 AT_Server[]="AT+CIPSERVER=1";	//AT+CIPSERVER - Configure as server , port: port number, default is 333
uint8 AT_PORT[]="1234";
uint8 AT_GET_IP[]="AT+CIFSR";


//This Function is used to send the String in UART Communication
Std_Func_t UART_Send_String(uint8 *String) 
{
	 uint8 i = 0;
	while (String[i] != '\0') {
		UART_send(String[i]);
		i++;
		_delay_ms(10);
	}
	// Below Values is used to send the Enter so as to send the AT Command and followed by Enter
	UART_send(0x0D);
	UART_send(0x0A);
	return OK;
}

//This Function is used to run in the ISR of UART_Receive 
void RX_Callback(void) {
    PORTB ^=(1<<PB4);
     uint8 temp = 0 ;
	 UART_recieve(&temp);			
    if((64 < temp)&&(temp<123))			//This Condition is used to select The Useful Character to take action upon 
	{
    	Received_Character =temp;
    }

}

int main(void) {
    DDRB = 0xFF;

    DIO_init();						//Initialization of DIO 
    Phase_Correct_PWM(100);			// Set the PWM Value which feed Motors 

    UART_Set_Callback_RX(RX_Callback);	// Function is used to Set the Callback UART_Receiver
	UART_init();

	_delay_ms(1000);			// Wait for the Initialization to be done

	
	// These Below Commands are used to Send the AT Commands to ESP8266
	UART_Send_String(AT);
	_delay_ms(1000);

	UART_Send_String(ATE0);
	_delay_ms(1000);

	UART_Send_String(AT_MODE);
	_delay_ms(1000);

	UART_Send_String(AT_CWSAP);
	_delay_ms(1000);

	UART_Send_String(AT_MUX);
	_delay_ms(1000);

	UART_Send_String(AT_Server);
	_delay_ms(1000);

	PORTB|=(1<<PB4);			//Indication of the AT Commands sent to the ESP8266

	while (1) {

		//Upon the Recieved Character from UART_Receive to take the proper Action 
		switch(Received_Character)
		{
			case'a':
			{
				MOTOR_CarForward();
				PORTB|=(1<<PB5);
				PORTB&=~(1<<PB6);

				break;
			}

			case'b':
			{
				MOTOR_CarBackward();
				PORTB|=(1<<PB6);
				PORTB&=~(1<<PB5);
				break;
			}

			case'c':
			{

				PORTB|=(1<<PB7);
				break;
			}

			case'd':
			{

				break;
			}

			default:
			{
				MOTOR_CarStop();
				PORTB&=~(1<<PB5);
				PORTB&=~(1<<PB6);
				break;
			}
		}
		Received_Character = 0;

		_delay_ms(3000);

}}
