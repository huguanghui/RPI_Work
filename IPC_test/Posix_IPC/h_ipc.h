#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

#define HAVE_MQUEUE_H 1

#define	va_mode_t	mode_t

#define	MAX_PATH	1024
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define PRT_Y(x...) do{printf("\033[33m");printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);printf("\033[0m\n");}while(0)

int Getopt(int argc, char * const *argv, const char *str);

void *Calloc(size_t n, size_t size);
void Close(int fd);
void *Malloc(size_t size);

#ifdef	HAVE_MQUEUE_H
			/* 4Posix message queues */
mqd_t	 Mq_open(const char *, int, ...);
void	 Mq_close(mqd_t);
void	 Mq_unlink(const char *pathname);
void	 Mq_send(mqd_t, const char *, size_t, unsigned int);
ssize_t	 Mq_receive(mqd_t, char *, size_t, unsigned int *);
void	 Mq_notify(mqd_t, const struct sigevent *);
void	 Mq_getattr(mqd_t, struct mq_attr *);
void	 Mq_setattr(mqd_t, const struct mq_attr *, struct mq_attr *);
#endif	/* HAVE_MQUEUE_H */

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);
