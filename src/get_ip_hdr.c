/*
 * get_ip_hdr.c
 *
 *  Created on: 16 апр. 2015 г.
 *      Author: andrey
 */

#include "head.h"


int get_ip_hdr(struct params_struct *params){

	// IPv4 header

	// IPv4 header length (4 bits): Number of 32-bit words in header = 5
	params->iphdr.ip_hl = IP4_HDRLEN / sizeof (uint32_t);

	// Internet Protocol version (4 bits): IPv4
	params->iphdr.ip_v = 4;

	// Type of service (8 bits)
	params->iphdr.ip_tos = 0;

	// Total length of datagram (16 bits): IP header + UDP header + datalen
	params->iphdr.ip_len = htons (IP4_HDRLEN + UDP_HDRLEN + params->datalen);

	// ID sequence number (16 bits): unused, since single datagram
	params->iphdr.ip_id = htons (0);

	// Flags, and Fragmentation offset (3, 13 bits): 0 since single datagram

	// Zero (1 bit)
	params->ip_flags[0] = 0;

	// Do not fragment flag (1 bit)
	params->ip_flags[1] = 0;

	// More fragments following flag (1 bit)
	params->ip_flags[2] = 0;

	// Fragmentation offset (13 bits)
	params->ip_flags[3] = 0;

	params->iphdr.ip_off = htons ((params->ip_flags[0] << 15)
			+ (params->ip_flags[1] << 14)
			+ (params->ip_flags[2] << 13)
			+  params->ip_flags[3]);

	// Time-to-Live (8 bits): default to maximum value
	params->iphdr.ip_ttl = 255;

	// Transport layer protocol (8 bits): 17 for UDP
	params->iphdr.ip_p = IPPROTO_UDP;


	// IPv4 header checksum (16 bits): set to 0 when calculating checksum
	params->iphdr.ip_sum = 0;
	params->iphdr.ip_sum = checksum ((uint16_t *) &params->iphdr, IP4_HDRLEN);

	return 0;
}
