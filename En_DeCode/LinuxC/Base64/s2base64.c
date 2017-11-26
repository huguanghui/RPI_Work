#include "common.h"

const char soap_base64o[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *s2base64(const unsigned char *s, char *t, int n)
{
  printf("N:%d\n", n);
  int i;
  unsigned long m;
  char *p;
  if (!t)
    t = (char*)malloc((n + 2) / 3 * 4 + 1);
  if (!t)
    return NULL;
  p = t;
  t[0] = '\0';
  if (!s)
    return p;
  for (; n > 2; n -= 3, s += 3)
  { m = s[0];
    m = (m << 8) | s[1];
    m = (m << 8) | s[2];
    for (i = 4; i > 0; m >>= 6)
      t[--i] = soap_base64o[m & 0x3F];
    t += 4;
  }
  t[0] = '\0';
  if (n > 0) /* 0 < n <= 2 implies that t[0..4] is allocated (base64 scaling formula) */
  { m = 0;
    for (i = 0; i < n; i++)
      m = (m << 8) | *s++;
    for (; i < 3; i++)
      m <<= 8;
    for (i = 4; i > 0; m >>= 6)
      t[--i] = soap_base64o[m & 0x3F];
    for (i = 3; i > n; i--)
      t[i] = '=';
    t[4] = '\0';
  }
  return p;
}