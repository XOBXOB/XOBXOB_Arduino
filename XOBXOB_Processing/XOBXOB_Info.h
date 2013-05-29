// XOBXOB server information

#ifndef _xobxob_info_h
#define _xobxob_info_h

#define XOBXOB_SERVER_NAME "www.xobxob.com"
#define XOBXOB_SERVER_PORT 80

static String _LF = "\x0A";
static String HOST_HEADER = _LF + "Host: " + XOBXOB_SERVER_NAME + _LF + _LF;

#endif