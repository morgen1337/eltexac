all: systemv/client systemv/server POSIX/server POSIX/client chatclient chatserver

chatclient: chatclient.c vars.h
	gcc $< -g3 -O0 -o $@ -pthread -lncurses

chatserver: chatserver.c vars.h
	gcc $< -g3 -O0 -o $@ -pthread

systemv/client: systemv/client.c
	gcc $< -o $@

systemv/server: systemv/server.c
	gcc $< -o $@

POSIX/server: POSIX/server.c
	gcc $< -o $@ -lrt

POSIX/client: POSIX/client.c
	gcc $< -o $@ -lrt