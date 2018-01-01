#ifndef OVFS_ALIST_H
#define OVFS_ALIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ovfs_threads.h"

#define OVFS_CALLOC(num,size) calloc(num, size);
#define OVFS_FREE(s); free(s);

/**************************** ALIST API *******************************/
#ifndef OVFS_MAXALLOCSIZE
# define OVFS_MAXALLOCSIZE  (0)
#endif

#ifndef OVFS_CANARY
# define OVFS_CANARY (0xC0DE) 
#endif

typedef struct ALIST_S
{
	void *memlist;
	MUTEX_TYPE mutex;
}ALIST_T;

int ovfs_ovf_alist_init(ALIST_T *list);
void* ovfs_ovf_alist_calloc(ALIST_T *list, size_t n);
char* ovfs_ovf_alist_strdup(ALIST_T *list, const char *s);
void ovfs_ovf_alist_dealloc(ALIST_T *list, void *p);
int ovfs_ovf_alist_uninit(ALIST_T *list);

void ovfs_ovf_alist_echo(ALIST_T *list);

#endif /* ovfs_alist.h */
