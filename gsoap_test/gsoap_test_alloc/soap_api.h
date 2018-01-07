#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ALIST void*
#define PRINT_Y(x...) do{printf("\033[33m");printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);printf("\033[0m\n");}while(0)

#define soap_strncat(buf, len, src, num)  ((buf) == NULL || ((size_t)(len) > strlen((buf)) + (size_t)(num) ? (strncat((buf), (src), (num)), (buf)[(size_t)(len) - 1] = '\0') : 1))

#ifndef SOAP_MAXALLOCSIZE
# define SOAP_MAXALLOCSIZE (0) /* max size that malloc() can handle, zero for no limit */
#endif

#ifndef TEST_TEMPLEN
# define TEST_TEMPLEN (1024)
#endif

#ifndef SOAP_CANARY
# define SOAP_CANARY (0xC0DE)
#endif

#ifdef SOAP_MEM_DEBUG
# ifndef SOAP_MALLOC
# define SOAP_MALLOC(size)
# endif
# ifndef SOAP_FREE
# define SOAP_FREE(ptr)   
# endif
#endif

#ifndef  SOAP_MALLOC 
# define SOAP_MALLOC(size)  malloc(size)
#endif

#ifndef SOAP_FREE
# define SOAP_FREE(ptr) free((void*)(ptr))
#endif

typedef struct tagPARAM_TABLE
{
	char name[32];
	char *value;
}PARAM_TABLE_T;

typedef struct tagQUERY_PARAM
{
	int a;
}QUERY_PARAM_T;

typedef struct tagTEST_CONTEXT
{
	char tmpbuf[TEST_TEMPLEN];
	ALIST alist;	
}TEST_CONTEXT_T;

extern TEST_CONTEXT_T *gContext;

void* soap_malloc(ALIST *list, size_t n);

void soap_echo_alist(ALIST *list);

void soap_dealloc(ALIST *list, void *p);