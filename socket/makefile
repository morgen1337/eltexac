all: hello/TCPlocalclient hello/TCPlocalserver hello/UDPlocalserver hello/UDPlocalclient hello/TCPinetserver hello/TCPinetclient 1parralelserver/client 1parralelserver/server

hello/TCPlocalclient: hello/TCPlocalclient.c
	gcc $< -o $@

hello/TCPlocalserver: hello/TCPlocalserver.c
	gcc $< -o $@

hello/UDPlocalserver: hello/UDPlocalserver.c
	gcc $< -o $@

hello/UDPlocalclient: hello/UDPlocalclient.c
	gcc $< -o $@

hello/TCPinetserver: hello/TCPinetserver.c
	gcc $< -o $@

hello/TCPinetclient: hello/TCPinetclient.c
	gcc $< -o $@

1parralelserver/client: 1parralelserver/client.c
	gcc $< -o $@

1parralelserver/server: 1parralelserver/server.c
	gcc $< -o $@