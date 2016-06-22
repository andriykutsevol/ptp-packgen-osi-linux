/*
 ============================================================================
 Name        : PTP_Client.c
 Author      : Andrey Kutsevol
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "head.h"

// USAGE:	sudo ./sock config.txt

int main(int argc, char **argv) {




	struct params_struct params[255];

	int clients_num;
	clients_num = ptp_client_set(params, argv);


	int j = 0;

	for(j=0; j < clients_num; j++){
		ptp_client_init(&params[j], j);
	}


	int k = 0;
	while(k < 100000){
		for(j=0; j< clients_num; j++){
			ptp_client_change(&params[j], j);
			ptp_client_sent(&params[j], j);
		}
		k = k + 1;
	}




	//=========================================

	return EXIT_SUCCESS;
}
