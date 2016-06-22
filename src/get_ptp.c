/*
 * get_ptp.c
 *
 *  Created on: 16 апр. 2015 г.
 *      Author: andrey
 */


#include "head.h"

int get_ptp(struct params_struct *params){

	  params->data[0] = 0b00000001;		// TransportSpecific

	  params->data[1] = 0b00000010;		// Version PTP

	  params->data[2] = 0b00000000;		// Message lenght
	  params->data[3] = 0b00101100;

	  params->data[4] = 0b00000000;		// Subdomain number
	  params->data[5] = 0b00000000;

	  params->data[5] = 0b00000000;		// Flags
	  params->data[5] = 0b00000000;

	  params->data[5] = 0b00000000;		// Correction Field
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;

	  params->data[5] = 0b00000000;		// ClockIdentity
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;

	  params->data[5] = 0b00000000;		// Source PortID
	  params->data[5] = 0b00000001;

	  params->data[5] = 0b00000000;		// Sequence ID
	  params->data[5] = 0b00000001;

	  params->data[5] = 0b00000001;		// Control

	  params->data[5] = 0b00111111;		// LogMessagePeriod

	  params->data[5] = 0b00000000;		// TimeStamp(seconds)
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;

	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;
	  params->data[5] = 0b00000000;		// TimeStamp(nanoseconds)


	return 0;
}
