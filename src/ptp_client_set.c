/*
 * ptp_client_set.c
 *
 *  Created on: 18 апр. 2015 г.
 *      Author: andrey
 */




#include "head.h"
#include <stdlib.h>
#include <stdio.h>

int ptp_client_set(struct params_struct *params, char **argv){

	printf("config is: %s \n", argv[1]);

	struct data_from_file from_config;

	FILE *ifp;
	char *mode = "r";
	char *inputFilename = argv[1];

	ifp = fopen(inputFilename, mode);

	if (ifp == NULL) {
	  fprintf(stderr, "Can't open input file ./config.txt! \n");
	  exit(1);
	}


	ssize_t read;
	size_t len = 0;
	char * line = NULL;


	// Clients number
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	params->clients_num = atoi(line);							// !!! clients_num !!!
	//printf("clients_num: %d \n", from_config.clients_num);


	// Iface
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	line[strlen(line)-1] = 0;
	from_config.iface = allocate_strmem (40);
	strcpy(from_config.iface, line );


	// Datalen
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	from_config.datalen = atoi(line);							// !!! clients_num !!!
	//printf("datalen: %d \n", from_config.datalen);


	// Source MAC
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	line[strlen(line)-1] = 0;
	sscanf(line, "%x:%x:%x:%x:%x:%x", &from_config.src_mac[0], &from_config.src_mac[1], &from_config.src_mac[2], &from_config.src_mac[3], &from_config.src_mac[4], &from_config.src_mac[5]);
	//printf("SRC_MAC: %x:%x:%x:%x:%x:%x \n", from_config.src_mac[0], from_config.src_mac[1], from_config.src_mac[2], from_config.src_mac[3], from_config.src_mac[4], from_config.src_mac[5]);


	// Dst MAC
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	line[strlen(line)-1] = 0;
	sscanf(line, "%x:%x:%x:%x:%x:%x", &from_config.dst_mac[0], &from_config.dst_mac[1], &from_config.dst_mac[2], &from_config.dst_mac[3], &from_config.dst_mac[4], &from_config.dst_mac[5]);
	//printf("DST_MAC: %x:%x:%x:%x:%x:%x \n", from_config.dst_mac[0], from_config.dst_mac[1], from_config.dst_mac[2], from_config.dst_mac[3], from_config.dst_mac[4], from_config.dst_mac[5]);


	// SRC IP
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	line[strlen(line)-1] = 0;
	from_config.src_ip = allocate_strmem (40);
	strcpy(from_config.src_ip, line );

	// DST IP
	read = getline(&line, &len, ifp);
	read = getline(&line, &len, ifp);
	line[strlen(line)-1] = 0;
	from_config.dst_ip = allocate_strmem (40);
	strcpy(from_config.dst_ip, line );
	//printf("DST IP: %s \n", from_config.dst_ip);


	//====================================================================================
	// Теперь в цикле инициализируем столько params сколько
	// прочитали из файла в from_config.clients_num

	int k;
	for (k = 0; k < params->clients_num; k++){

	// Allocate memory for various arrays.
	params[k].src_mac = allocate_ustrmem (6);
	params[k].dst_mac = allocate_ustrmem (6);
	params[k].data = allocate_ustrmem (IP_MAXPACKET);
	params[k].ether_frame = allocate_ustrmem (IP_MAXPACKET);
	params[k].interface = allocate_strmem (40);
	params[k].target = allocate_strmem (40);
	params[k].src_ip = allocate_strmem (INET_ADDRSTRLEN);
	params[k].dst_ip = allocate_strmem (INET_ADDRSTRLEN);
	params[k].ip_flags = allocate_intmem (4);
	// Interface to send packet through.

	params[k].datalen = from_config.datalen;


	params[k].interface = from_config.iface;


	params[k].src_mac[0] = from_config.src_mac[0];
	params[k].src_mac[1] = from_config.src_mac[1];
	params[k].src_mac[2] = from_config.src_mac[2];
	params[k].src_mac[3] = from_config.src_mac[3];
	params[k].src_mac[4] = from_config.src_mac[4];
	params[k].src_mac[5] = from_config.src_mac[5] + k;
	//printf("src_mac: %d \n", params[k].src_mac[5]);
	//printf("src_mac: %x \n", params[k].src_mac[5]);


	params[k].dst_mac[0] = from_config.dst_mac[0];
	params[k].dst_mac[1] = from_config.dst_mac[1];
	params[k].dst_mac[2] = from_config.dst_mac[2];
	params[k].dst_mac[3] = from_config.dst_mac[3];
	params[k].dst_mac[4] = from_config.dst_mac[4];
	params[k].dst_mac[5] = from_config.dst_mac[5];


	int tmp[4];
	sscanf(from_config.src_ip, "%d.%d.%d.%d", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
	tmp[3] = tmp[3] + k;


	sprintf(from_config.src_ip, "%d.%d.%d.%d", tmp[0], tmp[1], tmp[2], tmp[3]);

	// Source IPv4 address: you need to fill this out
	strcpy (params[k].src_ip, from_config.src_ip);
	//printf("params[k].src_ip: %s \n", params[k].src_ip);

	// Destination URL or IPv4 address: you need to fill this out
	strcpy (params[k].target, from_config.dst_ip);
	printf("params[k].target: %s \n", params[k].target);

	}

	return params->clients_num;
}
