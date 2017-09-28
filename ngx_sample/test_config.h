#ifndef TEST_CONFIG__H
#define TEST_CONFIG__H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PRINT_Y(x...) do{printf("\033[33m");printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);printf("\033[0m\n");}while(0)

#ifndef test_inline
# define test_inline inline
#endif

typedef unsigned int  test_uint_t;

#endif