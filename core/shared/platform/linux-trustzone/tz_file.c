#include "platform_api_vmcore.h"

// Global output buffer that is points to the untrusted memory
static void *output_buffer;
static uint64_t output_buffer_size;

int close(int fd)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->int_param1 = fd;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_CLOSE_CMD, NULL,
                    p, sizeof(struct PluginOperationData), &out_len);
    if (tee_res)
        EMSG("invoke plugin failed close with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int closedir(DIR *dirp)
{
    EMSG("closedir is not supported.");
    return -1;
}

int fcntl(int fd, int cmd, ... /* arg */ )
{
    if (fd < 3 && cmd == F_GETFL)
    {
        return 0x8002;
    }

    EMSG("fcntl is not supported.");
    return -1;
}

int fdatasync(int fd)
{
    EMSG("fdatasync is not supported.");
    return -1;
}

DIR *fdopendir(int fd)
{
    EMSG("fdopendir is not supported.");
    return NULL;
}

int fstat(int fd, struct stat *statbuf)
{
    if (fd < 3)
    {
        statbuf->st_mode = 0x2190;
        return 0;
    }

    EMSG("fstat(fd: %d) is not supported.", fd);
    return -1;
}

int fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags)
{
    EMSG("fstatat is not supported.");
    return -1;
}

int fsync(int fd)
{
    EMSG("fsync is not supported.");
    return -1;
}

int ftruncate(int fd, off_t length)
{
    EMSG("ftruncate is not supported.");
    return -1;
}

ssize_t getrandom(void *buf, size_t buflen, unsigned int flags)
{
    EMSG("getrandom is not supported.");
    return -1;
}

int ioctl(int fd, unsigned long request, ...)
{
    EMSG("ioctl is not supported.");
    return -1;
}

int isatty(int fd)
{
    EMSG("isatty is not supported.");
    return -1;
}

int linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags)
{
    EMSG("linkat is not supported.");
    return -1;
}

off_t lseek(int fd, off_t offset, int whence)
{
    EMSG("lseek is not supported.");
    return (off_t) -1;
}

int mkdirat(int dirfd, const char *pathname, mode_t mode)
{
    EMSG("mkdirat is not supported.");
    return -1;
}

int mkfifo(const char *pathname, mode_t mode)
{
    TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

    size_t len = strlen(pathname) + 1;
	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
    p->size_t_param1 = len;
	TEE_MemMove(p->buf, pathname, p->size_t_param1);
    p->int_param1 = mode;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_MAKE_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res) {
		EMSG("invoke plugin failed mkfifo() with code 0x%x", tee_res);
	}

	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}

int open(const char *pathname, int flags, ...)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    size_t len = strlen(pathname) + 1;
    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->size_t_param1 = len;
    TEE_MemMove(p->buf, pathname, p->size_t_param1);
    p->int_param1 = flags;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_OPEN_CMD, NULL,
                    p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
    if (tee_res)
        EMSG("invoke plugin failed open with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int openat(int dirfd, const char *pathname, int flags, ...)
{
    EMSG("openat is not supported.");
    return -1;
}

int poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    EMSG("poll is not supported.");
    return -1;
}

int posix_fallocate(int fd, off_t offset, off_t len)
{
    EMSG("posix_fallocate is not supported.");
    return -1;
}

ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    EMSG("preadv is not supported.");
    return -1;
}

ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset)
{
    EMSG("pwritev is not supported.");
    return -1;
}

ssize_t read(int fd, void *buf, size_t count)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + count, 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->int_param1 = fd;
    p->size_t_param1 = count;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_READ_CMD, NULL,
                    p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
    if (tee_res)
        EMSG("invoke plugin failed read with code 0x%x", tee_res);

    TEE_MemMove(buf, p->buf, p->size_t_param1);
    ssize_t res = p->res.ssize_t_val;
    TEE_Free(p);

    return res;
}

struct dirent *readdir(DIR *dirp)
{
    EMSG("readdir is not supported.");
    return NULL;
}

ssize_t readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz)
{
    EMSG("readlinkat is not supported.");
    return -1;
}

ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
    EMSG("readv is not supported.");
    return -1;
}

char *realpath(const char *path, char *resolved_path)
{
    EMSG("realpath is not supported.");
    return NULL;
}

int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath)
{
    EMSG("renameat is not supported.");
    return -1;
}

void rewinddir(DIR *dirp)
{
    EMSG("rewinddir is not supported.");
}

int sched_yield(void)
{
    EMSG("sched_yield is not supported.");
    return -1;
}

void seekdir(DIR *dirp, long loc)
{
    EMSG("seekdir is not supported.");
}

int symlinkat(const char *target, int newdirfd, const char *linkpath)
{
    EMSG("symlinkat is not supported.");
    return -1;
}

long telldir(DIR *dirp)
{
    EMSG("telldir is not supported.");
    return -1;
}

int unlink(const char *pathname)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    size_t len = strlen(pathname) + 1;
    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->size_t_param1 = len;
    TEE_MemMove(p->buf, pathname, p->size_t_param1);

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_UNLINK_CMD, NULL,
                    p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
    if (tee_res)
        EMSG("invoke plugin failed unlink with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int unlinkat(int dirfd, const char *pathname, int flags)
{
    EMSG("unlinkat is not supported.");
    return -1;
}

ssize_t write(int fd, const void *buf, size_t count)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + count, 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->int_param1 = fd;
    p->size_t_param1 = count;
    TEE_MemMove(p->buf, buf, p->size_t_param1);

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, FILE_WRITE_CMD, NULL,
                    p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
    if (tee_res)
        EMSG("invoke plugin failed write with code 0x%x", tee_res);

    ssize_t res = p->res.ssize_t_val;
    TEE_Free(p);

    return res;
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
    if (fd == 1 || fd == 2)
    {
        int i;
    
        // Count the number of characters
        size_t nchars = 0;
        for(i = 0; i < iovcnt; i++) {
            nchars += iov[i].iov_len;
        }

        // Allocate a memory to store the assembled characters from the vector
        void *buffer = os_malloc(nchars);
        void *buffer_iter = buffer;
        
        for (i = 0; i < iovcnt; i++) {
            memcpy(buffer_iter, iov[i].iov_base, iov[i].iov_len);
            buffer_iter += iov[i].iov_len;
        }

        // Print in the secure console
        os_printf("%.*s", nchars, buffer);

        // Store the output in the shared buffer with the untrusted world
        if (output_buffer_size > nchars) {
            memcpy(output_buffer, buffer, nchars);
            output_buffer += nchars;
            output_buffer_size -= nchars;
        } else {
            EMSG("The output buffer is full!");
        }

        os_free(buffer);
        
        return nchars;
    }

    EMSG("writev is not supported.");
    return -1;
}
void vedliot_set_output_buffer(uint8_t *buffer, uint32_t buffer_size) {
    output_buffer = buffer;
    output_buffer_size = buffer_size;
}