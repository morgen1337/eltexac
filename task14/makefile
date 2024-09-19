all: systemv/client systemv/server POSIX/server POSIX/client chatclient chatserver

chatclient: chatclient.c vars.h
	gcc $< -o $@ -pthread -lncurses

chatserver: chatserver.c vars.h
	gcc $< -o $@

systemv/client: systemv/client.c
	gcc $< -o $@

systemv/server: systemv/server.c
	gcc $< -o $@

POSIX/server: POSIX/server.c
	gcc $< -o $@

POSIX/client: POSIX/client.c
	gcc $< -o $@