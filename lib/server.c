#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <cjson/cJSON.h>
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>

#define REQUEST_LIMIT 100

typedef struct {
	cJSON *items[REQUEST_LIMIT];
	int front;
	int rear;
	int size;
} JSONQueue;

static JSONQueue *request_queue = NULL;
static char *link = NULL;

bool server_run(const char *ip, const int port, const char *pl);
bool _server_close(void);
bool _interpreter_close(void);
bool _interpreter_start(const char *pl);
bool _request_handle(void);
char *_get_link(const char *ip, const int port);
void _queue_handle(void);

void _request_queue_init(void);
void _request_queue_free(void);
bool _request_queue_isempty(void);
bool _request_queue_isfull(void);
void _request_enqueue(cJSON *request_json);
cJSON *_request_dequeue(void);
cJSON *_request_queue_peek(void);

bool
_request_queue_init(void)
{
	request_queue = (JSONQueue*)malloc(sizeof(JSONQueue));
	if (!request_queue)
		return false;

	request_queue->front = 0;
	request_queue->rear = -1;
	request_queue->size = 0;

	return true;
}

void
_request_queue_free()
{
	while (!request_queue_isempty())
		cJSON_Delete(_request_dequeue);
}

bool
_request_queue_isfull(void)
{
	return request_queue->size == MAX_QUEUE_SIZE;
}

bool
_request_queue_isempty(void)
{
	return request_queue->size == 0;
}

void
_request_enqueue(cJSON *request_json)
{
	if (request_queue_isfull())
		return;

	request_queue->rear = (request_queue->rear + 1) % REQUEST_LIMIT;
	request_queue->items[request_queue->rear] = request_json;
	request_queue->size++;
}

cJSON *
_request_dequeue(void)
{
	if (request_queue_isfull())
		return NULL;

	cJSON *request_json= request_queue->items[request_queue->front];
	request_queue->front = (request_queue->front + 1) % REQUEST_LIMIT;
	request_queue->size--;
	return request_json;
}

cJSON *
_request_queue_peek(void)
{
    	if (request_queue_isempty())
        	return NULL;

	return request_queue->items[request_queue->front];
}

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
	if (!_request_queue_init())
		return;

	/* Listen to the link */
	/* Store all the JSON requests in the queue */
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
