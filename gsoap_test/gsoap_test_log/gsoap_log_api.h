#ifndef GSOAP_LOG_API_H
#define GSOAP_LOG_API_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define HPT(x...) do{printf("[%s:%d]", __FUNCTION__, __LINE__);printf(x);}while(0)

#ifndef SOAP_MALLOC                     /* use libc malloc */
# define SOAP_MALLOC(soap, size) malloc(size)
#endif

#ifndef SOAP_FREE                       /* use libc free */
# define SOAP_FREE(soap, ptr) free((void*)(ptr))
#endif

#ifdef SOAP_DEBUG
# ifndef SOAP_MESSAGE
#  define SOAP_MESSAGE fprintf
# endif
# ifndef DBGLOG
#  ifdef DEBUG_STAMP
#   ifdef WIN32
#    define DBGLOG(DBGFILE, CMD) \
{ if (soap)\
  { if (!soap->fdebug[SOAP_INDEX_##DBGFILE])\
      soap_open_logfile((struct soap*)soap, SOAP_INDEX_##DBGFILE);\
    if (soap->fdebug[SOAP_INDEX_##DBGFILE])\
    { FILE *fdebug = soap->fdebug[SOAP_INDEX_##DBGFILE];\
      SYSTEMTIME _localTime;\
      ::GetLocalTime(&_localTime); \
      fprintf(fdebug, "%02d%02d%02d %02d:%02d:%02d.%03d|", (int)_localTime.wYear%100, (int)_localTime.wMonth, (int)_localTime.wDay, (int)_localTime.wHour, (int)_localTime.wMinute, (int)_localTime.wSecond, (int)_localTime.wMilliseconds);\
      CMD;\
      fflush(fdebug);\
    }\
  }\
}
#   else
#    define DBGLOG(DBGFILE, CMD) \
{ if (soap)\
  { if (!soap->fdebug[SOAP_INDEX_##DBGFILE])\
      soap_open_logfile((struct soap*)soap, SOAP_INDEX_##DBGFILE);\
    if (soap->fdebug[SOAP_INDEX_##DBGFILE])\
    { FILE *fdebug = soap->fdebug[SOAP_INDEX_##DBGFILE];\
      struct timeval _tv;\
      struct tm _tm;\
      gettimeofday(&_tv, NULL);\
      localtime_r(&_tv.tv_sec, &_tm);\
      fprintf(fdebug, "%02d%02d%02d %02d:%02d:%02d.%06ld|", (int)_tm.tm_year%100, (int)_tm.tm_mon+1, (int)_tm.tm_mday, (int)_tm.tm_hour, (int)_tm.tm_min, (int)_tm.tm_sec, (long)_tv.tv_usec);\
      CMD;\
      fflush(fdebug);\
    }\
  }\
}
#   endif
#  else
#   define DBGLOG(DBGFILE, CMD) \
{ if (soap)\
  { if (!soap->fdebug[SOAP_INDEX_##DBGFILE])\
      soap_open_logfile((struct soap*)soap, SOAP_INDEX_##DBGFILE);\
    if (soap->fdebug[SOAP_INDEX_##DBGFILE])\
    { FILE *fdebug = soap->fdebug[SOAP_INDEX_##DBGFILE];\
      CMD;\
      fflush(fdebug);\
    }\
  }\
}
#  endif
# endif
# ifndef DBGMSG
#  define DBGMSG(DBGFILE, MSG, LEN) \
{ if (soap)\
  { if (!soap->fdebug[SOAP_INDEX_##DBGFILE])\
      soap_open_logfile((struct soap*)soap, SOAP_INDEX_##DBGFILE);\
    if (soap->fdebug[SOAP_INDEX_##DBGFILE])\
    { fwrite((void*)(MSG), 1, (size_t)(LEN), soap->fdebug[SOAP_INDEX_##DBGFILE]);\
      fflush(soap->fdebug[SOAP_INDEX_##DBGFILE]);\
    }\
  }\
}
# endif
# ifndef DBGFUN
#  define DBGFUN(FNAME) DBGLOG(TEST, SOAP_MESSAGE(fdebug, "%s(%d): %s()\n", __FILE__, __LINE__, FNAME))
#  define DBGFUN1(FNAME, FMT, ARG) DBGLOG(TEST, SOAP_MESSAGE(fdebug, "%s(%d): %s(" FMT ")\n", __FILE__, __LINE__, FNAME, (ARG)))
#  define DBGFUN2(FNAME, FMT1, ARG1, FMT2, ARG2) DBGLOG(TEST, SOAP_MESSAGE(fdebug, "%s(%d): %s(" FMT1 ", " FMT2 ")\n", __FILE__, __LINE__, FNAME, (ARG1), (ARG2)))
#  define DBGFUN3(FNAME, FMT1, ARG1, FMT2, ARG2, FMT3, ARG3) DBGLOG(TEST, SOAP_MESSAGE(fdebug, "%s(%d): %s(" FMT1 ", " FMT2 ", " FMT3 ")\n", __FILE__, __LINE__, FNAME, (ARG1), (ARG2), (ARG3)))
#  define DBGFUN4(FNAME, FMT1, ARG1, FMT2, ARG2, FMT3, ARG3, FMT4, ARG4) DBGLOG(TEST, SOAP_MESSAGE(fdebug, "%s(%d): %s(" FMT1 ", " FMT2 ", " FMT3 ", " FMT4 ")\n", __FILE__, __LINE__, FNAME, (ARG1), (ARG2), (ARG3), (ARG4)))
# endif
# ifndef DBGHEX
#  define DBGHEX(DBGFILE, MSG, LEN) \
{ if (soap)\
  { if (!soap->fdebug[SOAP_INDEX_##DBGFILE])\
      soap_open_logfile(soap, SOAP_INDEX_##DBGFILE);\
    if (soap->fdebug[SOAP_INDEX_##DBGFILE])\
    { int i; char *s;\
      for (s = (char*)(MSG), i = (LEN); i; i--)\
        fprintf(soap->fdebug[SOAP_INDEX_##DBGFILE], "%2.2X  ", (int)*s++&0xFF);\
      fflush(soap->fdebug[SOAP_INDEX_##DBGFILE]);\
    }\
  }\
}
# endif
#else
# define DBGLOG(DBGFILE, CMD)
# define DBGMSG(DBGFILE, MSG, LEN)
# define DBGFUN(FNAME)
# define DBGFUN1(FNAME, FMT, ARG)
# define DBGFUN2(FNAME, FMT1, ARG1, FMT2, ARG2)
# define DBGFUN3(FNAME, FMT1, ARG1, FMT2, ARG2, FMT3, ARG3)
# define DBGFUN4(FNAME, FMT1, ARG1, FMT2, ARG2, FMT3, ARG3, FMT4, ARG4)
# define DBGHEX(DBGFILE, MSG, LEN)
#endif

# define SOAP_MAXLOGS     (3) /* max number of debug logs per struct soap environment */
# define SOAP_INDEX_RECV  (0)
# define SOAP_INDEX_SENT  (1)
# define SOAP_INDEX_TEST  (2)

struct soap
{
    const char *logfile[SOAP_MAXLOGS];
    FILE *fdebug[SOAP_MAXLOGS];
//    struct soap_mlist *mht[SOAP_PTRHASH];
};

#endif /* gsoap_log_api.h */
