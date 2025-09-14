<!-- TODO: handle if error is only sent to the client that sent the corresponding request, or to all the other ones if they are in the queue. -->
<!-- TODO: Specify C-C behaviour  -->

# Overview
A simple client-server protocol for executing code for interactive programming.

## Transport
-   Socket type: TCP
-   IP: localhost (default)
-   Port: 5252 (default)
-   Encoding: UTF-8 text
-   Framing: Line-delimited JSON messages

## Roles
-   Server
    -   Accepts multiple client connections.
    -   Executes requests one at a time.
    -   Requires a reply if standard input is used.
    -   Can send stream or multiple outputs (intermediate results, logs, progress updates, etc.).
    -   Sends a `execute reply` to indicate execution is complete along with meta-data (i.e execution time). 
    -   Stores where requests are from and replies accordingly.
    -   Intermediate outputs and execute replies have the same id as the corresponding execution request.
    -   Maintains a FIFO request queue
    -   If an error has occurred all requests in queue canceled and error an message is sent to the client(s). 
-   Client
    -   Sends requests to the server.
    -   Waits for replies not outputs.

## Message Format
Each message is a single JSON object serialized to one line.

- General structure:
    ``` json
    {
      "type": "<string>",      // message type
      "id": "<uuid>",          // unique per request
      "payload": { ... }       // message-specific data
    }
    ```

## Message Types

### Client -> Server

1.  Execute_request
    ``` json
    {
      "type": "execute_request",
      "id": "12345",
      "payload": {
        "code": "print('hello')"
      }
    }
    ```

    Executes the given code string.

2.  Shutdown request
    ``` json
    {
      "type": "shutdown_request",
      "id": "12345",
      "payload": {}
    }
    ```

    Requests the server to shut down gracefully.

3. Ping
    ``` json
    {
        "type": "ping",
        "id": "12345"
        "payload": {
            "ip": "127.0.0.1"
        }
    }
    ```

    Check if the server is up.

4. Reply to `stdin_request`
    ``` json
    {
      "type": "stdin_reply",
      "id": "12345",            // must match the request id
      "payload": {
        "value": "Alice"        // user-provided input string
      }
    }
    ```

### Server -> Client

1.  Execute reply 
    ``` json
    {
      "type": "execute_reply",
      "id": "12345",
      "payload": {
        "status": "ok",
        "result": "hello\n"
      }
    }
    ```

    Reply to an `execute_request`{.verbatim}.

2.  Output
    ``` json
    {
      "type": "output",
      "id": "12345",
      "payload": {
        "stream": "stdout",
        "text": "hello\n"
      }
    }
    ```

    Asynchronous output (e.g., from stdout/stderr).

3.  Shutdown reply 
    ``` json
    {
        "type": "shutdown_reply",
        "id": "12345",
        "payload": {
            "status": "ok"
      }
    }
    ```

    Reply to a shutdown request.

4. Pong
    ``` json
    {
        "type": "pong",
        "id": "12345",
    }
    ```

    Reply if the server is up.

5. Request stdin message
    ``` json
    {
        "type": "stdin_request",
        "id": "12345",                       // execution request id
        "payload": {
            "prompt": "Enter your name: ",   // message shown to the user
            "hide_input": false              // if true, hide input (e.g. passwords)
      }
    }
    ```

6.  Errors
    ``` json
    {
        "type": "error",
        "error": "invalid_message"
    }
    ```
