/*
* @Author: vutt6
* @Date:   2018-10-10 17:05:30
* @Last Modified by:   vutt6
* @Last Modified time: 2018-10-11 15:08:55
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lib/logger.h"

#define LOGDIR "./lightSensor.log"

typedef _StrUdpSocketID {
	int socket_fd;
	struct sockaddr_in socket_addr;
	int8_t socket_isOpen;
} StrUdpSocketID;

typedef enum {
	SOCKET_RET_OK,
	SOCKET_RET_ERROR
} EnSocketRet;

pthread_t tid_timer; /*For timer thread*/
StrUdpSocketID clienSocket;

void testLog() {
	LOG_WARN("LOG_WARN");
	LOG_DEBUG("LOG_DEBUG");
	LOG_INFO("LOG_INFO");
	LOG_ERROR("LOG_ERROR");
	LOG_FATAL("LOG_FATAL");
}

void *timer_check(void *p) {
	while (1) {
		LOG_INFO("Test timer thread");
		sleep(1);
	}
}

void openTimerThread(void) {
	pthread_attr_t pthread_attr;
	pthread_attr_init(&pthread_attr); 
	pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&tid_timer, &pthread_attr, &timer_check, NULL) != 0) {
		LOG_ERROR("Create timer_check thread fail");
	}
	pthread_attr_destroy(&pthread_attr);
}

int client_udpSocket_open(StrUdpSocketID *pSocketID, int16_t udpPort, \
	const int8_t *pIPAddr) {
	/*Init Socket ID*/
	pSocketID->socket_fd = -1;
	pSocketID->socket_addr.sin_family = AF_INET;
	pSocketID->socket_addr.sin_port = 0;
	pSocketID->socket_addr.sin_addr.s_addr = 0;
	pSocketID->socket_isOpen = 0;
	memset(&(pSocketID->socket_addr.sin_zero), 0, 8);

	/*Open an Socket*/
	pSocketID->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (pSocketID->socket_fd < 0) {
		LOG_ERROR("Socket open fail errno = %s", (char *) strerror(errno));
		return -SOCKET_RET_ERROR;
	}
}

int main(int argc, char *argv[]) {
	config_log(LOGDIR, 0x1f, 3);
	/*Test Log*/
	testLog();

	openTimerThread();
	while(1);
	return 0;
}