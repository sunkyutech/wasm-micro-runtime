#ifndef _TZ_PIPE_H
#define _TZ_PIPE_H

#ifdef __cplusplus
extern "C" {
#endif

#define O_RDONLY  00
#define O_WRONLY  01
#define O_RDWR    02

/*
 * Interface with tee-supplicant plugin
 */
#define PLUGIN_UUID { 0x9dc30945, 0x39eb, 0x4af4, \
		{ 0xb9, 0xae, 0x35, 0x94, 0x3f, 0x76, 0xcf, 0xc7 } }
#define MAKE_CMD	     0
#define OPEN_CMD	     1
#define READ_CMD	     2
#define WRITE_CMD	     3
#define CLOSE_CMD	     4
#define SOCKET_CMD	     5
#define UNLINK_CMD	     6
#define BIND_CMD	     7
#define LISTEN_CMD	     8
#define ACCEPT_CMD	     9
#define RECV_CMD	     10
#define SEND_CMD	     11
#define CONNECT_CMD		 12

typedef unsigned int socklen_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
typedef long int ssize_t;

// struct sockaddr_un {
// 	uint16_t sun_family; 
//     char sun_path[108];
// };

struct in_addr {
	in_addr_t s_addr;
};

struct sockaddr_in {
    uint16_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};

struct sockaddr_un {
	uint16_t sun_family;
	char sun_path[108];
};

struct sockaddr {
	uint16_t sa_family;
	char sa_data[14];
};

#include "wasmtime_ssp.h"

struct PluginOperationData {
	int param1;
	int param2;
	int param3;
	int param4;
	size_t size;
	socklen_t len;
	struct sockaddr addr;
	struct timespec time1;  // for experiment
	struct timespec time2;  // for experiment
	union {
        int int_res;
		ssize_t ssize_t_res;
    } res;
	char buf[0];
};

// int mkfifo(const char *pathname, mode_t mode);
// int open(const char *pathname, int flags, ...);
// int close(int fd);
// ssize_t write(int fd, const void *buf, size_t count);
// ssize_t read(int fd, void *buf, size_t count);


#ifdef __cplusplus
}
#endif

#endif /* end of _TZ_PIPE_H */

