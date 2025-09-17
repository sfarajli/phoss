.POSIX:

CFLAGS = -lnng -I/usr/include/cjson

server.o: lib/server.c
	${CC} ${CFLAGS} -c -o $@ $<
