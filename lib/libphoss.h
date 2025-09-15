#ifndef _LIBPHOSS_H__
#define _LIBPHOSS_H__

#include <stdbool.h>
#include <sys/types.h>

#include <cjson/cJSON.h>

/* Server side */
bool server_run(const char *ip, const char *port, char *pl);

/* Client side */
bool server_request(const cJSON *request, const char *ip, const char *port);

#endif
