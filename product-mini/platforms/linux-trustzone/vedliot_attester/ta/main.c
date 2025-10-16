#include <stdlib.h>
#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include "wasm_export.h"
#include "bh_platform.h"

#include <wamr_ta.h>
#include <wasm.h>

#include "logging.h"
#include "ra_wasi.h"
#include "remote_attestation.h"
#include "tee_benchmarks.h"
#include "tz_utils.h"
#include "plugin_ta.h"

// static uint32_t heap_size;
uint32_t heap_size = 1 * 1024 * 1024;
uintptr_t shm_addr;
// int ca_pid = -1;
extern int ca_pid;
pid_t ca_pgid;

#define PLUGIN_UUID { 0x9dc30945, 0x39eb, 0x4af4, \
		{ 0xb9, 0xae, 0x35, 0x94, 0x3f, 0x76, 0xcf, 0xc7 } }

extern uint64_t paddr;

TEE_Result TA_CreateEntryPoint(void) {
    DMSG("has been called");
    return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void) {
    DMSG("has been called");
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, TEE_Param __maybe_unused params[4], void __maybe_unused **sess_ctx) {
    uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
					     TEE_PARAM_TYPE_NONE,
					     TEE_PARAM_TYPE_NONE,
					     TEE_PARAM_TYPE_NONE);
    DMSG("has been called");

    if (param_types != exp_param_types)
      return TEE_ERROR_BAD_PARAMETERS;

    (void)&params;
    (void)&sess_ctx;

    return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void __maybe_unused *sess_ctx) {
    (void)&sess_ctx;
    DMSG("Goodbye!");
}

static TEE_Result TA_SetHeapSize(uint32_t size) {
    heap_size = size;
    DMSG("The heap set is set to %u", heap_size);

    return TEE_SUCCESS;
}

