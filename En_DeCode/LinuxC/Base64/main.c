#include "common.h"

int main()
{
	int iRet = 0;
	unsigned char str[] = "s13";
	char *s = NULL;

	s = s2base64(str, NULL, sizeof(str)/sizeof(char));
	printf("S:%s\n", s);
	free(s);

	return iRet;
}