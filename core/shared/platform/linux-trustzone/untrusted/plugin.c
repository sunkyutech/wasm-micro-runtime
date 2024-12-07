#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <semaphore.h>

#include <syslog.h>

#include <tee_plugin_method.h>
#include <tee_client_api.h>


/*
 * Data structure for the plugin operation
 */
struct PluginOperationData {
	int int_param1;
	int int_param2;
	int int_param3;
	int int_param4;
	size_t size_t_param1;
	socklen_t socklen_t_param1;
	// sem_t sem_t_param1;
    uintptr_t sem_handle1;
	struct sockaddr sockaddr_param1;
	struct timespec timespec_param1;  // for experiment
	struct timespec timespec_param2;  // for experiment
	union {
        int int_val;
		ssize_t ssize_t_val;
		// sem_t *sem_t_ptr;
		uintptr_t sem_handle;
    } res;
	char buf[0];
};

/*
 * OP-TEE has access to the plugin by the UUID
 */
#define PLUGIN_UUID { 0x9dc30945, 0x39eb, 0x4af4, \
		{ 0xb9, 0xae, 0x35, 0x94, 0x3f, 0x76, 0xcf, 0xc7 } }

/* plugin cmd for files (100 - 199, with intervals) */
#define TO_FILE_MAKE           100  // ファイルの作成
#define TO_FILE_OPEN           110  // ファイルを開く
#define TO_FILE_READ           120  // ファイルから読み取り
#define TO_FILE_WRITE          130  // ファイルへの書き込み
#define TO_FILE_CLOSE          140  // ファイルを閉じる
#define TO_FILE_UNLINK         150  // ファイルの削除
/* plugin cmd for sockets (200 - 299, with intervals) */
#define TO_SOCKET_CREATE       200  // ソケットの作成
#define TO_SOCKET_BIND         210  // バインド
#define TO_SOCKET_LISTEN       220  // リスン
#define TO_SOCKET_ACCEPT       230  // 接続の受け入れ
#define TO_SOCKET_CONNECT      240  // 接続の確立
#define TO_SOCKET_SEND         250  // データの送信
#define TO_SOCKET_RECV         260  // データの受信
#define TO_SOCKET_SENDTO       270  // 指定先へのデータ送信
#define TO_SOCKET_RECVFROM     280  // 指定元からのデータ受信
#define TO_SOCKET_SETSOCKOPT   290  // ソケットオプションの設定
/* plugin cmd for semaphores (300 - 399, with intervals) */
#define TO_SEM_OPEN            300  // セマフォのオープン
#define TO_SEM_CLOSE           310  // セマフォのクローズ
#define TO_SEM_WAIT            320  // セマフォの待機（待ち状態になる）
#define TO_SEM_POST            330  // セマフォの解放（待ち状態の解除）
#define TO_SEM_UNLINK          340  // セマフォの削除
/* plugin cmd for pipes (400 - 499, with intervals) */
#define TO_PIPE_CREATE         400  // パイプの作成
#define TO_PIPE_WRITE          410  // パイプへの書き込み
#define TO_PIPE_READ           420  // パイプからの読み取り
#define TO_PIPE_CLOSE          430  // パイプのクローズ
/* plugin cmd for shared memory (500 - 599, with intervals) */
#define TO_SHM_OPEN            500  // 共有メモリのオープン
#define TO_SHM_UNLINK          510  // 共有メモリの削除
#define TO_SHM_MAP             520  // 共有メモリのマッピング
#define TO_SHM_UNMAP           530  // 共有メモリのアンマップ
/* plugin cmd for signals (600 - 699, with intervals) */
#define TO_SIGNAL_SEND         600  // シグナルの送信
#define TO_SIGNAL_WAIT         610  // シグナルの待機
#define TO_SIGNAL_IGNORE       620  // シグナルの無視
#define TO_SIGNAL_HANDLE       630  // シグナルハンドラの設定
/* plugin cmd for testing */
#define TO_TEST                999  // テスト


static TEEC_Result plugin_init(void)
{
	return TEEC_SUCCESS;
}

/**
 * int mkfifo(const char *pathname, mode_t mode);
 * - Creates a named pipe (FIFO) at the given path.
 */
