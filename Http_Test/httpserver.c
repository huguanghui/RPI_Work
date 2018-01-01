#include "httpserver.h"

static const struct soap_code_map h_http_error_codes[] =
{ { 200, "OK" },
  { 201, "Created" },
  { 202, "Accepted" },
  { 203, "Non-Authoritative Information" },
  { 204, "No Content" },
  { 205, "Reset Content" },
  { 206, "Partial Content" },
  { 300, "Multiple Choices" },
  { 301, "Moved Permanently" },
  { 302, "Found" },
  { 303, "See Other" },
  { 304, "Not Modified" },
  { 305, "Use Proxy" },
  { 307, "Temporary Redirect" },
  { 400, "Bad Request" },
  { 401, "Unauthorized" },
  { 402, "Payment Required" },
  { 403, "Forbidden" },
  { 404, "Not Found" },
  { 405, "Method Not Allowed" },
  { 406, "Not Acceptable" },
  { 407, "Proxy Authentication Required" },
  { 408, "Request Time-out" },
  { 409, "Conflict" },
  { 410, "Gone" },
  { 411, "Length Required" },
  { 412, "Precondition Failed" },
  { 413, "Request Entity Too Large" },
  { 414, "Request-URI Too Large" },
  { 415, "Unsupported Media Type" },
  { 416, "Requested range not satisfiable" },
  { 417, "Expectation Failed" },
  { 500, "Internal Server Error" },
  { 501, "Not Implemented" },
  { 502, "Bad Gateway" },
  { 503, "Service Unavailable" },
  { 504, "Gateway Time-out" },
  { 505, "HTTP Version not supported" },
  {   0, NULL }
};

static int ovfs_recv_raw(OVFS_OVF_HTTP_REQUEST_T *req)
{
	size_t ret;
	int r;

	req->bufidx = 0;
	req->buflen = ret = recv(req->ipcFd, req->buf, sizeof(req->buf), 0);

	if (ret)
	{
		req->count += ret;
		return 0;
	}

	return -1;
}

int ovfs_recv(OVFS_OVF_HTTP_REQUEST_T *req)
{
	return req->error = ovfs_recv_raw(req);
}

static unsigned char ovfs_getchar(OVFS_OVF_HTTP_REQUEST_T *request)
{
	unsigned char c;
	c = request->ahead;
	if (c)
	{
		if ((int)c != EOF)
			request->ahead = 0;
		return c;
	}
	return ovfs_get1(request);
}

static int ovfs_getline(OVFS_OVF_HTTP_REQUEST_T *req, char *buf, int len)
{
	char *s = buf;
	int i = len;
	unsigned char c = 0;

	for (;;)
	{
		while (i > 1)
		{
			if (c == '\r' || c == '\n')
				break;
			if ((int)c == EOF)
				return req->error = -1;
			*s++ = (char)c;
			i--;
		}
		*s = '\0';
		if (c != '\n')
			c = ovfs_getchar(req);
		if (c == '\n')
		{
			if (i == len)
				break;
			c = ovfs_get0(req);
			if (c != ' ' && c != '\t')
				break;
		}
		else if ((int)c == EOF)
		{
			return req->error = -1;
		}
		if (i <= 0)
			return req->error = -1;
	}	

	return 0;
}

static int ovfs_parse_header(OVFS_OVF_HTTP_REQUEST_T *req, const char *key, const char *val)
{
	if (!ovfs_tag_cmp(key, "Content-Type"))
	{
		req->http_content = ovfs_ovf_alist_strdup(&req->alist, val);
	}
	else if (!ovfs_tag_cmp(key, "Content-Length"))
	{
		req->length = atoi(val);
	}

	return 0;
}

