#include "ovfs_alist.h"

int ovfs_ovf_alist_init(ALIST_T *list)
{
	if (!list)
		return -1;

	list->memlist = NULL;
	MUTEX_SETUP(list->mutex);

	return 0;
}

void* ovfs_ovf_alist_calloc(ALIST_T *list, size_t n)
{
	char *p;

	if (!list)
		return NULL;
	if (OVFS_MAXALLOCSIZE > 0 && n > OVFS_MAXALLOCSIZE)
		return NULL;
	if (n + sizeof(short) < n)
		return NULL;
	n += sizeof(short);
	if (n + ((-(long)n) & (sizeof(void*)-1)) + sizeof(void*) + sizeof(size_t) < n)
		return NULL;
	n += (-(long)n) & (sizeof(void*)-1);
	p = (char*)OVFS_CALLOC(1, n + sizeof(void*) + sizeof(size_t));
	if (!p)
		return NULL;
	*(unsigned short*)(p+n-sizeof(unsigned short)) = (unsigned short)OVFS_CANARY;
	MUTEX_LOCK(list->mutex);
	*(void**)(p + n) = list->memlist;
	*(size_t*)(p + n + sizeof(void*)) = n;
	list->memlist = p + n;
	MUTEX_UNLOCK(list->mutex);

	return p;
}

char* ovfs_ovf_alist_strdup(ALIST_T *list, const char *s)
{
	char *t = NULL;

	if (s)
	{
		size_t n = strlen(s) + 1;
		if (n > 0)
		{
			t = (char*)ovfs_ovf_alist_calloc(list, n);
			if (t)
			{
				memcpy((void*)t, (const void*)s, n);
				t[n - 1] = '\0';
			}
		}
	}

	return t;
}

void ovfs_ovf_alist_dealloc(ALIST_T *list, void *p)
{
	if (!list)
		return ;

	MUTEX_LOCK(list->mutex);
	if (p)
	{
		char **q;
		for (q = (char **)(void*)&list->memlist; *q; q = *(char***)q)
		{
			if (*(unsigned short*)(char*)(*q - sizeof(unsigned short)) != (unsigned short)OVFS_CANARY)
				return;
			if (p == (void*)(*q - *(size_t*)(*q + sizeof(void*))))
			{
				*q = **(char***)q;
				OVFS_FREE(p);
				MUTEX_UNLOCK(list->mutex);
				return;
			}
		}
	}
	else
	{
		char *q;
		while (list->memlist)
		{
			q = (char*)list->memlist;
			if (*(unsigned short*)(char*)(q - sizeof(unsigned short)) != (unsigned short)OVFS_CANARY)
			{
				MUTEX_UNLOCK(list->mutex);
				return;
			}
			list->memlist = *(void**)q;
			q -= *(size_t*)(q + sizeof(void*));
			OVFS_FREE(q);
		}
	}
	MUTEX_UNLOCK(list->mutex);

	return ;
}

int ovfs_ovf_alist_uninit(ALIST_T *list)
{
	if (!list)
		return -1;

	ovfs_ovf_alist_dealloc(list, NULL);
	MUTEX_CLEANUP(list->mutex);

	return 0;
}

void ovfs_ovf_alist_echo(ALIST_T *list)
{
	char *q;
	char *tmp;
	int index;

	if (!list)
		return;

	MUTEX_LOCK(list->mutex);
	tmp = list->memlist;
	while (tmp)
	{
		q = (char*)tmp;
		if (*(unsigned short*)(char*)(q - sizeof(unsigned short)) != (unsigned short)OVFS_CANARY)
		{
			MUTEX_UNLOCK(list->mutex);
			return;
		}
		tmp = *(void**)q;
		q -= *(size_t*)(q + sizeof(void*));
		printf("[%s:%d][%d]%p\n", __FUNCTION__, __LINE__, index, q);
		index ++;
	}
	MUTEX_UNLOCK(list->mutex);

	return;
}