/*
 * head.c
 *
 *  Created on: 13 апр. 2015 г.
 *      Author: andrey
 */


// Define some constants.
#define ETH_HDRLEN 14  // Ethernet header length
#define IP4_HDRLEN 20  // IPv4 header length
#define UDP_HDRLEN  8  // UDP header length, excludes data



#include <stdio.h>


//#include <netinet/if_ether.h>
//#include <netpacket/packet.h>
#include <sys/ioctl.h>



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()

#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t, uint32_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_UDP, INET_ADDRSTRLEN
#include <netinet/ip.h>       // struct ip and IP_MAXPACKET (which is 65535)
#include <netinet/udp.h>      // struct udphdr
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_IP = 0x0800, ETH_P_IPV6 = 0x86DD
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>

#include <errno.h>            // errno, perror()


struct params_struct
{
    struct sockaddr_ll device;
	struct ip iphdr;
	struct udphdr udphdr;
	int clients_num, datalen, frame_length, sd[255];
	char *interface, *target, *src_ip, *dst_ip;
	uint8_t *data, *src_mac, *dst_mac, *ether_frame;
	int *ip_flags;


};

typedef struct params_struct *pstruct_t;


struct data_from_file{
	int clients_num;
	char *iface;
	int datalen;
	unsigned int src_mac[6];
	unsigned int dst_mac[6];
	char *src_ip, *dst_ip;
};



int ptp_client_init(struct params_struct *params, int k);
int ptp_client_sent(struct params_struct *params, int k);
int ptp_client_set(struct params_struct *params, char **argv);
int ptp_client_change(struct params_struct *params, int k);




int get_ip_hdr(struct params_struct *params);
int get_udp_hdr(struct params_struct *params);
int get_ptp(struct params_struct *params);


// Function prototypes
uint16_t checksum (uint16_t *, int);
uint16_t udp4_checksum (struct ip, struct udphdr, uint8_t *, int);
char *allocate_strmem (int);
uint8_t *allocate_ustrmem (int);
int *allocate_intmem (int);



int sock_raw_func(void);

int pf_packet_func(int argc, char **argv);

int ptp_packgen_func(int argc, char **argv);

uint16_t checksum (uint16_t *addr, int len);
//uint16_t udp4_checksum (struct ip iphdr, struct udphdr udphdr, uint8_t *payload, int payloadlen);
char * allocate_strmem (int len);
int * allocate_intmem (int len);



uint16_t udp4_checksum(struct ip iphdr, struct udphdr udphdr, uint8_t *payload, int payloadlen);

