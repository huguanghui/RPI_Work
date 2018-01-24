#include "gsoap_log_api.h"

/******************************************************************************/

static void soap_init_logs(struct soap *soap)
{ 
  int i;
  for (i = 0; i < SOAP_MAXLOGS; i++)
  { soap->logfile[i] = NULL;
    soap->fdebug[i] = NULL;
  }
}

/******************************************************************************/

void soap_open_logfile(struct soap *soap, int i)
{ 
    if (soap->logfile[i])
    soap->fdebug[i] = fopen(soap->logfile[i], i < 2 ? "ab" : "a");
}

/******************************************************************************/

static void soap_close_logfile(struct soap *soap, int i)
{ 
  if (soap->fdebug[i])
  { fclose(soap->fdebug[i]);
    soap->fdebug[i] = NULL;
  }
}

/******************************************************************************/

void soap_close_logfiles(struct soap *soap)
{ 
  int i;
  for (i = 0; i < SOAP_MAXLOGS; i++)
    soap_close_logfile(soap, i);
}

/******************************************************************************/

static void soap_set_logfile(struct soap *soap, int i, const char *logfile)
{ 
  const char *s;
  char *t = NULL;
  soap_close_logfile(soap, i);
  s = soap->logfile[i];
  soap->logfile[i] = logfile;
  if (s)
    SOAP_FREE(soap, s);
  if (logfile)
  { size_t l = strlen(logfile) + 1;
    t = (char*)SOAP_MALLOC(soap, l);
    if (t)
      soap_memcpy((void*)t, l, (const void*)logfile, l);
  }
  soap->logfile[i] = t;
}

/******************************************************************************/

void soap_set_recv_logfile(struct soap *soap, const char *logfile)
{ 
  (void)soap; (void)logfile;
  soap_set_logfile(soap, SOAP_INDEX_RECV, logfile);
}

/******************************************************************************/

void soap_set_sent_logfile(struct soap *soap, const char *logfile)
{
  (void)soap; (void)logfile;
  soap_set_logfile(soap, SOAP_INDEX_SENT, logfile);
}

/******************************************************************************/

void soap_set_test_logfile(struct soap *soap, const char *logfile)
{ 
  (void)soap; (void)logfile;
  soap_set_logfile(soap, SOAP_INDEX_TEST, logfile);
}