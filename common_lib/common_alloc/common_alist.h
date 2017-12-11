#ifndef COMMON_ALIST_H
#define COMMON_ALIST_H

#ifndef COMMON_MAXALLOCSIZE
#define COMMON_MAXALLOCSIZE (0)
#endif

#ifndef COMMON_CANARY
#define COMMON_CANARY (0xC0DE) 
#endif

typedef struct {
    void *memlist;
    MUTEX_TYPE mutex;
}ALIST_T;

int common_alist_init(ALIST_T *list);
int common_alist_calloc(ALIST_T *list, size_t n);
int common_alist_strdup(ALIST_T *list, const char *s);
void common_alist_dealloc(ALIST_T *list, void *p);
void common_alist_uninit(ALIST_T *list);

void common_alist_echo(ALIST_T *list);

#endif
