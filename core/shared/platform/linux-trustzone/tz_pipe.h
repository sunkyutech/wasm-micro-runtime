#ifndef _TZ_PIPE_H
#define _TZ_PIPE_H

#ifdef __cplusplus
extern "C" {
#endif

int pipe(int pipefd[2]);
int pipe2(int pipefd[2], int flags);

#ifdef __cplusplus
}
#endif

#endif /* end of _TZ_PIPE_H */

