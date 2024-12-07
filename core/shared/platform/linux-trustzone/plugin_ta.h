#ifndef PLUGIN_TA_H
#define PLUGIN_TA_H

/*
 * Interface with tee-supplicant plugin
 */
#define PLUGIN_UUID { 0x9dc30945, 0x39eb, 0x4af4, \
		{ 0xb9, 0xae, 0x35, 0x94, 0x3f, 0x76, 0xcf, 0xc7 } }

/* plugin cmd for files (100 - 199, with intervals) */
#define FILE_MAKE_CMD               100  // ファイルの作成
#define FILE_OPEN_CMD               110  // ファイルを開く
#define FILE_READ_CMD               120  // ファイルから読み取り
#define FILE_WRITE_CMD              130  // ファイルへの書き込み
#define FILE_CLOSE_CMD              140  // ファイルを閉じる
#define FILE_UNLINK_CMD             150  // ファイルの削除
/* plugin cmd for sockets (200 - 299, with intervals) */
#define SOCKET_CREATE_CMD           200  // ソケットの作成
#define SOCKET_BIND_CMD             210  // バインド
#define SOCKET_LISTEN_CMD           220  // リスン
#define SOCKET_ACCEPT_CMD           230  // 接続の受け入れ
#define SOCKET_CONNECT_CMD          240  // 接続の確立
#define SOCKET_SEND_CMD             250  // データの送信
#define SOCKET_RECV_CMD             260  // データの受信
#define SOCKET_SENDTO_CMD           270  // 指定先へのデータ送信
#define SOCKET_RECVFROM_CMD         280  // 指定元からのデータ受信
#define SOCKET_SETSOCKOPT_CMD       290  // ソケットオプションの設定
/* plugin cmd for semaphores (300 - 399, with intervals) */
#define SEM_OPEN_CMD                300  // セマフォのオープン
#define SEM_CLOSE_CMD               310  // セマフォのクローズ
#define SEM_WAIT_CMD                320  // セマフォの待機（待ち状態になる）
#define SEM_POST_CMD                330  // セマフォの解放（待ち状態の解除）
#define SEM_UNLINK_CMD              340  // セマフォの削除
/* plugin cmd for pipes (400 - 499, with intervals) */
#define PIPE_CREATE_CMD             400  // パイプの作成
#define PIPE_WRITE_CMD              410  // パイプへの書き込み
#define PIPE_READ_CMD               420  // パイプからの読み取り
#define PIPE_CLOSE_CMD              430  // パイプのクローズ
/* plugin cmd for shared memory (500 - 599, with intervals) */
#define SHM_OPEN_CMD                500  // 共有メモリのオープン
#define SHM_UNLINK_CMD              510  // 共有メモリの削除
#define SHM_MAP_CMD                 520  // 共有メモリのマッピング
#define SHM_UNMAP_CMD               530  // 共有メモリのアンマップ
/* plugin cmd for signals (600 - 699, with intervals) */
#define SIGNAL_SEND_CMD             600  // シグナルの送信
#define SIGNAL_WAIT_CMD             610  // シグナルの待機
#define SIGNAL_IGNORE_CMD           620  // シグナルの無視
#define SIGNAL_HANDLE_CMD           630  // シグナルハンドラの設定
/* plugin cmd for testing */
#define TEST_CMD                    999  // テスト

typedef unsigned int socklen_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
typedef long int ssize_t;

typedef union
{
  char __size[32];
  long int __align;
} sem_t;

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

#endif /* PLUGIN_TA_H */