static TEEC_Result plugin_mkfifo(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	if (strcmp(p->buf, "/tmp/my_pipe1") == 0) {
		p->int_param2 = 111;
	} else if (strcmp(p->buf, "/tmp/my_pipe2") == 0) {
		p->int_param2 = 222;
	} else {
		p->int_param2 = 333;
	}
	p->res.int_val = mkfifo(p->buf, p->int_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int open(const char *pathname, int flags);
 * - Opens a file descriptor for the file at the given path.
 */
static TEEC_Result plugin_open(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = open(p->buf, p->int_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * ssize_t read(int fd, void *buf, size_t count);
 * - Reads up to count bytes from the file descriptor fd into the buffer starting at buf.
 */
static TEEC_Result plugin_read(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.ssize_t_val = read(p->int_param1, p->buf, p->size_t_param1);
	*out_len = sizeof(struct PluginOperationData) + p->size_t_param1;

	return TEEC_SUCCESS;
}

/**
 * ssize_t write(int fd, const void *buf, size_t count);
 * - Writes up to count bytes from the buffer starting at buf to the file descriptor fd.
 */
static TEEC_Result plugin_write(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.ssize_t_val = write(p->int_param1, p->buf, p->size_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int close(int fd);
 * - Closes the file descriptor fd.
 */
static TEEC_Result plugin_close(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = close(p->int_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int unlink(const char *pathname);
 * - Deletes a name from the filesystem.
 */
static TEEC_Result plugin_unlink(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = unlink(p->buf);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int socket(int domain, int type, int protocol);
 * - Creates an endpoint for communication and returns a file descriptor that refers to that endpoint.
 */
static TEEC_Result plugin_socket(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = socket(p->int_param1, p->int_param2, p->int_param3);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * - Assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
 */
static TEEC_Result plugin_bind(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = bind(p->int_param1, (struct sockaddr *)&p->sockaddr_param1, p->socklen_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int listen(int sockfd, int backlog);
 * - Marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests.
 */
static TEEC_Result plugin_listen(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = listen(p->int_param1, p->int_param2);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 * - Accepts a new connection on a socket.
 */
static TEEC_Result plugin_accept(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = accept(p->int_param1, (struct sockaddr *)&p->sockaddr_param1, &p->socklen_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * - Initiates a connection on a socket.
 */
static TEEC_Result plugin_connect(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = connect(p->int_param1, (struct sockaddr *)&p->sockaddr_param1, p->socklen_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * ssize_t send(int sockfd, const void *buf, size_t len, int flags);
 * - Sends a message on a socket.
 */
static TEEC_Result plugin_send(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.ssize_t_val = send(p->int_param1, p->buf, p->size_t_param1, p->int_param2);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * ssize_t recv(int sockfd, void *buf, size_t len, int flags);
 * - Receives a message from a socket.
 */
static TEEC_Result plugin_recv(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.ssize_t_val = recv(p->int_param1, p->buf, p->size_t_param1, p->int_param2);
	*out_len = sizeof(struct PluginOperationData) + p->size_t_param1;

	return TEEC_SUCCESS;
}

/**
 * ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
 * - Sends a message on a socket.
 */
static TEEC_Result plugin_sendto(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.ssize_t_val = sendto(p->int_param1, p->buf, p->size_t_param1, p->int_param2, (struct sockaddr *)&p->sockaddr_param1, p->socklen_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
 * - Receives a message from a socket.
 */
static TEEC_Result plugin_recvfrom(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.ssize_t_val = recvfrom(p->int_param1, p->buf, p->size_t_param1, p->int_param2, (struct sockaddr *)&p->sockaddr_param1, &p->socklen_t_param1);
	*out_len = sizeof(struct PluginOperationData) + p->size_t_param1;

	return TEEC_SUCCESS;
}

/**
 * int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
 * - Sets the value of the option specified by the optname argument for the socket referred to by the file descriptor sockfd.
 */
static TEEC_Result plugin_setsockopt(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;
	
	p->res.int_val = setsockopt(p->int_param1, p->int_param2, p->int_param3, p->buf, p->size_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
 * - Creates a new POSIX semaphore or opens an existing semaphore.
 */
static TEEC_Result plugin_sem_open(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	// p->res.sem_t_ptr = sem_open(p->buf, p->int_param1, p->int_param2, p->int_param3);
	// if (p->res.sem_t_ptr == SEM_FAILED) {
	// 	return TEEC_ERROR_GENERIC;
	// }
	sem_t *sem = sem_open(p->buf, p->int_param1, p->int_param2, p->int_param3);
	p->res.sem_handle = (uintptr_t)sem;
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int sem_close(sem_t *sem);
 * - Closes a named semaphore.
 */
static TEEC_Result plugin_sem_close(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = sem_close((sem_t *)(uintptr_t)p->sem_handle1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int sem_wait(sem_t *sem);
 * - Locks a semaphore.
 */
static TEEC_Result plugin_sem_wait(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = sem_wait((sem_t *)(uintptr_t)p->sem_handle1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int sem_post(sem_t *sem);
 * - Unlocks a semaphore.
 */
static TEEC_Result plugin_sem_post(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = sem_post((sem_t *)(uintptr_t)p->sem_handle1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int sem_unlink(const char *name);
 * - Removes a named semaphore.
 */
static TEEC_Result plugin_sem_unlink(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = sem_unlink(p->buf);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int pipe(int pipefd[2]);
 * - Creates a pipe, a unidirectional data channel that can be used for interprocess communication.
 */
// ToDo: pipe()の実装

/**
 * int shm_open(const char *name, int oflag, mode_t mode);
 * - Creates and opens a new, or opens an existing, POSIX shared memory object.
 */
static TEEC_Result plugin_shm_open(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = shm_open(p->buf, p->int_param1, p->int_param2);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int shm_unlink(const char *name);
 * - Removes a shared memory object.
 */
static TEEC_Result plugin_shm_unlink(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	p->res.int_val = shm_unlink(p->buf);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 * - Maps the file into memory.
 */
static TEEC_Result plugin_shm_map(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	// p->res.sem_t_val = mmap(p->buf, p->size_t_param1, p->int_param1, p->int_param2, p->int_param3, p->int_param4);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * int munmap(void *addr, size_t length);
 * - Unmaps the file from memory.
 */
static TEEC_Result plugin_shm_unmap(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	// p->res.int_val = munmap(p->buf, p->size_t_param1);
	*out_len = sizeof(struct PluginOperationData);

	return TEEC_SUCCESS;
}

/**
 * - This function is used to test the plugin, so default has nothing to do.
 */
static TEEC_Result plugin_test(void *data, size_t data_len, size_t *out_len)
{
	struct PluginOperationData *p = (struct PluginOperationData *)data;

	// Nothing to do.

	return TEEC_SUCCESS;
}

static TEEC_Result plugin_invoke(unsigned int cmd, unsigned int sub_cmd,
					void *data, size_t data_len,
					size_t *out_len)
{
	(void)out_len;

	switch (cmd) {
		/* File operations */
		case TO_FILE_MAKE:
			return plugin_mkfifo(data, data_len, out_len);
		case TO_FILE_OPEN:
			return plugin_open(data, data_len, out_len);
		case TO_FILE_READ:
			return plugin_read(data, data_len, out_len);
		case TO_FILE_WRITE:
			return plugin_write(data, data_len, out_len);
		case TO_FILE_CLOSE:
			return plugin_close(data, data_len, out_len);
		case TO_FILE_UNLINK:
			return plugin_unlink(data, data_len, out_len);

		/* Socket operations */
		case TO_SOCKET_CREATE:
			return plugin_socket(data, data_len, out_len);
		case TO_SOCKET_BIND:
			return plugin_bind(data, data_len, out_len);
		case TO_SOCKET_LISTEN:
			return plugin_listen(data, data_len, out_len);
		case TO_SOCKET_ACCEPT:
			return plugin_accept(data, data_len, out_len);
		case TO_SOCKET_CONNECT:
			return plugin_connect(data, data_len, out_len);
		case TO_SOCKET_SEND:
			return plugin_send(data, data_len, out_len);
		case TO_SOCKET_RECV:
			return plugin_recv(data, data_len, out_len);
		case TO_SOCKET_SENDTO:
			return plugin_sendto(data, data_len, out_len);
		case TO_SOCKET_RECVFROM:
			return plugin_recvfrom(data, data_len, out_len);
		case TO_SOCKET_SETSOCKOPT:
			return plugin_setsockopt(data, data_len, out_len);

		/* Semaphore operations */
		case TO_SEM_OPEN:
			return plugin_sem_open(data, data_len, out_len);
		case TO_SEM_CLOSE:
			return plugin_sem_close(data, data_len, out_len);
		case TO_SEM_WAIT:
			return plugin_sem_wait(data, data_len, out_len);
		case TO_SEM_POST:
			return plugin_sem_post(data, data_len, out_len);
		case TO_SEM_UNLINK:
			return plugin_sem_unlink(data, data_len, out_len);

		/* Pipe operations */
		case TO_PIPE_CREATE:
			return plugin_pipe_create(data, data_len, out_len);
		case TO_PIPE_WRITE:
			return plugin_pipe_write(data, data_len, out_len);
		case TO_PIPE_READ:
			return plugin_pipe_read(data, data_len, out_len);
		case TO_PIPE_CLOSE:
			return plugin_pipe_close(data, data_len, out_len);

		/* Shared memory operations */
		case TO_SHM_OPEN:
			return plugin_shm_open(data, data_len, out_len);
		case TO_SHM_UNLINK:
			return plugin_shm_unlink(data, data_len, out_len);
		case TO_SHM_MAP:
			return plugin_shm_map(data, data_len, out_len);
		case TO_SHM_UNMAP:
			return plugin_shm_unmap(data, data_len, out_len);

		/* Signal operations */
		case TO_SIGNAL_SEND:
			return plugin_signal_send(data, data_len, out_len);
		case TO_SIGNAL_WAIT:
			return plugin_signal_wait(data, data_len, out_len);
		case TO_SIGNAL_IGNORE:
			return plugin_signal_ignore(data, data_len, out_len);
		case TO_SIGNAL_HANDLE:
			return plugin_signal_handle(data, data_len, out_len);

		/* Test command */
		case TO_TEST:
			return plugin_test(data, data_len, out_len);
		
		/* Default */
		default:
			break;
	}
	return TEEC_ERROR_NOT_SUPPORTED;
}

struct plugin_method plugin_method = {
	"shadow_process",
	PLUGIN_UUID,
	plugin_init, /* can be NULL */
	plugin_invoke,
};
