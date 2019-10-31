/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART_cnfg.h"

Std_Func_t UART_init();

Std_Func_t UART_send(const uint8 Data_to_sent);

Std_Func_t UART_recieve(uint8 *Data_recieved);

Std_Func_t UART_Set_Callback_RX(void (*ptr)());

Std_Func_t UART_Set_Callback_TX(void (*ptr)());

#endif /* UART_H_ */
