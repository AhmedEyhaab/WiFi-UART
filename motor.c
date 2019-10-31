/*
 * motor.c
 *
 * Created: 10/2/2019 10:21:06 AM
 *  Author: Omar Sha3rawy
 */ 

#include "motor.h"
#include "DIO.h"

static void MOTOR_forward(motor_pairs);
static void MOTOR_backward(motor_pairs);
static void MOTOR_stop(motor_pairs);


void MOTOR_CarForward()
{
	MOTOR_forward(PAIR1);
	MOTOR_forward(PAIR2);
}

void MOTOR_CarBackward()
{
	MOTOR_backward(PAIR1);
	MOTOR_backward(PAIR2);
}

void MOTOR_CarStop()
{
	MOTOR_stop(PAIR1);
	MOTOR_stop(PAIR2);
}


void MOTOR_CarRight(uint16 duration)
{
	MOTOR_backward(PAIR1);
	MOTOR_forward(PAIR2);
	_delay_ms(TURN_TIME);

	MOTOR_stop(PAIR1);
	MOTOR_stop(PAIR2);
	_delay_ms(1000);
	
	MOTOR_forward(PAIR1);
	MOTOR_forward(PAIR2);
}

static void MOTOR_forward(motor_pairs mot)
{
	switch(mot){
		case PAIR1:
			DIO_write(motor1_c0, HIGH); // motor pair one
			DIO_write(motor1_c1, LOW);
		break;
		case PAIR2:
			DIO_write(motor2_c0, HIGH); // motor pair two
			DIO_write(motor2_c1, LOW);
		break;
	}
}

static void MOTOR_backward(motor_pairs mot)
{
	switch(mot){
		case PAIR1:
			DIO_write(motor1_c0, LOW); // motor pair one
			DIO_write(motor1_c1, HIGH);
		break;
		case PAIR2:
			DIO_write(motor2_c0, LOW); // motor pair two
			DIO_write(motor2_c1, HIGH);
		break;
	}
}

static void MOTOR_stop(motor_pairs mot)
{
	switch(mot){
		case PAIR1:
		DIO_write(motor1_c0, LOW); // motor pair one
		DIO_write(motor1_c1, LOW);
		break;
		case PAIR2:
		DIO_write(motor2_c0, LOW); // motor pair two
		DIO_write(motor2_c1, LOW);
		break;
	}
}
