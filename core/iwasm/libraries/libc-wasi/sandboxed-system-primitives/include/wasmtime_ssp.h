/*
 * Part of the Wasmtime Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://github.com/bytecodealliance/wasmtime/blob/main/LICENSE for license information.
 *
 * This file declares an interface similar to WASI, but augmented to expose
 * some implementation details such as the curfds arguments that we pass
 * around to avoid storing them in TLS.
 */

#ifndef WASMTIME_SSP_H
#define WASMTIME_SSP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#ifndef _Static_assert
#define _Static_assert static_assert
#endif /* _Static_assert */

#ifndef _Alignof
#define _Alignof alignof
#endif /* _Alignof */

#ifndef _Noreturn
#define _Noreturn [[ noreturn ]]
#endif /* _Noreturn */
extern "C" {
#endif

#define __WASI_ADDRESS_FAMILY_INET4 1
#define __WASI_ADDRESS_FAMILY_UNIX 3
// #define AF_INET __WASI_ADDRESS_FAMILY_INET4
// #define AF_UNIX __WASI_ADDRESS_FAMILY_UNIX
#define AF_INET 2
#define AF_UNIX 1

/**
 * IP port number
 */
typedef uint16_t __wasi_ip_port_t;

_Static_assert(sizeof(__wasi_ip_port_t) == 2, "witx calculated size");
_Static_assert(_Alignof(__wasi_ip_port_t) == 2, "witx calculated align");
/**
 * An IPv4 address is a 32-bit number that uniquely identifies a network interface on a machine.
 */
typedef struct __wasi_addr_ip4_t {
    uint8_t n0;
    uint8_t n1;
    uint8_t h0;
    uint8_t h1;
} __wasi_addr_ip4_t;

_Static_assert(sizeof(__wasi_addr_ip4_t) == 4, "witx calculated size");
_Static_assert(_Alignof(__wasi_addr_ip4_t) == 1, "witx calculated align");
_Static_assert(offsetof(__wasi_addr_ip4_t, n0) == 0, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_ip4_t, n1) == 1, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_ip4_t, h0) == 2, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_ip4_t, h1) == 3, "witx calculated offset");
/**
 * An IPv4 address with a port number
 */
typedef struct __wasi_addr_ip4_port_t {
    __wasi_ip_port_t port;
    __wasi_addr_ip4_t addr;
} __wasi_addr_ip4_port_t;

_Static_assert(sizeof(__wasi_addr_ip4_port_t) == 6, "witx calculated size");
_Static_assert(_Alignof(__wasi_addr_ip4_port_t) == 2, "witx calculated align");
_Static_assert(offsetof(__wasi_addr_ip4_port_t, port) == 0, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_ip4_port_t, addr) == 2, "witx calculated offset");
/**
 * Unix socket that is bound to no more than 107 bytes
 */
typedef struct __wasi_addr_unix_t {
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
    uint8_t b5;
    uint8_t b6;
    uint8_t b7;
    uint8_t b8;
    uint8_t b9;
    uint8_t b10;
    uint8_t b11;
    uint8_t b12;
    uint8_t b13;
    uint8_t b14;
    uint8_t b15;
    uint8_t b16;
    uint8_t b17;
    uint8_t b18;
    uint8_t b19;
    uint8_t b20;
    uint8_t b21;
    uint8_t b22;
    uint8_t b23;
    uint8_t b24;
    uint8_t b25;
    uint8_t b26;
    uint8_t b27;
    uint8_t b28;
    uint8_t b29;
    uint8_t b30;
    uint8_t b31;
    uint8_t b32;
    uint8_t b33;
    uint8_t b34;
    uint8_t b35;
    uint8_t b36;
    uint8_t b37;
    uint8_t b38;
    uint8_t b39;
    uint8_t b40;
    uint8_t b41;
    uint8_t b42;
    uint8_t b43;
    uint8_t b44;
    uint8_t b45;
    uint8_t b46;
    uint8_t b47;
    uint8_t b48;
    uint8_t b49;
    uint8_t b50;
    uint8_t b51;
    uint8_t b52;
    uint8_t b53;
    uint8_t b54;
    uint8_t b55;
    uint8_t b56;
    uint8_t b57;
    uint8_t b58;
    uint8_t b59;
    uint8_t b60;
    uint8_t b61;
    uint8_t b62;
    uint8_t b63;
    uint8_t b64;
    uint8_t b65;
    uint8_t b66;
    uint8_t b67;
    uint8_t b68;
    uint8_t b69;
    uint8_t b70;
    uint8_t b71;
    uint8_t b72;
    uint8_t b73;
    uint8_t b74;
    uint8_t b75;
    uint8_t b76;
    uint8_t b77;
    uint8_t b78;
    uint8_t b79;
    uint8_t b80;
    uint8_t b81;
    uint8_t b82;
    uint8_t b83;
    uint8_t b84;
    uint8_t b85;
    uint8_t b86;
    uint8_t b87;
    uint8_t b88;
    uint8_t b89;
    uint8_t b90;
    uint8_t b91;
    uint8_t b92;
    uint8_t b93;
    uint8_t b94;
    uint8_t b95;
    uint8_t b96;
    uint8_t b97;
    uint8_t b98;
    uint8_t b99;
    uint8_t b100;
    uint8_t b101;
    uint8_t b102;
    uint8_t b103;
    uint8_t b104;
    uint8_t b105;
    uint8_t b106;
    uint8_t b107;
} __wasi_addr_unix_t;

