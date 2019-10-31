/*
 * PWM.h
 *
 *  Created on: Oct 2, 2019
 *      Author: Mohammed
 */

#ifndef PWM_H_
#define PWM_H_


#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>


extern void Phase_Correct_PWM(double duty_cycle);

#endif /* PWM_H_ */
