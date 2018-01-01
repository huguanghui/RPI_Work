#ifndef THREADS_H
#define THREADS_H

#include <unistd.h>
#include <pthread.h>

# define THREAD_TYPE		pthread_t
# define THREAD_ID		pthread_self()
# define THREAD_CREATE(x,y,z)	pthread_create((x), NULL, (y), (z))
# define THREAD_DETACH(x)	pthread_detach((x))
# define THREAD_JOIN(x)		pthread_join((x), NULL)
# define THREAD_EXIT		pthread_exit(NULL)
# define THREAD_CANCEL(x)	pthread_cancel(x)
# define MUTEX_TYPE		pthread_mutex_t
# define MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER
# define MUTEX_SETUP(x)		pthread_mutex_init(&(x), NULL)
# define MUTEX_CLEANUP(x)	pthread_mutex_destroy(&(x))
#if 0 /* 1: DEBUG MUTEX */
# define MUTEX_LOCK(x)		(fprintf(stderr, "! LOCK   %p %s:%d\n", &x, __FILE__, __LINE__), pthread_mutex_lock(&(x)))
# define MUTEX_UNLOCK(x)	(fprintf(stderr, "! UNLOCK %p %s:%d\n", &x, __FILE__, __LINE__), pthread_mutex_unlock(&(x)))
#else
# define MUTEX_LOCK(x)		pthread_mutex_lock(&(x))
# define MUTEX_UNLOCK(x)	pthread_mutex_unlock(&(x))
#endif
# define COND_TYPE		pthread_cond_t
# define COND_SETUP(x)		pthread_cond_init(&(x), NULL)
# define COND_CLEANUP(x)	pthread_cond_destroy(&(x))
# define COND_SIGNAL(x)		pthread_cond_signal(&(x))
# define COND_WAIT(x,y)		pthread_cond_wait(&(x), &(y))

#endif /* threads.h */