_Static_assert(sizeof(__wasi_addr_unix_t) == 108, "witx calculated size");
_Static_assert(_Alignof(__wasi_addr_unix_t) == 1, "witx calculated align");
_Static_assert(offsetof(__wasi_addr_unix_t, b0) == 0, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b1) == 1, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b2) == 2, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b3) == 3, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b4) == 4, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b5) == 5, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b6) == 6, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b7) == 7, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b8) == 8, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b9) == 9, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b10) == 10, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b11) == 11, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b12) == 12, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b13) == 13, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b14) == 14, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b15) == 15, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b16) == 16, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b17) == 17, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b18) == 18, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b19) == 19, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b20) == 20, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b21) == 21, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b22) == 22, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b23) == 23, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b24) == 24, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b25) == 25, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b26) == 26, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b27) == 27, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b28) == 28, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b29) == 29, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b30) == 30, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b31) == 31, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b32) == 32, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b33) == 33, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b34) == 34, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b35) == 35, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b36) == 36, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b37) == 37, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b38) == 38, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b39) == 39, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b40) == 40, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b41) == 41, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b42) == 42, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b43) == 43, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b44) == 44, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b45) == 45, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b46) == 46, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b47) == 47, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b48) == 48, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b49) == 49, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b50) == 50, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b51) == 51, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b52) == 52, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b53) == 53, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b54) == 54, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b55) == 55, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b56) == 56, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b57) == 57, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b58) == 58, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b59) == 59, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b60) == 60, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b61) == 61, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b62) == 62, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b63) == 63, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b64) == 64, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b65) == 65, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b66) == 66, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b67) == 67, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b68) == 68, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b69) == 69, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b70) == 70, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b71) == 71, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b72) == 72, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b73) == 73, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b74) == 74, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b75) == 75, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b76) == 76, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b77) == 77, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b78) == 78, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b79) == 79, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b80) == 80, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b81) == 81, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b82) == 82, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b83) == 83, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b84) == 84, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b85) == 85, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b86) == 86, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b87) == 87, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b88) == 88, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b89) == 89, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b90) == 90, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b91) == 91, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b92) == 92, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b93) == 93, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b94) == 94, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b95) == 95, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b96) == 96, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b97) == 97, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b98) == 98, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b99) == 99, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b100) == 100, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b101) == 101, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b102) == 102, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b103) == 103, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b104) == 104, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b105) == 105, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b106) == 106, "witx calculated offset");
_Static_assert(offsetof(__wasi_addr_unix_t, b107) == 107, "witx calculated offset");
/**
 * Union that makes a generic IP address and port
 */
typedef union __wasi_addr_port_u_t {
    __wasi_addr_ip4_port_t inet4;
    __wasi_addr_unix_t unix_addr;
} __wasi_addr_port_u_t;
typedef struct __wasi_addr_port_t {
    uint8_t tag;
    __wasi_addr_port_u_t u;
} __wasi_addr_port_t;

_Static_assert(sizeof(__wasi_addr_port_t) == 110, "witx calculated size");
_Static_assert(_Alignof(__wasi_addr_port_t) == 2, "witx calculated align");

typedef uint32_t socklen_t;

_Static_assert(sizeof(socklen_t) == 4, "witx calculated size");
_Static_assert(_Alignof(socklen_t) == 4, "witx calculated align");

struct my_sockaddr {
    uint16_t sa_family;  // Address family
    char sa_data[14];    // Address data
};

_Static_assert(sizeof(struct my_sockaddr) == 16, "witx calculated size");
_Static_assert(_Alignof(struct my_sockaddr) == 2, "witx calculated align");
_Static_assert(offsetof(struct my_sockaddr, sa_family) == 0, "witx calculated offset");
_Static_assert(offsetof(struct my_sockaddr, sa_data) == 2, "witx calculated offset");

typedef union {
    char __size[32];
    long int __align;
} my_sem_t;

_Static_assert(sizeof(my_sem_t) == 32, "witx calculated size");
_Static_assert(_Alignof(my_sem_t) == 8, "witx calculated align");

_Static_assert(_Alignof(int8_t) == 1, "non-wasi data layout");
_Static_assert(_Alignof(uint8_t) == 1, "non-wasi data layout");
_Static_assert(_Alignof(int16_t) == 2, "non-wasi data layout");
_Static_assert(_Alignof(uint16_t) == 2, "non-wasi data layout");
_Static_assert(_Alignof(int32_t) == 4, "non-wasi data layout");
_Static_assert(_Alignof(uint32_t) == 4, "non-wasi data layout");
#if 0
_Static_assert(_Alignof(int64_t) == 8, "non-wasi data layout");
_Static_assert(_Alignof(uint64_t) == 8, "non-wasi data layout");
#endif

typedef uint8_t __wasi_advice_t;
#define __WASI_ADVICE_NORMAL     (0)
#define __WASI_ADVICE_SEQUENTIAL (1)
#define __WASI_ADVICE_RANDOM     (2)
#define __WASI_ADVICE_WILLNEED   (3)
#define __WASI_ADVICE_DONTNEED   (4)
#define __WASI_ADVICE_NOREUSE    (5)

