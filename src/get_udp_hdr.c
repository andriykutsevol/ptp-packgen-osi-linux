/*
 * get_udp_hdr.c
 *
 *  Created on: 16 апр. 2015 г.
 *      Author: andrey
 */




#include "head.h"

int get_udp_hdr(struct params_struct *params){

	// UDP header

	// Source port number (16 bits): pick a number
	params->udphdr.source = htons (319);

	// Destination port number (16 bits): pick a number
	params->udphdr.dest = htons (319);

	// Length of UDP datagram (16 bits): UDP header + UDP data
	params->udphdr.len = htons (UDP_HDRLEN + params->datalen);


	return 0;
}
