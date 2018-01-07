#include "soap_api.h"

TEST_CONTEXT_T *gContext = NULL;

char *slower(char *string)
{
	char *s;

	if (string == NULL)
	{
		return NULL;
	}
	s = string;
	while (*s)
	{
		if (isupper(*s))
		{
			*s = (char)tolower((unsigned char) *s);
		}
		s ++;
	}
	*s = '\0';

	return string;
}

int main(int argc, char **argv)
{
	int iRet = 0;
	char *p1,*p2,*p3,*p4 = NULL;
	ALIST *list = NULL;
	char *q;
	void *m;
	char *url;  

	if (argv[1])
	{
		url = argv[1];
	}
	else
	{
	   url = "/PTZ/PresetTour?Token=PresetTour_0&TourSpot";		
	}


	gContext = malloc(sizeof(TEST_CONTEXT_T));
	memset(gContext, 0, sizeof(TEST_CONTEXT_T));
/*
	list = malloc(sizeof(ALIST));
	*list = NULL;
	p1 = soap_malloc(list, 4);
	PRINT_Y("P1:%p", p1);

	p2 = soap_malloc(list, 8);
	PRINT_Y("P2:%p", p2);

	p3 = soap_malloc(list, 8);
	PRINT_Y("P3:%p", p3);

	p4 = soap_malloc(list, 8);
	PRINT_Y("P4:%p", p4);

	soap_echo_alist(list);
	soap_dealloc(list, p2);
	soap_echo_alist(list);
	soap_dealloc(list, NULL);
	soap_echo_alist(list);
*/
	{
		char *pos;
		char *pre_pos;
		char *next_pos;
		int len = 0;
		char action[128];
		char param[64];
		PARAM_TABLE_T tmp;
		
		if (url && strlen(url))
		{
			PRINT_Y("URL:%s", url);
			pos = strchr(url, '?');
			if (pos)
			{
				PRINT_Y("%s", pos);
				len = pos - url;
				PRINT_Y("Len:%d", len);
				memcpy(action, url, len);
				action[len] = '\0';

				pre_pos = pos + 1;
				while (pre_pos && strlen(pre_pos))
				{
					pos = strchr(pre_pos, '&');
					if (pos)
					{
						len = pos - pre_pos;
						memcpy(param, pre_pos, len);
						param[len] = '\0';
						pre_pos = pos + 1;
					}
					else
					{
						snprintf(param, sizeof(param), "%s", pre_pos);
						pre_pos = NULL;
					}
					PRINT_Y("Para:%s", param);
					{
						char *name;
						name = strchr(param, '=');
						if (name)
						{
							len = name - param;
							memcpy(tmp.name, param, len);
							tmp.name[len] = '\0';
							tmp.value = name + 1;
						}
						else
						{
							snprintf(tmp.name, sizeof(tmp.name), "%s", param);
							tmp.value = NULL;
						}
					}
					{
						PRINT_Y("Name:%s", tmp.name);
						PRINT_Y("Value:%s", tmp.value?tmp.value:"NULL");
					}
				}
			}
			else
			{
				snprintf(action, sizeof(action), "%s", url);
			}
			slower(action);
			PRINT_Y("Action:%s", action);
		}
	}

	for (;;)
	{
		sleep(5);
	}
		
	free(gContext);

	return iRet;
}

void* soap_malloc(ALIST *list, size_t n)
{ 
	char *p;

	if (SOAP_MAXALLOCSIZE > 0 && n > SOAP_MAXALLOCSIZE)
		return NULL;
	if (n + sizeof(short) < n)
  		return NULL;
	n += sizeof(short);
	if (n + ((-(long)n) & (sizeof(void*)-1)) + sizeof(void*) + sizeof(size_t) < n)
  		return NULL;
	n += (-(long)n) & (sizeof(void*)-1); /* align at 4-, 8- or 16-byte boundary by rounding up */	
	p = (char*)SOAP_MALLOC(n + sizeof(void*) + sizeof(size_t));
	if (!p)
	{ 
  		return NULL;
	}
	/* set a canary word to detect memory overruns and data corruption */
	*(unsigned short*)(p + n - sizeof(unsigned short)) = (unsigned short)SOAP_CANARY;
	/* keep chain of alloced cells for destruction */
	*(void**)(p + n) = *list;
	*(size_t*)(p + n + sizeof(void*)) = n;
	*list = p + n;
	PRINT_Y("[%d]List:%x", n, *list);
	
	return p;
}

void soap_echo_alist(ALIST *list)
{
	char **q;
	int i = 0;

	for (q = (char **)(void *)list; *q; q = *(char***)q)
	{
		if (*(unsigned short*)(char*)(*q - sizeof(unsigned short)) != (unsigned short)SOAP_CANARY)
		{
			PRINT_Y("MOE");
			return;
		}
		PRINT_Y("List[%d]:%x", i, *q);
		i ++;	
	}
}

void soap_dealloc(ALIST *list, void *p)
{
	if (p)
	{
		char **q;
		for (q = (char **)(void *)list; *q; q = *(char***)q)
		{
			if (*(unsigned short*)(char*)(*q - sizeof(unsigned short)) != (unsigned short)SOAP_CANARY)
			{
				PRINT_Y("MOE");
				return;
			}
			PRINT_Y("P:%p *Q:%p", p, *q);
			PRINT_Y("T:%p", (void*)(*q - *(size_t*)(*q + sizeof(void*))));
			if (p == (void*)(*q - *(size_t*)(*q + sizeof(void*))))
			{
				*q = **(char***)q;
				SOAP_FREE(p);
				return;
			}
		}
	}
	else
	{
		char *q;
		while (*list)
		{
			q = (char*)*list;
			if (*(unsigned short*)(char*)(q - sizeof(unsigned short)) != (unsigned short)SOAP_CANARY)
			{
				PRINT_Y("MOE");
				return;
			}
			*list = *(void**)q;
			q -= *(size_t*)(q + sizeof(void*));
			SOAP_FREE(p);
		}
	}

	return;
}