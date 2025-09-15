.POSIX:

server.o: lib/server.c
	${CC} ${CFLAGS} -c -o $@ $<
