#include "platform_api_vmcore.h"

uint16 htonl(uint16 hostlong)
{
	return ((hostlong & 0xff00) >> 8) | ((hostlong & 0x00ff) << 8);
}

uint16_t htons(uint16_t hostshort)
{
    return ((hostshort & 0xff00) >> 8) | ((hostshort & 0x00ff) << 8);
}

uint16_t ntohs(uint16_t netshort)
{
	return ((netshort & 0xff00) >> 8) | ((netshort & 0x00ff) << 8);
}

char *inet_ntoa(struct in_addr in)
{
	static char buf[16];
	unsigned char *a = (void *)&in;
	snprintf(buf, sizeof buf, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
	return buf;
}

int accept(int fd, struct sockaddr *addr, socklen_t *addr_len)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = fd;
	TEE_MemMove(&p->sockaddr_param1, addr, sizeof(struct sockaddr));
	TEE_MemMove(&p->socklen_t_param1, addr_len, sizeof(socklen_t));

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_ACCEPT_CMD, NULL,
					p, sizeof(struct PluginOperationData), &out_len);
	if (tee_res)
		EMSG("invoke plugin failed accept with code 0x%x", tee_res);

	TEE_MemMove(addr, &p->sockaddr_param1, sizeof(struct sockaddr));
	TEE_MemMove(addr_len, &p->socklen_t_param1, sizeof(socklen_t));

	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}

int bind(int fd, const struct sockaddr *addr, socklen_t addr_len)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = fd;
	TEE_MemMove(&p->sockaddr_param1, addr, sizeof(struct sockaddr));
	p->socklen_t_param1 = addr_len;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_BIND_CMD, NULL,
					p, sizeof(struct PluginOperationData), &out_len);
	if (tee_res)
		EMSG("invoke plugin failed bind with code 0x%x", tee_res);
	
	TEE_MemMove(addr, &p->sockaddr_param1, sizeof(struct sockaddr));

	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}

int connect(int fd, const struct sockaddr *addr, socklen_t len)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = fd;
	TEE_MemMove(&p->sockaddr_param1, addr, sizeof(struct sockaddr));
	p->socklen_t_param1 = len;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_CONNECT_CMD, NULL,
					p, sizeof(struct PluginOperationData), &out_len);
	if (tee_res)
		EMSG("invoke plugin failed connect with code 0x%x", tee_res);

	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
    EMSG("getsockopt is not supported.");
    return -1;
}

int listen(int fd, int n)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = fd;
	p->int_param2 = n;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_LISTEN_CMD, NULL,
					p, sizeof(struct PluginOperationData), &out_len);
	if (tee_res)
		EMSG("invoke plugin failed listen with code 0x%x", tee_res);
	
	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = sockfd;
	TEE_MemMove(p->buf, buf, len);
	p->size_t_param1 = len;
	p->int_param2 = flags;
	
	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_RECV_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res)
		EMSG("invoke plugin failed recv with code 0x%x", tee_res);

	TEE_MemMove(buf, p->buf, p->size_t_param1);
	ssize_t res = p->res.ssize_t_val;
	TEE_Free(p);
	
	return res;
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = sockfd;
	TEE_MemMove(p->buf, buf, len);
	p->size_t_param1 = len;
	p->int_param2 = flags;
	TEE_MemMove(&p->sockaddr_param1, src_addr, sizeof(struct sockaddr));
	TEE_MemMove(&p->socklen_t_param1, addrlen, sizeof(socklen_t));

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_RECVFROM_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res)
		EMSG("invoke plugin failed recvfrom with code 0x%x", tee_res);

	TEE_MemMove(buf, p->buf, p->size_t_param1);
	TEE_MemMove(src_addr, &p->sockaddr_param1, sizeof(struct sockaddr));
	TEE_MemMove(addrlen, &p->socklen_t_param1, sizeof(socklen_t));
	ssize_t res = p->res.ssize_t_val;
	TEE_Free(p);

	return res;
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)
{
    EMSG("recvmsg is not supported.");
	return -1;
}

ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = sockfd;
	TEE_MemMove(p->buf, buf, len);
	p->size_t_param1 = len;
	p->int_param2 = flags;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_SEND_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res)
		EMSG("invoke plugin failed send with code 0x%x", tee_res);

	ssize_t res = p->res.ssize_t_val;
	TEE_Free(p);

	return res;
}

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
    EMSG("sendmsg is not supported.");
	return -1;
}

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
	TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = sockfd;
	TEE_MemMove(p->buf, buf, len);
	p->size_t_param1 = len;
	p->int_param2 = flags;
	TEE_MemMove(&p->sockaddr_param1, dest_addr, sizeof(struct sockaddr));
	p->socklen_t_param1 = addrlen;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_SENDTO_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res)
		EMSG("invoke plugin failed sendto with code 0x%x", tee_res);

	ssize_t res = p->res.ssize_t_val;
	TEE_Free(p);

	return res;
}

int shutdown(int sockfd, int how)
{
    EMSG("shutdown is not supported.");
    return -1;
}

int socket(int domain, int type, int protocol)
{
    TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;

	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
	if (!p)
		return TEE_ERROR_OUT_OF_MEMORY;
	p->int_param1 = domain;
	p->int_param2 = type;
	p->int_param3 = protocol;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SOCKET_CREATE_CMD, NULL,
					p, sizeof(struct PluginOperationData), &out_len);
	if (tee_res)
		EMSG("invoke plugin failed socket with code 0x%x", tee_res);

	int res = p->res.int_val;
	TEE_Free(p);

	return res;
}
