#include "h_ipc.h"

int Getopt(int argc, char * const *argv, const char *str)
{
	int opt;

	if ((opt = getopt(argc, argv, str)) == '?')
	{
		exit(1);
	}

	return (opt);
}

void *Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

/* include Close */
void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}
/* end Close */

void *Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

#ifdef	HAVE_MQUEUE_H

mqd_t Mq_open(const char *pathname, int oflag, ...)
{
	mqd_t	mqd;
	va_list	ap;
	mode_t	mode;
	struct mq_attr	*attr;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		attr = va_arg(ap, struct mq_attr *);
		if ( (mqd = mq_open(pathname, oflag, mode, attr)) == (mqd_t) -1)
			err_sys("mq_open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (mqd = mq_open(pathname, oflag)) == (mqd_t) -1)
			err_sys("mq_open error for %s", pathname);
	}
	return(mqd);
}

void Mq_close(mqd_t mqd)
{
	if (mq_close(mqd) == -1)
		err_sys("mq_close error");
}

void Mq_unlink(const char *pathname)
{
	if (mq_unlink(pathname) == -1)
		err_sys("mq_unlink error");
}

void Mq_send(mqd_t mqd, const char *ptr, size_t len, unsigned int prio)
{
	if (mq_send(mqd, ptr, len, prio) == -1)
		err_sys("mq_send error");
}

ssize_t Mq_receive(mqd_t mqd, char *ptr, size_t len, unsigned int *prio)
{
	ssize_t	n;

	if ( (n = mq_receive(mqd, ptr, len, prio)) == -1)
		err_sys("mq_receive error");
	return(n);
}

void Mq_notify(mqd_t mqd, const struct sigevent *notification)
{
	if (mq_notify(mqd, notification) == -1)
		err_sys("mq_notify error");
}

void Mq_getattr(mqd_t mqd, struct mq_attr *mqstat)
{
	if (mq_getattr(mqd, mqstat) == -1)
		err_sys("mq_getattr error");
}

void Mq_setattr(mqd_t mqd, const struct mq_attr *mqstat, struct mq_attr *omqstat)
{
	if (mq_setattr(mqd, mqstat, omqstat) == -1)
		err_sys("mq_setattr error");
}
#endif	/* HAVE_SYS_MSG_H */

