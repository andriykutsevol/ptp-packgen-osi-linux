/*
 * ptp_client_sent.c
 *
 *  Created on: 16 апр. 2015 г.
 *      Author: andrey
 */


#include "head.h"


int ptp_client_sent(struct params_struct *params, int k){


	// UDP checksum (16 bits)
	params->udphdr.check = udp4_checksum(params->iphdr, params->udphdr, params->data, params->datalen);

	//-------------------------------------------------


	//=================================================
	// Отправка пакета.


	// Send ethernet frame to socket.
	int bytes = 0;
	if ((bytes = sendto (params->sd[k], params->ether_frame, params->frame_length, 0, (struct sockaddr *) &params->device, sizeof (params->device))) <= 0) {
		perror ("sendto() failed");
		exit (EXIT_FAILURE);
	}// else {
	//	printf("Bytes %d: \n", bytes);
	//}

	// Close socket descriptor.
	//close (params->sd[k]);


	return 0;
}
