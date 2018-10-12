/*
* @Author: vutt6
* @Date:   2018-10-10 17:05:30
* @Last Modified by:   vutang
* @Last Modified time: 2018-10-12 15:16:23
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#include <string.h>
#include <error.h>
#include <errno.h>
#include "lib/logger.h"

#define LOGDIR "./lightSensor.log"
#define CLIENT_UDP_PORT 7777
#define SERVER_UDP_PORT 6666
#define SERVER_IP "192.168.120.100"

typedef unsigned int u_int32_t; /* 32 bit unsigned integer */
typedef unsigned short u_int16_t; /* 16 bit unsigned integer */
typedef unsigned char u_int8_t; /* 8 bit unsigned integer */
typedef signed int s_int32_t; /* 32 bit signed integer */
typedef signed short s_int16_t; /* 16 bit signed integer */
typedef signed char s_int8_t; /* 8 bit signed integer */

typedef struct _str_udpskt_id_t {
	int socket_fd;
	struct sockaddr_in socket_addr;
	int8_t socket_isOpen;
} str_udpskt_id_t;

typedef enum {
	SOCKET_RET_OK,
	SOCKET_RET_ERROR
} en_skt_ret_t;

pthread_t tid_timer; /*For timer thread*/
str_udpskt_id_t gcli_skt;
int8_t gtest_eth_flag = 1;
char server_ip[INET_ADDRSTRLEN];

void send_udp_test_pattern(void);

void testLog() {
	LOG_WARN("LOG_WARN");
	LOG_DEBUG("LOG_DEBUG");
	LOG_INFO("LOG_INFO");
	LOG_ERROR("LOG_ERROR");
	LOG_FATAL("LOG_FATAL");
}

void *timer_check(void *p) {
	while (1) {
		if (gtest_eth_flag) 
			send_udp_test_pattern();
		sleep(1);
	}
}

void open_timer_thd(void) {
	pthread_attr_t pthread_attr;
	pthread_attr_init(&pthread_attr); 
	pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&tid_timer, &pthread_attr, &timer_check, NULL) != 0) {
		LOG_ERROR("Create timer_check thread fail");
	}
	pthread_attr_destroy(&pthread_attr);
}

en_skt_ret_t cli_udpskt_open(str_udpskt_id_t *pskt_id, int16_t udpPort) {
	/*Init Socket ID*/
	pskt_id->socket_fd = -1;
	pskt_id->socket_addr.sin_family = AF_INET;
	pskt_id->socket_addr.sin_port = 0;
	pskt_id->socket_addr.sin_addr.s_addr = 0;
	pskt_id->socket_isOpen = 0;
	memset(&(pskt_id->socket_addr.sin_zero), 0, 8);

	/*Open an Socket*/
	pskt_id->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (pskt_id->socket_fd < 0) {
		LOG_ERROR("Socket open fail errno = %s", (char *) strerror(errno));
		return -SOCKET_RET_ERROR;
	}

	pskt_id->socket_addr.sin_port = htons(udpPort);
	pskt_id->socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*Bind*/
	if (bind(pskt_id->socket_fd, (struct sockaddr *) &pskt_id->socket_addr, \
		sizeof(struct sockaddr)) < 0) {
		LOG_ERROR("Socket bind fail errno = %s", strerror(errno));
		return -SOCKET_RET_ERROR;
	}
	return SOCKET_RET_OK;
}

en_skt_ret_t cli_udpskt_send(str_udpskt_id_t *pskt_id, void *psend_buf, \
		int send_buf_len, u_int32_t dest_ip, u_int16_t dest_port, \
		u_int32_t *p_sent_dat_len) {

	struct sockaddr_in receiver_addr;
	int32_t num_byte;

	receiver_addr.sin_family = AF_INET;
	receiver_addr.sin_port = htons(dest_port);
	receiver_addr.sin_addr.s_addr = dest_ip;
	memset(&(receiver_addr.sin_zero), 0, 8);

	if ((num_byte = sendto(pskt_id->socket_fd, psend_buf, send_buf_len, 0,\
		(struct sockaddr *) &receiver_addr, sizeof(struct sockaddr))) < 0) {
		LOG_ERROR("sendto socket fail errno = %s", (char *) strerror(errno));
		return -SOCKET_RET_ERROR;
	}
	return SOCKET_RET_OK;
}

void send_udp_test_pattern(void) {
	char buf[128];
	int i = 0, ret, sent_len = -1;
	for (i = 0; i < 128; i++)
		buf[i] = i;
	LOG_DEBUG("Send test msg to %s", SERVER_IP);
	ret = cli_udpskt_send(&gcli_skt, buf, i, inet_addr(SERVER_IP), SERVER_UDP_PORT, \
		&sent_len);
	if (ret < 0) {
		LOG_ERROR("cli_udpskt_send fail");
		return;
	}
	return;
}

int main(int argc, char *argv[]) {
	int ret;
	config_log(LOGDIR, 0x1f, 3);
	/*Test Log*/
	testLog();

	// strcpy(server_ip, SERVER_IP);

	/*Open Socket*/
	ret = cli_udpskt_open(&gcli_skt, CLIENT_UDP_PORT);
	if (ret < 0) {
		LOG_ERROR("create cli_udpskt_open fail");
		return 1;
	}

	open_timer_thd();
	while(1);
	return 0;
}