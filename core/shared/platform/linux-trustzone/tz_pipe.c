#include "platform_api_vmcore.h"

int pipe(int pipefd[2])
{
    EMSG("pipe is not supported.");
    return -1;
}

int pipe2(int pipefd[2], int flags)
{
    EMSG("pipe2 is not supported.");
    return -1;
}
