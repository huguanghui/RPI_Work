#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ovfs_alist.h"

#define HPT(x...) do{printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);}while(0)

#define ovfs_coblank(c) ((c)+1 > 0 && (c) <= 32)
#define ovfs_unget(req, c) ((req)->ahead = c)

#ifndef OVFS_BUFLEN
# define OVFS_BUFLEN (65536)
#endif

#ifndef OVFS_TMPLEN
# define OVFS_TMPLEN (1024)
#endif

#ifndef OVFS_HDRLEN
# define OVFS_HDRLEN (8192)
#endif

#ifndef OVFS_TAGLEN
# define OVFS_TAGLEN (1024)
#endif

#ifndef LONG64 
# define LONG64 long long
#endif

struct soap_code_map
{ LONG64 code;
  const char *string;
};
const char* ovfs_code_str(const struct soap_code_map *code_map, long code);
LONG64 ovfs_code_int(const struct soap_code_map *code_map, const char *str, LONG64 other);

typedef struct
{
	char *url;
	int contentLen;
	char *authorization;
}OVFS_OVF_HTTP_HEADER_T;

typedef struct 
{
	ALIST_T alist;
	int ipcFd;
	OVFS_OVF_HTTP_HEADER_T header;
	char *http_content;
	int length;
	int error;
	int ahead;
	int count;
	int status;
	size_t bufidx;
	size_t buflen;
	char buf[OVFS_BUFLEN];
	char msgbuf[OVFS_TMPLEN];
	char tmpbuf[OVFS_TMPLEN];
	char path[OVFS_TAGLEN];
}OVFS_OVF_HTTP_REQUEST_T;

int ovfs_recv(OVFS_OVF_HTTP_REQUEST_T *req);

# define ovfs_get0(req) (((req)->bufidx>=(req)->buflen && ovfs_recv(req)) ? EOF : (unsigned char)(req)->buf[(req)->bufidx])
# define ovfs_get1(req) (((req)->bufidx>=(req)->buflen && ovfs_recv(req)) ? EOF : (unsigned char)(req)->buf[(req)->bufidx++])

unsigned long ovfs_strtoul(const char *s, char **t, int b);
int ovfs_tag_cmp(const char *s, const char *t);

int ovfs_send_raw(OVFS_OVF_HTTP_REQUEST_T *req, const char *s, size_t n);

int ovfs_begin_send(OVFS_OVF_HTTP_REQUEST_T *req);
int ovfs_response(OVFS_OVF_HTTP_REQUEST_T *req);

int ovfs_flush_raw(OVFS_OVF_HTTP_REQUEST_T *req, const char *s, size_t n);
int ovfs_flush(OVFS_OVF_HTTP_REQUEST_T *req);
int ovfs_end_send_flush(OVFS_OVF_HTTP_REQUEST_T *req);
int ovfs_end_send(OVFS_OVF_HTTP_REQUEST_T *req);

#endif /* httpserver.h */
