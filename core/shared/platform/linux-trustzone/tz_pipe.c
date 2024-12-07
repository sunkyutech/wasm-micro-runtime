#include "platform_api_vmcore.h"
#include "plugin_ta.h"

int mkfifo(const char *pathname, mode_t mode)
{
    TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

    // size_t len = strlen(pathname) + 1;
	// struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	// if (!p)
	// 	return TEE_ERROR_OUT_OF_MEMORY;
    // p->size = len;
	// TEE_MemMove(p->buf, pathname, p->size);
    // // p->mode = mode;
    // p->mode = 0666;

	// TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, MAKE_CMD, NULL,
	// 				p, sizeof(struct PluginOperationData) + p->size, &out_len);
	// if (tee_res) {
	// 	EMSG("invoke plugin failed mkfifo with code 0x%x", tee_res);
	// 	TEE_Free(p);
	// }

	// ssize_t res = (ssize_t)p->res;
	// TEE_Free(p);

	// return res;
}

int open(const char *pathname, int flags, ...)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    // size_t len = strlen(pathname) + 1;
    // struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
    // if (!p)
    //     return TEE_ERROR_OUT_OF_MEMORY;
    // p->size = len;
    // TEE_MemMove(p->buf, pathname, p->size);
    // // p->oflag = flags;
    // p->oflag = 2;

    // TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, OPEN_CMD, NULL,
    //                 p, sizeof(struct PluginOperationData) + p->size, &out_len);
    // if (tee_res) {
    //     EMSG("invoke plugin failed open with code 0x%x", tee_res);
    //     TEE_Free(p);
    // }
    // // IMSG("p->res: %d", p->res);

    // int res = (int)p->res;
    // TEE_Free(p);

    // return res;
}

int close(int fd)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    // struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
    // if (!p)
    //     return TEE_ERROR_OUT_OF_MEMORY;
    // p->fd = fd;

    // TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, CLOSE_CMD, NULL,
    //                 p, sizeof(struct PluginOperationData), &out_len);
    // if (tee_res) {
    //     EMSG("invoke plugin failed close with code 0x%x", tee_res);
    //     TEE_Free(p);
    // }

    // int res = (int)p->res;
    // TEE_Free(p);

    // return res;
}

ssize_t read(int fd, void *buf, size_t count)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;
    // IMSG("read fd: %d, count: %d", fd, count);

    // struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + count, 0);
    // if (!p)
    //     return TEE_ERROR_OUT_OF_MEMORY;
    // p->fd = fd;
    // p->size = count;

    // TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, READ_CMD, NULL,
    //                 p, sizeof(struct PluginOperationData) + p->size, &out_len);
    // if (tee_res) {
    //     EMSG("invoke plugin failed read with code 0x%x", tee_res);
    //     TEE_Free(p);
    // }

    // TEE_MemMove(buf, p->buf, p->size);
    // ssize_t res = (ssize_t)p->res;
    // TEE_Free(p);

    // return res;
}

ssize_t write(int fd, const void *buf, size_t count)
{
    TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;
    // IMSG("write fd: %d, count: %d", fd, count);

	// struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + count, 0);
	// if (!p)
	// 	return TEE_ERROR_OUT_OF_MEMORY;
    // p->fd = fd;
    // p->size = count;
	// TEE_MemMove(p->buf, buf, p->size);

	// TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, WRITE_CMD, NULL,
	// 				p, sizeof(struct PluginOperationData) + p->size, &out_len);
	// if (tee_res) {
	// 	EMSG("invoke plugin failed write with code 0x%x", tee_res);
	// 	TEE_Free(p);
	// }

	// ssize_t res = (ssize_t)p->res;
	// TEE_Free(p);

	// return res;
}
