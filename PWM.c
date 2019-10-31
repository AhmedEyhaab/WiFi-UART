/*
 * PWM.c
 *
 *  Created on: Oct 2, 2019
 *      Author: Mohammed
 */

#include "PWM.h"
#include "DIO.h"


void Phase_Correct_PWM(double duty_cycle)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */

	OCR1A= (255*(duty_cycle/100));
	OCR1B= (255*(duty_cycle/100));
	//OCR1A = duty_cycle; /* Set the compare value */


	/* Configure timer control register TCCR1A
     * 1. Clear OC1A/OC1B on compare match (non inverting mode) COM1A1=1 COM1A0=0  || COM1B=0 COM1B1=0
     * 2. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
     * 3. Phase Correct PWM Mode with TOP 0x00FF  WGM10=1 WGM11=0 (Mode Number 1)
	 */
	TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);

	/* Configure timer control register TCCR1A
	 * 1.  Phase Correct PWM Mode with TOP 0x00FF WGM12=0 WGM13=0 (Mode Number 1)
	 * 2. Prescaler = F_CPU/64
     */
	TCCR1B =   (1<<CS10) | (1<<CS11);
}