typedef uint32_t __wasi_clockid_t;
#define __WASI_CLOCK_REALTIME           (0)
#define __WASI_CLOCK_MONOTONIC          (1)
#define __WASI_CLOCK_PROCESS_CPUTIME_ID (2)
#define __WASI_CLOCK_THREAD_CPUTIME_ID  (3)

typedef uint64_t __wasi_device_t;

typedef uint64_t __wasi_dircookie_t;
#define __WASI_DIRCOOKIE_START (0)

typedef uint16_t __wasi_errno_t;
#define __WASI_ESUCCESS        (0)
#define __WASI_E2BIG           (1)
#define __WASI_EACCES          (2)
#define __WASI_EADDRINUSE      (3)
#define __WASI_EADDRNOTAVAIL   (4)
#define __WASI_EAFNOSUPPORT    (5)
#define __WASI_EAGAIN          (6)
#define __WASI_EALREADY        (7)
#define __WASI_EBADF           (8)
#define __WASI_EBADMSG         (9)
#define __WASI_EBUSY           (10)
#define __WASI_ECANCELED       (11)
#define __WASI_ECHILD          (12)
#define __WASI_ECONNABORTED    (13)
#define __WASI_ECONNREFUSED    (14)
#define __WASI_ECONNRESET      (15)
#define __WASI_EDEADLK         (16)
#define __WASI_EDESTADDRREQ    (17)
#define __WASI_EDOM            (18)
#define __WASI_EDQUOT          (19)
#define __WASI_EEXIST          (20)
#define __WASI_EFAULT          (21)
#define __WASI_EFBIG           (22)
#define __WASI_EHOSTUNREACH    (23)
#define __WASI_EIDRM           (24)
#define __WASI_EILSEQ          (25)
#define __WASI_EINPROGRESS     (26)
#define __WASI_EINTR           (27)
#define __WASI_EINVAL          (28)
#define __WASI_EIO             (29)
#define __WASI_EISCONN         (30)
#define __WASI_EISDIR          (31)
#define __WASI_ELOOP           (32)
#define __WASI_EMFILE          (33)
#define __WASI_EMLINK          (34)
#define __WASI_EMSGSIZE        (35)
#define __WASI_EMULTIHOP       (36)
#define __WASI_ENAMETOOLONG    (37)
#define __WASI_ENETDOWN        (38)
#define __WASI_ENETRESET       (39)
#define __WASI_ENETUNREACH     (40)
#define __WASI_ENFILE          (41)
#define __WASI_ENOBUFS         (42)
#define __WASI_ENODEV          (43)
#define __WASI_ENOENT          (44)
#define __WASI_ENOEXEC         (45)
#define __WASI_ENOLCK          (46)
#define __WASI_ENOLINK         (47)
#define __WASI_ENOMEM          (48)
#define __WASI_ENOMSG          (49)
#define __WASI_ENOPROTOOPT     (50)
#define __WASI_ENOSPC          (51)
#define __WASI_ENOSYS          (52)
#define __WASI_ENOTCONN        (53)
#define __WASI_ENOTDIR         (54)
#define __WASI_ENOTEMPTY       (55)
#define __WASI_ENOTRECOVERABLE (56)
#define __WASI_ENOTSOCK        (57)
#define __WASI_ENOTSUP         (58)
#define __WASI_ENOTTY          (59)
#define __WASI_ENXIO           (60)
#define __WASI_EOVERFLOW       (61)
#define __WASI_EOWNERDEAD      (62)
#define __WASI_EPERM           (63)
#define __WASI_EPIPE           (64)
#define __WASI_EPROTO          (65)
#define __WASI_EPROTONOSUPPORT (66)
#define __WASI_EPROTOTYPE      (67)
#define __WASI_ERANGE          (68)
#define __WASI_EROFS           (69)
#define __WASI_ESPIPE          (70)
#define __WASI_ESRCH           (71)
#define __WASI_ESTALE          (72)
#define __WASI_ETIMEDOUT       (73)
#define __WASI_ETXTBSY         (74)
#define __WASI_EXDEV           (75)
#define __WASI_ENOTCAPABLE     (76)

typedef uint16_t __wasi_eventrwflags_t;
#define __WASI_EVENT_FD_READWRITE_HANGUP (0x0001)

typedef uint8_t __wasi_eventtype_t;
#define __WASI_EVENTTYPE_CLOCK          (0)
#define __WASI_EVENTTYPE_FD_READ        (1)
#define __WASI_EVENTTYPE_FD_WRITE       (2)

typedef uint32_t __wasi_exitcode_t;

typedef uint32_t __wasi_fd_t;

typedef uint16_t __wasi_fdflags_t;
#define __WASI_FDFLAG_APPEND   (0x0001)
#define __WASI_FDFLAG_DSYNC    (0x0002)
#define __WASI_FDFLAG_NONBLOCK (0x0004)
#define __WASI_FDFLAG_RSYNC    (0x0008)
#define __WASI_FDFLAG_SYNC     (0x0010)

typedef int64_t __wasi_filedelta_t;

