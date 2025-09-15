#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <cjson/cJSON.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>

/* TODO: implement queue data structure */

static char *link = NULL;

bool server_run(const char *ip, const int port, const char *pl);
bool _server_close();
bool _interpreter_close();
bool _interpreter_start(const char *pl);
bool _request_handle();
char *_get_link(const char *ip, const int port);
void _queue_handle();

char *
_get_link(char *ip, int port)
{
	char *socket_type = "tcp";
	char *link_format = "%s://%s:%d";

	int link_length = snprintf(NULL, 0, link_format, socket_type, ip, port);
	char *link = malloc(link_length + 1);
	if (link == NULL)
		return NULL;

	if (snprintf(link, link_length + 1, link_format, socket_type, ip, port) < 0)
		return NULL;

	return link;
}

void
_queue_handle()
{
	/* Initialize request queue */
	/* Listen to the given link */
	/* Store all the JSON requests inside of the queue */
	/* If the number of requests exceed the limit give a warning */
	/* Call request_handle one by one for each request in queue */
	/* Do not handle the next request unless the current one is completely finished */
	/* Cancel all the following requests if one request fails */
}

bool
server_run(const char *ip, const char *port, char *pl)
{
	if ((link = _get_link(ip, port)) == NULL)
		return false;

	if (_interpreter_start(pl) == NULL)
		return false;

	_queue_handle();
}
