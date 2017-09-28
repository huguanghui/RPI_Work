#ifndef UN_API__H
# define UN_API__H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>

#define PRINT_Y(x...) do{printf("\033[33m");printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);printf("\033[0m\n");}while(0)


#endif