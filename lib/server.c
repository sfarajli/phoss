#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <cjson/cJSON.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>

static char *link = NULL;

bool server_run(const char *ip, const int port, const char *pl);
bool _server_close();
bool _interpreter_close();
bool _interpreter_start();
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

bool
server_run(const char *ip, const char *port, char *pl)
{
	/* TODO: Implement */
	/* Set the global link variable using `_get_link()` */
	/* Start the interpreter using `_interpreter_start()` */
	/* Call `_queue_handle()` which handles the queue and calls `_request_handle` when needed */
}