static int ovfs_ovf_http_parse(OVFS_OVF_HTTP_REQUEST_T *req)
{
	char header[OVFS_HDRLEN], *s;
	unsigned short httpcmd = 0;
	unsigned char c;

	// 1.Parse Http-Header
	c = ovfs_getchar(req);
	while (ovfs_coblank(c))
	{
		c = ovfs_getchar(req);
	}
	ovfs_unget(req, c);
	HPT("Waiting for HTTP request...\n");
	ovfs_getline(req, req->msgbuf, sizeof(req->msgbuf));
	s = strchr(req->msgbuf, ' ');
	if (s)
	{
		req->status = (unsigned short)ovfs_strtoul(s, &s, 10);
		if (!ovfs_coblank((unsigned char)*s))
			req->status = 0;
	}
	for (;;)
	{
		ovfs_getline(req, header, OVFS_HDRLEN);
		if (!*header)
			break;
		s = strchr(header, ':');
		if (s)
		{ 
			char *t;
			*s = '\0';
			do
			{ s++;
			} while (*s && *s <= 32);
			if (*s == '"')
			  s++;
			t = s + strlen(s) - 1;
			while (t > s && *t <= 32)
			  t--;
			if (t >= s && *t == '"')
			  t--;
			t[1] = '\0';
			ovfs_parse_header(req, header, s);
		}
	}
	s = strstr(req->msgbuf, "HTTP/");
	size_t l = 0;
	if (s)
	{
		if (!strncmp(req->msgbuf, "POST ", l = 5))
			httpcmd = 1;
		else if (!strncmp(req->msgbuf, "PUT ", l = 4))
			httpcmd = 2;
		else if (!strncmp(req->msgbuf, "GET ", l = 4))
			httpcmd = 3;
		else if (!strncmp(req->msgbuf, "DELETE ", l = 7))
			httpcmd = 4;
		else if (!strncmp(req->msgbuf, "OPTIONS ", l = 8))
			httpcmd = 5;
		else if (!strncmp(req->msgbuf, "HEAD ", l = 5))
			httpcmd = 6;
		if (httpcmd)
		{
			size_t m,n,k;
			int err = 0;
			while (req->msgbuf[l] && ovfs_coblank(req->msgbuf[l]))
				l++;
			k = s - req->msgbuf - l;
			strncpy(req->path, req->msgbuf + l, k);
		}
	}
	// 2.Parse Http-Body
	{

	}
	// 3.Handler
	{

	}
	// 4.Response
	{
		ovfs_response(req);
		ovfs_end_send(req);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int result;
	int listen_fd;
	int accept_fd;
	struct sockaddr_in server_in, client_in;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server_in, sizeof(server_in));
	server_in.sin_family = AF_INET;
	server_in.sin_addr.s_addr = INADDR_ANY;
	server_in.sin_port = htons(8585);
	bind(listen_fd, (struct sockaddr*)&server_in, sizeof(server_in));
	listen(listen_fd, 100);

	printf("Listen ...!\n");
	for (;;)
	{
		socklen_t len = sizeof(struct sockaddr_in);
		accept_fd = accept(listen_fd, (struct sockaddr *)(&client_in), &len);

		printf("Server get connection from:%s\n", inet_ntoa(client_in.sin_addr));
		if (accept_fd > 0)
		{
			for (;;)
			{
				OVFS_OVF_HTTP_REQUEST_T *request = calloc(1, sizeof(OVFS_OVF_HTTP_REQUEST_T));
				ovfs_ovf_alist_init(&request->alist);
				request->ipcFd = accept_fd;
				request->error = ovfs_ovf_http_parse(request);
				ovfs_ovf_alist_uninit(&request->alist);
				if (request->error)
				{
					close(request->ipcFd);
					break;
				}
			}
		}
	}

	return 0;
}


unsigned long ovfs_strtoul(const char *s, char **t, int b)
{ unsigned long n = 0;
  int c;
  while (*s > 0 && *s <= 32)
    s++;
  if (b == 10)
  { short neg = 0;
    if (*s == '-')
    { s++;
      neg = 1;
    }
    else if (*s == '+')
      s++;
    while ((c = *s) && c >= '0' && c <= '9')
    { if (n >= 429496729 && (n > 429496729 || c >= '6'))
        break;
      n *= 10;
      n += c - '0';
      s++;
    }
    if (neg && n > 0)
      s--;
  }
  else /* b == 16 */
  { while ((c = *s))
    { if (c >= '0' && c <= '9')
        c -= '0';
      else if (c >= 'A' && c <= 'F')
        c -= 'A' - 10;
      else if (c >= 'a' && c <= 'f')
        c -= 'a' - 10;
      if (n > 0x0FFFFFFF)
        break;
      n <<= 4;
      n += c;
      s++;
    }
  }
  if (t)
    *t = (char*)s;
  return n;
}

int ovfs_tag_cmp(const char *s, const char *t)
{ 
	for (;;)
  { int c1 = *s;
    int c2 = *t;
    if (!c1 || c1 == '"')
      break;
    if (c2 != '-')
    { if (c1 != c2)
      { if (c1 >= 'A' && c1 <= 'Z')
          c1 += 'a' - 'A';
        if (c2 >= 'A' && c2 <= 'Z')
          c2 += 'a' - 'A';
      }
      if (c1 != c2)
      { if (c2 != '*')
          return 1;
        c2 = *++t;
        if (!c2)
          return 0;
        if (c2 >= 'A' && c2 <= 'Z')
          c2 += 'a' - 'A';
        for (;;)
        { c1 = *s;
          if (!c1 || c1 == '"')
            break;
          if (c1 >= 'A' && c1 <= 'Z')
            c1 += 'a' - 'A';
          if (c1 == c2 && !ovfs_tag_cmp(s + 1, t + 1))
            return 0;
          s++;
        }
        break;
      }
    }
    s++;
    t++;
  }
  if (*t == '*' && !t[1])
    return 0;
  return *t;
}