static TEE_Result TA_RunWasm(uint8_t* wasm_bytecode, uint32_t wasm_bytecode_size, char* arg_buff, void *output_buffer,
        uint64_t output_buffer_size, void *benchmark_buffer, uint64_t benchmark_buffer_size)
{
    (void)&benchmark_buffer;
    (void)&benchmark_buffer_size;
    DMSG("has been called");

#ifdef PROFILING_LAUNCH_TIME
    TEE_GetREETime(benchmark_get_store(PROFILING_LAUNCH_TIME_START_MEMORY));
#endif

    // Allocate secure memory locations
    uint8_t *global_heap_buf = TEE_Malloc(heap_size, TEE_USER_MEM_HINT_NO_FILL_ZERO);
    uint8_t *trusted_wasm_bytecode = TEE_Malloc(wasm_bytecode_size, TEE_USER_MEM_HINT_NO_FILL_ZERO);

    // Copy the shared memory that contains the WASM bytecode into the secure memory
    TEE_MemMove(trusted_wasm_bytecode, wasm_bytecode, wasm_bytecode_size);

#ifdef PROFILING_LAUNCH_TIME
    TEE_GetREETime(benchmark_get_store(PROFILING_LAUNCH_TIME_END_MEMORY));
#endif

    // Set the output buffer to gather the stdout once the application ended
    TA_SetOutputBuffer(output_buffer, output_buffer_size);

    // General settings for the runtime
    TEE_Result result;
    wamr_context context =
    {
        .heap_buf = global_heap_buf,
        .heap_size = heap_size,
        .native_symbols = wasi_ra_native_symbols,
        .native_symbols_size = wasi_ra_native_symbols_size,
        .wasm_bytecode = trusted_wasm_bytecode,
        .wasm_bytecode_size = wasm_bytecode_size
    };

#ifdef PROFILING_LAUNCH_TIME
    TEE_GetREETime(benchmark_get_store(PROFILING_LAUNCH_TIME_START_HASH));
#endif

    // Hash the WASM bytecode for future RA quotes
    result = TA_HashWasmBytecode(&context);
    if (result != TEE_SUCCESS) goto error;

#ifdef PROFILING_LAUNCH_TIME
    TEE_GetREETime(benchmark_get_store(PROFILING_LAUNCH_TIME_END_HASH));
#endif

    DMSG("TA_InitializeWamrRuntime\n");
    int argc = arg_buff != NULL ? 2 : 1;
    char* argv[] = {(char*)"", arg_buff};
    result = TA_InitializeWamrRuntime(&context, argc, argv);
    if (result != TEE_SUCCESS) goto error;

    DMSG("TA_ExecuteWamrRuntime\n");
    result = TA_ExecuteWamrRuntime(&context);
    if (result != TEE_SUCCESS) goto error;

#ifdef PROFILING_LAUNCH_TIME
    snprintf(benchmark_buffer, benchmark_buffer_size, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,", \
        benchmark_get_value(PROFILING_LAUNCH_TIME_START_MEMORY), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_END_MEMORY), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_START_HASH), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_END_HASH), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_END_INIT), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_END_LOAD), \
        benchmark_get_value(PROFILING_LAUNCH_TIME_END_INSTANTIATE));
#endif

#ifdef PROFILING_MESSAGES
    snprintf(benchmark_buffer, benchmark_buffer_size, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n", \
            benchmark_get_value(PROFILING_MESSAGES_QUOTE_START), \
            benchmark_get_value(PROFILING_MESSAGES_QUOTE_END), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE0_MEM_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE0_KEYGEN_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE0_KEYGEN_END), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE1_MEM_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE1_ASYM_CRYPTO_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE1_KEYGEN_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE1_SYM_CRYPTO_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE1_SYM_CRYPTO_END), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE2_MEM_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE2_SYM_CRYPTO_START), \
            benchmark_get_value(PROFILING_MESSAGES_MESSAGE2_SYM_CRYPTO_END));
#endif

#ifdef PROFILING_MESSAGE3
    snprintf(benchmark_buffer, benchmark_buffer_size, "%ld,%ld,%ld,%ld,", \
            benchmark_get_value(PROFILING_MESSAGE3_MALLOC_START), \
            benchmark_get_value(PROFILING_MESSAGE3_MALLOC_END), \
            benchmark_get_value(PROFILING_MESSAGE3_DECRYPT_START), \
            benchmark_get_value(PROFILING_MESSAGE3_DECRYPT_END));
#endif

    error:
    DMSG("TA_TearDownWamrRuntime\n");
    TA_TearDownWamrRuntime(&context);

    // Free up the allocated resources
    TEE_Free(global_heap_buf);
    TEE_Free(trusted_wasm_bytecode);

    return result;
}

static TEE_Result invoke_sp(uint32_t param_types, TEE_Param params[4])
{
	IMSG("[TA] Starting invoke_sp...");

	TEE_Result tee_res = TEE_SUCCESS;
	TEE_UUID plugin_uuid = PLUGIN_UUID;
	size_t out_len;

	uint32_t exp_param_types = 
		TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT, TEE_PARAM_TYPE_VALUE_INPUT,
				TEE_PARAM_TYPE_VALUE_INPUT, TEE_PARAM_TYPE_VALUE_INPUT);

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	// receive CA PID and PGID
	ca_pid = (pid_t)params[0].value.a;
	ca_pgid = (pid_t)params[1].value.a;

	paddr = ((uint64_t)params[2].value.a << 32) | params[2].value.b;
	IMSG("[TA] Physical Address: 0x%016lx", paddr);

	// シャドウプロセスを起動
	struct PluginOperationData2 *supp = TEE_Malloc(sizeof(struct PluginOperationData2), 0);
	if (!supp)
		return TEE_ERROR_OUT_OF_MEMORY;

	supp->ta_num = ca_pid;
	supp->mmap_size = 1 * 1024 * 1024; // 1MB
	supp->fdp_flag = params[3].value.a;

	tee_res = tee_invoke_supp_plugin(&plugin_uuid, SP_INVOKE_CMD, NULL,
						supp, sizeof(struct PluginOperationData2), &out_len);
	if (tee_res) {
		EMSG("[TA] tee_invoke_supp_plugin failed with code 0x%x", tee_res);
	}

	// send back TA PID
	pid_t ta_pid = supp->ta_pid;
	params[0].value.b = (uint32_t)ta_pid;

	TEE_Free(supp);

	return tee_res;
}

static TEE_Result unpack_argv_buf(const void *buf, size_t sz, int *out_argc, char ***out_argv)
{
    *out_argc = 0;
    *out_argv = NULL;

    if (buf == NULL || sz == 0) {
        char **argv0 = TEE_Malloc(sizeof(char*), 0);
        if (!argv0) return TEE_ERROR_OUT_OF_MEMORY;
        argv0[0] = NULL;
        *out_argc = 0;
        *out_argv = argv0;
        return TEE_SUCCESS;
    }

    const char *cbuf = (const char *)buf;

    if (cbuf[sz - 1] != '\0') {
        return TEE_ERROR_BAD_PARAMETERS;
    }

    int argc = 0;
    size_t off = 0;
    while (off < sz) {
        size_t remain = sz - off;
        const void *z = memchr(cbuf + off, '\0', remain);
        if (!z) return TEE_ERROR_BAD_PARAMETERS;
        argc++;
        off = (size_t)((const char*)z - cbuf) + 1;
    }

    char *payload = TEE_Malloc(sz, 0);
    if (!payload) return TEE_ERROR_OUT_OF_MEMORY;
    TEE_MemMove(payload, buf, sz);

    char **argv = TEE_Malloc(sizeof(char*) * (argc + 1), 0);
    if (!argv) { TEE_Free(payload); return TEE_ERROR_OUT_OF_MEMORY; }

    off = 0;
    int i = 0;
    while (off < sz) {
        argv[i++] = payload + off;
        while (off < sz && payload[off] != '\0') off++;
        off++;
    }
    argv[argc] = NULL;

    *out_argc = argc;
    *out_argv = argv;
    
	return TEE_SUCCESS;
}

static TEE_Result invoke_main(uint32_t param_types, TEE_Param params[4])
{
	IMSG("[TA] Starting invoke_main...");

	TEE_Result tee_res = TEE_SUCCESS;

	uint32_t exp_param_types = 
		TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT, TEE_PARAM_TYPE_MEMREF_INOUT,
        		TEE_PARAM_TYPE_MEMREF_INOUT, TEE_PARAM_TYPE_VALUE_INOUT);

    if (param_types != exp_param_types)
    	return TEE_ERROR_BAD_PARAMETERS;
    
    // Allocate secure memory locations
    uint8_t *global_heap_buf = TEE_Malloc(heap_size, TEE_USER_MEM_HINT_NO_FILL_ZERO);
    uint8_t *trusted_wasm_bytecode = TEE_Malloc(wasm_bytecode_size, TEE_USER_MEM_HINT_NO_FILL_ZERO);

    // Copy the shared memory that contains the WASM bytecode into the secure memory
    TEE_MemMove(trusted_wasm_bytecode, wasm_bytecode, wasm_bytecode_size);

    // General settings for the runtime
    TEE_Result result;
    wamr_context context =
    {
        .heap_buf = global_heap_buf,
        .heap_size = heap_size,
        .native_symbols = wasi_ra_native_symbols,
        .native_symbols_size = wasi_ra_native_symbols_size,
        .wasm_bytecode = trusted_wasm_bytecode,
        .wasm_bytecode_size = wasm_bytecode_size
    };

    // Hash the WASM bytecode for future RA quotes
    result = TA_HashWasmBytecode(&context);
    if (result != TEE_SUCCESS) goto error;

	// receive argv
	char *argv_buf = params[0].memref.buffer;
	size_t argv_len = params[0].memref.size;

	int argc;
	char **argv;
	tee_res = unpack_argv_buf(argv_buf, argv_len, &argc, &argv);
	if (tee_res != TEE_SUCCESS) {
		return tee_res;
	}
	// NOTE: TA is not supported to receive envp

	// receive shared memory address and size
	shm_addr = params[1].memref.buffer;
	shm_size = params[1].memref.size;

	// receive shadow shared memory address and size
	struct PluginSharedMemoryData *shared_data = (struct PluginSharedMemoryData *)params[2].memref.buffer;
	size_t shadow_size = params[2].memref.size;

	// receive and store physical address of shadow memory
	paddr = ((uint64_t)params[3].value.a << 32) | params[3].value.b;
	if (register_shadow_shm_addr(shared_data) != 0) {
		EMSG("[TA] Failed to register shadow shared memory");
		return TEE_ERROR_GENERIC;
	}

	result = TA_InitializeWamrRuntime(&context, argc, argv);
    if (result != TEE_SUCCESS) goto error;

    DMSG("TA_ExecuteWamrRuntime\n");
    result = TA_ExecuteWamrRuntime(&context);
    if (result != TEE_SUCCESS) goto error;

	// end shadow process
    shared_data->command = END_CMD;
    shared_data->status = STATUS_REQUEST;

	TEE_Free(argv);

    error:
    DMSG("TA_TearDownWamrRuntime\n");
    TA_TearDownWamrRuntime(&context);

    // Free up the allocated resources
    TEE_Free(global_heap_buf);
    TEE_Free(trusted_wasm_bytecode);

    return result;
	
	return tee_res;
}

