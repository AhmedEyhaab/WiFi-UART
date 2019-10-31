/*
 * DIO_configuration.h
 *
 * Created: 9/20/2019 3:42:53 PM
 *  Author: omara
 */ 




#ifndef DIO_CONFIGURATION_H_
#define DIO_CONFIGURATION_H_

#include "std_types.h"

//typedef enum {motors_enable, motor1_c0, motor1_c1,  motor2_c0, motor2_c1, led_flag0, led_flag1,pwm , NUM_OF_PINS} pintype;

typedef enum {motor1_c0,motor1_c1,motors_enable1,motor2_c0,motor2_c1,motors_enable2,NUM_OF_PINS} pintype;

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW	 0

#define PULLUP 1
#define EXTRES 0

#define INITIALIZED 1
#define NOT_INITIALIZED 0

#define NA 0xff

typedef struct
{
	uint8 PORT;
	uint8 PIN;
	uint8 DIR;
	uint8 OUT;
	uint8 RES;
	uint8 IS_initialized;
}DIO_cnfig;

extern DIO_cnfig DIO_cnfig_list [NUM_OF_PINS];


#endif /* DIO_CONFIGURATION_H_ */