int ovfs_flush_raw(OVFS_OVF_HTTP_REQUEST_T *req, const char *s, size_t n)
{
	return req->error = send(req->ipcFd, s, (int)n, 0);
}

int ovfs_end_send_flush(OVFS_OVF_HTTP_REQUEST_T *req)
{
	if (ovfs_flush(req))
		return req->error;
	req->count = 0;
	return 0;
}

int ovfs_end_send(OVFS_OVF_HTTP_REQUEST_T *req)
{
	return ovfs_end_send_flush(req);
}

int ovfs_begin_send(OVFS_OVF_HTTP_REQUEST_T *req)
{
	req->error = 0;

	{
		req->bufidx = 0;
		req->buflen = 0;
	}

	return 0;
}

static const char* http_error(OVFS_OVF_HTTP_REQUEST_T *req, int status)
{
	const char *msg = NULL;

	msg = ovfs_code_str(h_http_error_codes, status);
	if (!msg)
		msg = NULL;

	return msg;
}

int ovfs_flush(OVFS_OVF_HTTP_REQUEST_T *req)
{ 
	size_t n = req->bufidx;
  	if (!n)
  		return req->error = send(req->ipcFd, NULL, (int)0, 0); /* force a zero send for HTTP GET and DELETE */

    req->bufidx = 0;

    return ovfs_flush_raw(req, req->buf, n);
}

int ovfs_send_raw(OVFS_OVF_HTTP_REQUEST_T *req, const char *s, size_t n)
{ 
	if (!n)
    	return 0;
   
	size_t i = sizeof(req->buf) - req->bufidx;
	while (n >= i)
	{ 
	  memcpy((void*)(req->buf + req->bufidx), s, i);
	  req->bufidx = sizeof(req->buf);
	  if (ovfs_flush(req))
	    return req->error;
	  s += i;
	  n -= i;
	  i = sizeof(req->buf);
	}
	memcpy((void*)(req->buf + req->bufidx), (const void*)s, n);
	req->bufidx += n;

  return 0;
}

static int http_send_header(OVFS_OVF_HTTP_REQUEST_T *req, const char *s)
{ const char *t;
  do
  { t = strchr(s, '\n'); /* disallow \n in HTTP headers */
    if (!t)
      t = s + strlen(s);
    if (ovfs_send_raw(req, s, t - s))
      return req->error;
    s = t + 1;
  } while (*t);
  return 0;
}

static int http_post_header(OVFS_OVF_HTTP_REQUEST_T *req, const char *key, const char *val)
{
  if (key)
  { if (http_send_header(req, key))
      return req->error;
    if (val && (ovfs_send_raw(req, ": ", 2) || http_send_header(req, val)))
      return req->error;
  }
  return ovfs_send_raw(req, "\r\n", 2);	
}

static int http_response(OVFS_OVF_HTTP_REQUEST_T *req, int status, int count)
{
	int err;
	char http[32];
	int code = status;
	const char *line;

	snprintf(http, sizeof(http), "HTTP/1.1");
	
	if(!status)
	{
		code = 200;
	}
	line = http_error(req, code);

	snprintf(req->tmpbuf, sizeof(req->tmpbuf), "%s %d %s", http, code, line);
	http_post_header(req, req->tmpbuf, NULL);
	http_post_header(req, "Server", "gSoap/2.8");

	return http_post_header(req, NULL, NULL);
}

int ovfs_response(OVFS_OVF_HTTP_REQUEST_T *req)
{
	if (ovfs_begin_send(req))
		return req->error;

	req->error = http_response(req, 0, 244);
	if (req->error)
		return req->error;

	return 0;
}

const char* ovfs_code_str(const struct soap_code_map *code_map, long code)
{ 
  if (!code_map)
    return NULL;
  while (code_map->code != code && code_map->string)
    code_map++;
  return code_map->string;
}

LONG64 ovfs_code_int(const struct soap_code_map *code_map, const char *str, LONG64 other)
{ 
  if (code_map)
  { while (code_map->string)
    { if (!ovfs_tag_cmp(str, code_map->string)) /* case insensitive */
        return code_map->code;
      code_map++;
    }
  }
  return other;
}