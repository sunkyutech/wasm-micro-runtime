#include "platform_api_vmcore.h"

/*
 * Errno APIs
 */

static int global_errno;

/*
 * Errno is not bound to a thread.
 */
int* __errno_location(void)
{
    return &global_errno;
}


/*
 * Cond APIs
 */
int pthread_cond_destroy(pthread_cond_t *cond)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_cond_init(pthread_cond_t *cond, const void *attr)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_cond_signal(pthread_cond_t *cond)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, uint64_t useconds)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}


/*
 * Mutex APIs
 */

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}


/* 
 * Rwlock APIs
 */

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}

int pthread_rwlock_init(pthread_rwlock_t *rwlock, void *attr)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    // TA is not multithreaded, mutexes are therefore not implemented.
    return 0;
}


/*
 * Semaphore APIs
 */

int sem_close(sem_t **sem)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->sem_handle1 = (uintptr_t)*sem;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SEM_CLOSE_CMD, NULL,
                    p, sizeof(struct PluginOperationData), &out_len);
    if (tee_res) {
        EMSG("invoke plugin failed sem_close with code 0x%x", tee_res);
    }

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int sem_open(const char *name, int oflag, int mode, unsigned int value, sem_t **sem)
{
    TEE_UUID uuid = PLUGIN_UUID;
	size_t out_len;
    int res = 0;

    size_t len = strlen(name) + 1;
	struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
	// ToDo: TEE_ERROR_OUT_OF_MEMORYはunsigned intであるが，sem_tを返す必要がある
    // if (!p)
		// return TEE_ERROR_OUT_OF_MEMORY;
    p->size_t_param1 = len;
	TEE_MemMove(p->buf, name, p->size_t_param1);
    p->int_param1 = oflag;
    p->int_param2 = mode;
    p->int_param3 = value;

	TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SEM_OPEN_CMD, NULL,
					p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
	if (tee_res)
		EMSG("invoke plugin failed sem_open with code 0x%x", tee_res);
    
    *sem = (sem_t *)(uintptr_t)p->res.sem_handle;
    IMSG("sem_open: %p\n", *sem);
	TEE_Free(p);

	return res;
}

int sem_post(sem_t **sem)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->sem_handle1 = (uintptr_t)*sem;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SEM_POST_CMD, NULL,
                    p, sizeof(struct PluginOperationData), &out_len);
    if (tee_res)
        EMSG("invoke plugin failed sem_post with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int sem_unlink(const char *name)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    size_t len = strlen(name) + 1;
    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData) + len, 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->size_t_param1 = len;
    TEE_MemMove(p->buf, name, p->size_t_param1);

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SEM_UNLINK_CMD, NULL,
                    p, sizeof(struct PluginOperationData) + p->size_t_param1, &out_len);
    if (tee_res)
        EMSG("invoke plugin failed sem_unlink with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}

int sem_wait(sem_t **sem)
{
    TEE_UUID uuid = PLUGIN_UUID;
    size_t out_len;

    struct PluginOperationData *p = TEE_Malloc(sizeof(struct PluginOperationData), 0);
    if (!p)
        return TEE_ERROR_OUT_OF_MEMORY;
    p->sem_handle1 = (uintptr_t)*sem;

    TEE_Result tee_res = tee_invoke_supp_plugin(&uuid, SEM_WAIT_CMD, NULL,
                    p, sizeof(struct PluginOperationData), &out_len);
    if (tee_res)
        EMSG("invoke plugin failed sem_wait with code 0x%x", tee_res);

    int res = p->res.int_val;
    TEE_Free(p);

    return res;
}
