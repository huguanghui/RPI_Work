#include "common.h"

int main()
{
	int iRet = 0;
	unsigned char str[] = "s13";
	char *s = NULL;

	char *str1 = malloc(10);
	char *p = str1;
	memset(str1, 0, 10);

	*str1 ++ = 'a';

	printf("P:%p\n", p);
	printf("o:%c\n", *p);
	printf("str:%p\n", str1);
	printf("str:%c\n", *str1);

	s = s2base64(str, NULL, sizeof(str)/sizeof(str[0]));
	printf("S:%s\n", s);
	free(s);



	return iRet;
}