/*
 * ptpt_client_init.c
 *
 *  Created on: 16 апр. 2015 г.
 *      Author: andrey
 */




#include "head.h"


// Все задаваемые пользователем параметры сюда уже заходят.
// Тут они инкрементируются.
int ptp_client_init(struct params_struct *params, int k){


	//==============================================
	//========= Проверка интерфейса ================


	char *interface;
	interface = allocate_strmem (40);
	// Interface to send packet through.
	strcpy (interface, "lo");
	struct ifreq ifr;

	int sdt;
	// Submit request for a socket descriptor to look up interface.
	if ((sdt = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
		perror ("socket() failed to get socket descriptor for using ioctl() ");
		exit (EXIT_FAILURE);
	}


	// Use ioctl() to look up interface name and get its MAC address.
	memset (&ifr, 0, sizeof (ifr));
	snprintf (ifr.ifr_name, sizeof (ifr.ifr_name), "%s", interface);
	if (ioctl (sdt, SIOCGIFHWADDR, &ifr) < 0) {
		perror ("ioctl() failed to get source MAC address ");
		return (EXIT_FAILURE);
	} else {
		//printf("SIOCGIFHWADDR IS OK \n");
	}
	close (sdt);




	//==============================================
	//========= Инициализация сокета ===============



	// Submit request for a raw socket descriptor.
	if ((params->sd[k] = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
		perror ("socket() failed ");
		exit (EXIT_FAILURE);
	}else{
		//printf("sd is OK: %d \n", params->sd[k]);

	}




	//==============================================
	//================= Заводим IP ============

	struct sockaddr_in *ipv4;
	struct addrinfo hints, *res;
	int status;
	void *tmp;

	  // Fill out hints for getaddrinfo().
	  memset (&hints, 0, sizeof (struct addrinfo));
	  hints.ai_family = AF_INET;
	  hints.ai_socktype = SOCK_STREAM;
	  hints.ai_flags = hints.ai_flags | AI_CANONNAME;


	  // Resolve target using getaddrinfo().
	  printf("params->target: %s \n", params->target);
	  if ((status = getaddrinfo (params->target, NULL, &hints, &res)) != 0) {
		  fprintf (stderr, "getaddrinfo() failed: %s\n", gai_strerror (status));
		  exit (EXIT_FAILURE);
	  }
	  printf("AFTER \n");
	  ipv4 = (struct sockaddr_in *) res->ai_addr;
	  tmp = &(ipv4->sin_addr);
	  if (inet_ntop (AF_INET, tmp, params->dst_ip, INET_ADDRSTRLEN) == NULL) {
		  status = errno;
		  fprintf (stderr, "inet_ntop() failed.\nError message: %s", strerror (status));
		  exit (EXIT_FAILURE);
	  }
	  freeaddrinfo (res);
	  //-------------------------------------------------

	  // Source IPv4 address (32 bits)
	  if ((status = inet_pton (AF_INET, params->src_ip, &(params->iphdr.ip_src))) != 1) {
		  fprintf (stderr, "inet_pton() failedddd.\nError message: %s", strerror (status));
		  exit (EXIT_FAILURE);
	  }

	  // Destination IPv4 address (32 bits)
	  if ((status = inet_pton (AF_INET, params->dst_ip, &(params->iphdr.ip_dst))) != 1) {
		  fprintf (stderr, "inet_pton() failedssss.\nError message: %s", strerror (status));
		  exit (EXIT_FAILURE);
	  }

	//==============================================
	//========= Инициализация девайса ==============


	  // Find interface index from interface name and store index in
	  // struct sockaddr_ll device, which will be used as an argument of sendto().


	  memset (&params->device, 0, sizeof (params->device));
	  if ((params->device.sll_ifindex = if_nametoindex (params->interface)) == 0) {
	    perror ("if_nametoindex() failed to obtain interface index ");
	    exit (EXIT_FAILURE);
	  }
	  //printf ("Index for interface %s is %i\n", params->interface, params->device.sll_ifindex);

	  // Fill out sockaddr_ll.
	  params->device.sll_family = AF_PACKET;
	  memcpy (params->device.sll_addr, params->src_mac, 6 * sizeof (uint8_t));
	  params->device.sll_halen = 6;


		//==============================================
		//=============== Основная сборка пакета =======
	   	// В ходе отправки пакетов некоторые данные будут меняться выборочно.


		get_ip_hdr(params);

		//-------------------------------------------------


		get_udp_hdr(params);


		//-------------------------------------------------

		get_ptp(params);



		//------------ Затусовка ether_frame --------------


		// Destination and Source MAC addresses
		memcpy (params->ether_frame, params->dst_mac, 6 * sizeof (uint8_t));
		memcpy (params->ether_frame + 6, params->src_mac, 6 * sizeof (uint8_t));

		// Next is ethernet type code (ETH_P_IP for IPv4).
		// http://www.iana.org/assignments/ethernet-numbers
		params->ether_frame[12] = ETH_P_IP / 256;
		params->ether_frame[13] = ETH_P_IP % 256;

		// Next is ethernet frame data (IPv4 header + UDP header + UDP data).

		// IPv4 header
		memcpy (params->ether_frame + ETH_HDRLEN, &params->iphdr, IP4_HDRLEN * sizeof (uint8_t));

		// UDP header
		memcpy (params->ether_frame + ETH_HDRLEN + IP4_HDRLEN, &params->udphdr, UDP_HDRLEN * sizeof (uint8_t));

		// UDP data
		memcpy (params->ether_frame + ETH_HDRLEN + IP4_HDRLEN + UDP_HDRLEN, params->data, params->datalen * sizeof (uint8_t));


		// Ethernet frame length = ethernet header (MAC + MAC + ethernet type) + ethernet data (IP header + UDP header + UDP data)
		params->frame_length = 6 + 6 + 2 + IP4_HDRLEN + UDP_HDRLEN + params->datalen;



	return 0;

}
