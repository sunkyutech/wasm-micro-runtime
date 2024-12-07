cmake_minimum_required (VERSION 3.2)
project(9dc30945-39eb-4af4-b9ae-35943f76cfc7.plugin C)

set (CFG_TEE_PLUGIN_LOAD_PATH "/usr/lib/tee-supplicant/plugins/")
set (CMAKE_SHARED_LIBRARY_PREFIX "")
set (WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)

add_library(${PROJECT_NAME} SHARED ${WAMR_ROOT_DIR}/core/shared/platform/linux-trustzone/untrusted/plugin.c)

target_link_libraries(${PROJECT_NAME} PRIVATE teec)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CFG_TEE_PLUGIN_LOAD_PATH})