typedef uint64_t __wasi_filesize_t;

typedef uint8_t __wasi_filetype_t;
#define __WASI_FILETYPE_UNKNOWN          (0)
#define __WASI_FILETYPE_BLOCK_DEVICE     (1)
#define __WASI_FILETYPE_CHARACTER_DEVICE (2)
#define __WASI_FILETYPE_DIRECTORY        (3)
#define __WASI_FILETYPE_REGULAR_FILE     (4)
#define __WASI_FILETYPE_SOCKET_DGRAM     (5)
#define __WASI_FILETYPE_SOCKET_STREAM    (6)
#define __WASI_FILETYPE_SYMBOLIC_LINK    (7)

typedef uint16_t __wasi_fstflags_t;
#define __WASI_FILESTAT_SET_ATIM     (0x0001)
#define __WASI_FILESTAT_SET_ATIM_NOW (0x0002)
#define __WASI_FILESTAT_SET_MTIM     (0x0004)
#define __WASI_FILESTAT_SET_MTIM_NOW (0x0008)

typedef uint64_t __wasi_inode_t;

typedef uint32_t __wasi_linkcount_t;

typedef uint32_t __wasi_lookupflags_t;
#define __WASI_LOOKUP_SYMLINK_FOLLOW (0x00000001)

typedef uint16_t __wasi_oflags_t;
#define __WASI_O_CREAT     (0x0001)
#define __WASI_O_DIRECTORY (0x0002)
#define __WASI_O_EXCL      (0x0004)
#define __WASI_O_TRUNC     (0x0008)

typedef uint16_t __wasi_riflags_t;
#define __WASI_SOCK_RECV_PEEK    (0x0001)
#define __WASI_SOCK_RECV_WAITALL (0x0002)

typedef uint64_t __wasi_rights_t;
#define __WASI_RIGHT_FD_DATASYNC             (0x0000000000000001)
#define __WASI_RIGHT_FD_READ                 (0x0000000000000002)
#define __WASI_RIGHT_FD_SEEK                 (0x0000000000000004)
#define __WASI_RIGHT_FD_FDSTAT_SET_FLAGS     (0x0000000000000008)
#define __WASI_RIGHT_FD_SYNC                 (0x0000000000000010)
#define __WASI_RIGHT_FD_TELL                 (0x0000000000000020)
#define __WASI_RIGHT_FD_WRITE                (0x0000000000000040)
#define __WASI_RIGHT_FD_ADVISE               (0x0000000000000080)
#define __WASI_RIGHT_FD_ALLOCATE             (0x0000000000000100)
#define __WASI_RIGHT_PATH_CREATE_DIRECTORY   (0x0000000000000200)
#define __WASI_RIGHT_PATH_CREATE_FILE        (0x0000000000000400)
#define __WASI_RIGHT_PATH_LINK_SOURCE        (0x0000000000000800)
#define __WASI_RIGHT_PATH_LINK_TARGET        (0x0000000000001000)
#define __WASI_RIGHT_PATH_OPEN               (0x0000000000002000)
#define __WASI_RIGHT_FD_READDIR              (0x0000000000004000)
#define __WASI_RIGHT_PATH_READLINK           (0x0000000000008000)
#define __WASI_RIGHT_PATH_RENAME_SOURCE      (0x0000000000010000)
#define __WASI_RIGHT_PATH_RENAME_TARGET      (0x0000000000020000)
#define __WASI_RIGHT_PATH_FILESTAT_GET       (0x0000000000040000)
#define __WASI_RIGHT_PATH_FILESTAT_SET_SIZE  (0x0000000000080000)
#define __WASI_RIGHT_PATH_FILESTAT_SET_TIMES (0x0000000000100000)
#define __WASI_RIGHT_FD_FILESTAT_GET         (0x0000000000200000)
#define __WASI_RIGHT_FD_FILESTAT_SET_SIZE    (0x0000000000400000)
#define __WASI_RIGHT_FD_FILESTAT_SET_TIMES   (0x0000000000800000)
#define __WASI_RIGHT_PATH_SYMLINK            (0x0000000001000000)
#define __WASI_RIGHT_PATH_REMOVE_DIRECTORY   (0x0000000002000000)
#define __WASI_RIGHT_PATH_UNLINK_FILE        (0x0000000004000000)
#define __WASI_RIGHT_POLL_FD_READWRITE       (0x0000000008000000)
#define __WASI_RIGHT_SOCK_SHUTDOWN           (0x0000000010000000)

typedef uint16_t __wasi_roflags_t;
#define __WASI_SOCK_RECV_DATA_TRUNCATED (0x0001)

typedef uint8_t __wasi_sdflags_t;
#define __WASI_SHUT_RD (0x01)
#define __WASI_SHUT_WR (0x02)

typedef uint16_t __wasi_siflags_t;