static TEE_Result do_nothing(uint32_t param_types, TEE_Param params[4])
{
	uint32_t exp_param_types = 
		TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INOUT, TEE_PARAM_TYPE_NONE,
				TEE_PARAM_TYPE_NONE, TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types) 
		return TEE_ERROR_BAD_PARAMETERS;
	
	struct timespec tee_time;
	clock_gettime(CLOCK_REALTIME, &tee_time);

	TEE_MemMove(params[0].memref.buffer, &tee_time, sizeof(tee_time));
	params[0].memref.size = sizeof(tee_time);

	return TEE_SUCCESS;
}

TEE_Result TA_InvokeCommandEntryPoint(void __maybe_unused *sess_ctx, uint32_t cmd_id, uint32_t param_types,
     TEE_Param params[4])
{
    (void)&sess_ctx;
    uint32_t exp_param_types = 0;

    switch (cmd_id) {
    case COMMAND_RUN_WASM:
        exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT, TEE_PARAM_TYPE_MEMREF_INPUT,
					     TEE_PARAM_TYPE_MEMREF_INOUT, TEE_PARAM_TYPE_MEMREF_INOUT);
        if (exp_param_types != param_types) return TEE_ERROR_BAD_PARAMETERS;
        
        return TA_RunWasm((unsigned char*)params[0].memref.buffer,
            params[0].memref.size,
            (char*)params[1].memref.buffer,
            params[2].memref.buffer,
            params[2].memref.size,
            params[3].memref.buffer,
            params[3].memref.size);
    
    case COMMAND_CONFIGURE_HEAP:
        exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INPUT, TEE_PARAM_TYPE_NONE,
					     TEE_PARAM_TYPE_NONE, TEE_PARAM_TYPE_NONE);
        if (exp_param_types != param_types) return TEE_ERROR_BAD_PARAMETERS;

        return TA_SetHeapSize(params[0].value.a);
    
    case COMMAND_INVOKE_SP:
        return invoke_sp(param_types, params);
    
    case COMMAND_TA_MAIN:
        return invoke_main(param_types, params);
    
    case COMMAND_DO_NOTHING:
        return do_nothing(param_types, params);
    default:
        return TEE_ERROR_BAD_PARAMETERS;
    }
}
