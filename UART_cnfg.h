/*
 * UART_cnfg.h
 *
 *  Created on: Oct 11, 2019
 *      Author: PeterKleber
 */

#ifndef UART_CNFG_H_
#define UART_CNFG_H_

#include "std_types.h"

typedef enum {B_9600,} Baudrate_t;

typedef enum {NO_Parity, Even, Odd} Prity_t;
typedef enum {No_Interrupt,Interrupt} Interrupt_t;


typedef struct {
	Baudrate_t Baudrate;

	uint8 No_of_stop_bits;

	Prity_t Parity;
	uint8 No_of_parity_bits;

	uint8 No_of_data_bits;
	Interrupt_t Interrupt ;

} UART_cnfg_t;

extern UART_cnfg_t UART_cnfg_struct;

#endif /* UART_CNFG_H_ */