typedef uint8_t __wasi_signal_t;
// 0 is reserved; POSIX has special semantics for kill(pid, 0).
#define __WASI_SIGHUP    (1)
#define __WASI_SIGINT    (2)
#define __WASI_SIGQUIT   (3)
#define __WASI_SIGILL    (4)
#define __WASI_SIGTRAP   (5)
#define __WASI_SIGABRT   (6)
#define __WASI_SIGBUS    (7)
#define __WASI_SIGFPE    (8)
#define __WASI_SIGKILL   (9)
#define __WASI_SIGUSR1   (10)
#define __WASI_SIGSEGV   (11)
#define __WASI_SIGUSR2   (12)
#define __WASI_SIGPIPE   (13)
#define __WASI_SIGALRM   (14)
#define __WASI_SIGTERM   (15)
#define __WASI_SIGCHLD   (16)
#define __WASI_SIGCONT   (17)
#define __WASI_SIGSTOP   (18)
#define __WASI_SIGTSTP   (19)
#define __WASI_SIGTTIN   (20)
#define __WASI_SIGTTOU   (21)
#define __WASI_SIGURG    (22)
#define __WASI_SIGXCPU   (23)
#define __WASI_SIGXFSZ   (24)
#define __WASI_SIGVTALRM (25)
#define __WASI_SIGPROF   (26)
#define __WASI_SIGWINCH  (27)
#define __WASI_SIGPOLL   (28)
#define __WASI_SIGPWR    (29)
#define __WASI_SIGSYS    (30)

typedef uint16_t __wasi_subclockflags_t;
#define __WASI_SUBSCRIPTION_CLOCK_ABSTIME (0x0001)

typedef uint64_t __wasi_timestamp_t;

typedef uint64_t __wasi_userdata_t;

typedef uint8_t __wasi_whence_t;
#define __WASI_WHENCE_SET (0)
#define __WASI_WHENCE_CUR (1)
#define __WASI_WHENCE_END (2)

typedef uint8_t __wasi_preopentype_t;
#define __WASI_PREOPENTYPE_DIR              (0)

struct fd_table;
struct fd_prestats;
struct argv_environ_values;

typedef struct __wasi_dirent_t {
    __wasi_dircookie_t d_next;
    __wasi_inode_t d_ino;
    uint32_t d_namlen;
    __wasi_filetype_t d_type;
} __wasi_dirent_t __attribute__((aligned(8)));
_Static_assert(offsetof(__wasi_dirent_t, d_next) == 0, "non-wasi data layout");
_Static_assert(offsetof(__wasi_dirent_t, d_ino) == 8, "non-wasi data layout");
_Static_assert(offsetof(__wasi_dirent_t, d_namlen) == 16, "non-wasi data layout");
_Static_assert(offsetof(__wasi_dirent_t, d_type) == 20, "non-wasi data layout");
_Static_assert(sizeof(__wasi_dirent_t) == 24, "non-wasi data layout");
_Static_assert(_Alignof(__wasi_dirent_t) == 8, "non-wasi data layout");

typedef struct __wasi_event_t {
    __wasi_userdata_t userdata;
    __wasi_errno_t error;
    __wasi_eventtype_t type;
    uint8_t __paddings[5];
    union __wasi_event_u {
        struct __wasi_event_u_fd_readwrite_t {
            __wasi_filesize_t nbytes;
            __wasi_eventrwflags_t flags;
            uint8_t __paddings[6];
        } fd_readwrite;
    } u;
} __wasi_event_t __attribute__((aligned(8)));
_Static_assert(offsetof(__wasi_event_t, userdata) == 0, "non-wasi data layout");
_Static_assert(offsetof(__wasi_event_t, error) == 8, "non-wasi data layout");
_Static_assert(offsetof(__wasi_event_t, type) == 10, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_event_t, u.fd_readwrite.nbytes) == 16, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_event_t, u.fd_readwrite.flags) == 24, "non-wasi data layout");
_Static_assert(sizeof(__wasi_event_t) == 32, "non-wasi data layout");
_Static_assert(_Alignof(__wasi_event_t) == 8, "non-wasi data layout");

typedef struct __wasi_prestat_t {
    __wasi_preopentype_t pr_type;
    union __wasi_prestat_u {
        struct __wasi_prestat_u_dir_t {
            size_t pr_name_len;
        } dir;
    } u;
} __wasi_prestat_t;
_Static_assert(offsetof(__wasi_prestat_t, pr_type) == 0, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    offsetof(__wasi_prestat_t, u.dir.pr_name_len) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    offsetof(__wasi_prestat_t, u.dir.pr_name_len) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    sizeof(__wasi_prestat_t) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    sizeof(__wasi_prestat_t) == 16, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    _Alignof(__wasi_prestat_t) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    _Alignof(__wasi_prestat_t) == 8, "non-wasi data layout");

typedef struct __wasi_fdstat_t {
    __wasi_filetype_t fs_filetype;
    __wasi_fdflags_t fs_flags;
    uint8_t __paddings[4];
    __wasi_rights_t fs_rights_base;
    __wasi_rights_t fs_rights_inheriting;
} __wasi_fdstat_t __attribute__((aligned(8)));
_Static_assert(
    offsetof(__wasi_fdstat_t, fs_filetype) == 0, "non-wasi data layout");
_Static_assert(offsetof(__wasi_fdstat_t, fs_flags) == 2, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_fdstat_t, fs_rights_base) == 8, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_fdstat_t, fs_rights_inheriting) == 16,
    "non-wasi data layout");
_Static_assert(sizeof(__wasi_fdstat_t) == 24, "non-wasi data layout");
_Static_assert(_Alignof(__wasi_fdstat_t) == 8, "non-wasi data layout");

typedef struct __wasi_filestat_t {
    __wasi_device_t st_dev;
    __wasi_inode_t st_ino;
    __wasi_filetype_t st_filetype;
    __wasi_linkcount_t st_nlink;
    __wasi_filesize_t st_size;
    __wasi_timestamp_t st_atim;
    __wasi_timestamp_t st_mtim;
    __wasi_timestamp_t st_ctim;
} __wasi_filestat_t __attribute__((aligned(8)));
_Static_assert(offsetof(__wasi_filestat_t, st_dev) == 0, "non-wasi data layout");
_Static_assert(offsetof(__wasi_filestat_t, st_ino) == 8, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_filetype) == 16, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_nlink) == 20, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_size) == 24, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_atim) == 32, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_mtim) == 40, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_filestat_t, st_ctim) == 48, "non-wasi data layout");
_Static_assert(sizeof(__wasi_filestat_t) == 56, "non-wasi data layout");
_Static_assert(_Alignof(__wasi_filestat_t) == 8, "non-wasi data layout");

typedef struct __wasi_ciovec_t {
    const void *buf;
    size_t buf_len;
} __wasi_ciovec_t;
_Static_assert(offsetof(__wasi_ciovec_t, buf) == 0, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    offsetof(__wasi_ciovec_t, buf_len) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    offsetof(__wasi_ciovec_t, buf_len) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    sizeof(__wasi_ciovec_t) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    sizeof(__wasi_ciovec_t) == 16, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    _Alignof(__wasi_ciovec_t) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    _Alignof(__wasi_ciovec_t) == 8, "non-wasi data layout");

typedef struct __wasi_iovec_t {
    void *buf;
    size_t buf_len;
} __wasi_iovec_t;
_Static_assert(offsetof(__wasi_iovec_t, buf) == 0, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    offsetof(__wasi_iovec_t, buf_len) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    offsetof(__wasi_iovec_t, buf_len) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    sizeof(__wasi_iovec_t) == 8, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    sizeof(__wasi_iovec_t) == 16, "non-wasi data layout");
_Static_assert(sizeof(void *) != 4 ||
    _Alignof(__wasi_iovec_t) == 4, "non-wasi data layout");
_Static_assert(sizeof(void *) != 8 ||
    _Alignof(__wasi_iovec_t) == 8, "non-wasi data layout");

typedef struct __wasi_subscription_t {
    __wasi_userdata_t userdata;
    __wasi_eventtype_t type;
    uint8_t __paddings[7];
    union __wasi_subscription_u {
        struct __wasi_subscription_u_clock_t {
            __wasi_userdata_t identifier;
            __wasi_clockid_t clock_id;
            uint8_t __paddings1[4];
            __wasi_timestamp_t timeout;
            __wasi_timestamp_t precision;
            __wasi_subclockflags_t flags;
            uint8_t __paddings2[6];
        } clock;
        struct __wasi_subscription_u_fd_readwrite_t {
            __wasi_fd_t fd;
        } fd_readwrite;
    } u;
} __wasi_subscription_t __attribute__((aligned(8)));
_Static_assert(
    offsetof(__wasi_subscription_t, userdata) == 0, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, type) == 8, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.clock.identifier) == 16,
    "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.clock.clock_id) == 24,
    "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.clock.timeout) == 32, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.clock.precision) == 40,
    "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.clock.flags) == 48, "non-wasi data layout");
_Static_assert(
    offsetof(__wasi_subscription_t, u.fd_readwrite.fd) == 16,
    "non-wasi data layout");
_Static_assert(sizeof(__wasi_subscription_t) == 56, "non-wasi data layout");
_Static_assert(_Alignof(__wasi_subscription_t) == 8, "non-wasi data layout");

#if defined(WASMTIME_SSP_WASI_API)
#define WASMTIME_SSP_SYSCALL_NAME(name) \
    asm("__wasi_" #name)
#else
#define WASMTIME_SSP_SYSCALL_NAME(name)
#endif

__wasi_errno_t wasmtime_ssp_args_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct argv_environ_values *arg_environ,
#endif
    char **argv,
    char *argv_buf
) WASMTIME_SSP_SYSCALL_NAME(args_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_args_sizes_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct argv_environ_values *arg_environ,
#endif
    size_t *argc,
    size_t *argv_buf_size
) WASMTIME_SSP_SYSCALL_NAME(args_sizes_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_clock_res_get(
    __wasi_clockid_t clock_id,
    __wasi_timestamp_t *resolution
) WASMTIME_SSP_SYSCALL_NAME(clock_res_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_clock_time_get(
    __wasi_clockid_t clock_id,
    __wasi_timestamp_t precision,
    __wasi_timestamp_t *time
) WASMTIME_SSP_SYSCALL_NAME(clock_time_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_environ_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct argv_environ_values *arg_environ,
#endif
    char **environ,
    char *environ_buf
) WASMTIME_SSP_SYSCALL_NAME(environ_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_environ_sizes_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct argv_environ_values *arg_environ,
#endif
    size_t *environ_count,
    size_t *environ_buf_size
) WASMTIME_SSP_SYSCALL_NAME(environ_sizes_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_prestat_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_prestats *prestats,
#endif
    __wasi_fd_t fd,
    __wasi_prestat_t *buf
) WASMTIME_SSP_SYSCALL_NAME(fd_prestat_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_prestat_dir_name(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_prestats *prestats,
#endif
    __wasi_fd_t fd,
    char *path,
    size_t path_len
) WASMTIME_SSP_SYSCALL_NAME(fd_prestat_dir_name) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_close(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
    struct fd_prestats *prestats,
#endif
    __wasi_fd_t fd
) WASMTIME_SSP_SYSCALL_NAME(fd_close) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_datasync(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd
) WASMTIME_SSP_SYSCALL_NAME(fd_datasync) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_pread(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const __wasi_iovec_t *iovs,
    size_t iovs_len,
    __wasi_filesize_t offset,
    size_t *nread
) WASMTIME_SSP_SYSCALL_NAME(fd_pread) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_pwrite(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const __wasi_ciovec_t *iovs,
    size_t iovs_len,
    __wasi_filesize_t offset,
    size_t *nwritten
) WASMTIME_SSP_SYSCALL_NAME(fd_pwrite) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_read(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const __wasi_iovec_t *iovs,
    size_t iovs_len,
    size_t *nread
) WASMTIME_SSP_SYSCALL_NAME(fd_read) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_renumber(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
    struct fd_prestats *prestats,
#endif
    __wasi_fd_t from,
    __wasi_fd_t to
) WASMTIME_SSP_SYSCALL_NAME(fd_renumber) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_seek(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filedelta_t offset,
    __wasi_whence_t whence,
    __wasi_filesize_t *newoffset
) WASMTIME_SSP_SYSCALL_NAME(fd_seek) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_tell(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filesize_t *newoffset
) WASMTIME_SSP_SYSCALL_NAME(fd_tell) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_fdstat_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_fdstat_t *buf
) WASMTIME_SSP_SYSCALL_NAME(fd_fdstat_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_fdstat_set_flags(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_fdflags_t flags
) WASMTIME_SSP_SYSCALL_NAME(fd_fdstat_set_flags) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_fdstat_set_rights(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_rights_t fs_rights_base,
    __wasi_rights_t fs_rights_inheriting
) WASMTIME_SSP_SYSCALL_NAME(fd_fdstat_set_rights) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_sync(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd
) WASMTIME_SSP_SYSCALL_NAME(fd_sync) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_write(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const __wasi_ciovec_t *iovs,
    size_t iovs_len,
    size_t *nwritten
) WASMTIME_SSP_SYSCALL_NAME(fd_write) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_advise(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filesize_t offset,
    __wasi_filesize_t len,
    __wasi_advice_t advice
) WASMTIME_SSP_SYSCALL_NAME(fd_advise) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_allocate(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filesize_t offset,
    __wasi_filesize_t len
) WASMTIME_SSP_SYSCALL_NAME(fd_allocate) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_create_directory(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const char *path,
    size_t path_len
) WASMTIME_SSP_SYSCALL_NAME(path_create_directory) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_link(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
    struct fd_prestats *prestats,
#endif
    __wasi_fd_t old_fd,
    __wasi_lookupflags_t old_flags,
    const char *old_path,
    size_t old_path_len,
    __wasi_fd_t new_fd,
    const char *new_path,
    size_t new_path_len
) WASMTIME_SSP_SYSCALL_NAME(path_link) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_open(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t dirfd,
    __wasi_lookupflags_t dirflags,
    const char *path,
    size_t path_len,
    __wasi_oflags_t oflags,
    __wasi_rights_t fs_rights_base,
    __wasi_rights_t fs_rights_inheriting,
    __wasi_fdflags_t fs_flags,
    __wasi_fd_t *fd
) WASMTIME_SSP_SYSCALL_NAME(path_open) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_readdir(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    void *buf,
    size_t buf_len,
    __wasi_dircookie_t cookie,
    size_t *bufused
) WASMTIME_SSP_SYSCALL_NAME(fd_readdir) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_readlink(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const char *path,
    size_t path_len,
    char *buf,
    size_t buf_len,
    size_t *bufused
) WASMTIME_SSP_SYSCALL_NAME(path_readlink) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_rename(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t old_fd,
    const char *old_path,
    size_t old_path_len,
    __wasi_fd_t new_fd,
    const char *new_path,
    size_t new_path_len
) WASMTIME_SSP_SYSCALL_NAME(path_rename) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_filestat_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filestat_t *buf
) WASMTIME_SSP_SYSCALL_NAME(fd_filestat_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_filestat_set_times(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_timestamp_t st_atim,
    __wasi_timestamp_t st_mtim,
    __wasi_fstflags_t fstflags
) WASMTIME_SSP_SYSCALL_NAME(fd_filestat_set_times) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_fd_filestat_set_size(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_filesize_t st_size
) WASMTIME_SSP_SYSCALL_NAME(fd_filestat_set_size) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_filestat_get(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_lookupflags_t flags,
    const char *path,
    size_t path_len,
    __wasi_filestat_t *buf
) WASMTIME_SSP_SYSCALL_NAME(path_filestat_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_filestat_set_times(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    __wasi_lookupflags_t flags,
    const char *path,
    size_t path_len,
    __wasi_timestamp_t st_atim,
    __wasi_timestamp_t st_mtim,
    __wasi_fstflags_t fstflags
) WASMTIME_SSP_SYSCALL_NAME(path_filestat_set_times) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_symlink(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
    struct fd_prestats *prestats,
#endif
    const char *old_path,
    size_t old_path_len,
    __wasi_fd_t fd,
    const char *new_path,
    size_t new_path_len
) WASMTIME_SSP_SYSCALL_NAME(path_symlink) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_unlink_file(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const char *path,
    size_t path_len
) WASMTIME_SSP_SYSCALL_NAME(path_unlink_file) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_path_remove_directory(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t fd,
    const char *path,
    size_t path_len
) WASMTIME_SSP_SYSCALL_NAME(path_remove_directory) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_poll_oneoff(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    const __wasi_subscription_t *in,
    __wasi_event_t *out,
    size_t nsubscriptions,
    size_t *nevents
) WASMTIME_SSP_SYSCALL_NAME(poll_oneoff) __attribute__((__warn_unused_result__));

#if 0
/**
 * We throw exception in libc-wasi wrapper function wasi_proc_exit()
 * but not call this function.
 */
_Noreturn void wasmtime_ssp_proc_exit(
    __wasi_exitcode_t rval
) WASMTIME_SSP_SYSCALL_NAME(proc_exit);
#endif

__wasi_errno_t wasmtime_ssp_proc_raise(
    __wasi_signal_t sig
) WASMTIME_SSP_SYSCALL_NAME(proc_raise) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_random_get(
    void *buf,
    size_t buf_len
) WASMTIME_SSP_SYSCALL_NAME(random_get) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_recv(
// #if !defined(WASMTIME_SSP_STATIC_CURFDS)
//     struct fd_table *curfds,
// #endif
    int sockfd,
    void *buf,
    size_t len,
    int flags
) WASMTIME_SSP_SYSCALL_NAME(sock_recv) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_recvfrom(
    int sockfd,
    void *buf,
    size_t len,
    int flags,
    struct sockaddr *src_addr,
    socklen_t *addrlen
) WASMTIME_SSP_SYSCALL_NAME(sock_recvfrom) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_send(
// #if !defined(WASMTIME_SSP_STATIC_CURFDS)
//     struct fd_table *curfds,
// #endif
    int sockfd,
    const void *buf,
    size_t len,
    int flags
) WASMTIME_SSP_SYSCALL_NAME(sock_send) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_sendto(
    int sockfd,
    const void *buf,
    size_t len,
    int flags,
    const struct sockaddr *dest_addr,
    socklen_t addrlen
) WASMTIME_SSP_SYSCALL_NAME(sock_sendto) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_open(
    int domain,
    int type,
    int protocol
) WASMTIME_SSP_SYSCALL_NAME(sock_open) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_bind(
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen
) WASMTIME_SSP_SYSCALL_NAME(sock_bind) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_listen(
    int sockfd,
    int backlog
) WASMTIME_SSP_SYSCALL_NAME(sock_listen) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_accept(
    int sockfd,
    struct sockaddr *addr,
    socklen_t *addrlen
) WASMTIME_SSP_SYSCALL_NAME(sock_accept) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_connect(
    int sockfd,
    const struct sockaddr *addr,
    socklen_t addrlen
) WASMTIME_SSP_SYSCALL_NAME(sock_connect) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_mkfifo(
    const char *path,
    int mode
) WASMTIME_SSP_SYSCALL_NAME(mkfifo) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_open(
    const char *path,
    int oflag
) WASMTIME_SSP_SYSCALL_NAME(open) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_close(
    int fd
) WASMTIME_SSP_SYSCALL_NAME(close) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_read(
    int fd,
    void *buf,
    size_t count
) WASMTIME_SSP_SYSCALL_NAME(read) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_write(
    int fd,
    const void *buf,
    size_t count
) WASMTIME_SSP_SYSCALL_NAME(write) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sem_open(
    const char *name,
    int oflag,
    int mode,
    unsigned int value,
    my_sem_t *sem
) WASMTIME_SSP_SYSCALL_NAME(sem_open) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sem_close(
    my_sem_t *sem
) WASMTIME_SSP_SYSCALL_NAME(sem_close) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sem_post(
    my_sem_t *sem
) WASMTIME_SSP_SYSCALL_NAME(sem_post) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sem_wait(
    my_sem_t *sem
) WASMTIME_SSP_SYSCALL_NAME(sem_wait) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sem_unlink(
    const char *name
) WASMTIME_SSP_SYSCALL_NAME(sem_unlink) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sock_shutdown(
#if !defined(WASMTIME_SSP_STATIC_CURFDS)
    struct fd_table *curfds,
#endif
    __wasi_fd_t sock,
    __wasi_sdflags_t how
) WASMTIME_SSP_SYSCALL_NAME(sock_shutdown) __attribute__((__warn_unused_result__));

__wasi_errno_t wasmtime_ssp_sched_yield(void)
    WASMTIME_SSP_SYSCALL_NAME(sched_yield) __attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif

#undef WASMTIME_SSP_SYSCALL_NAME

#endif

