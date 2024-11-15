all: hello/TCPlocalclient hello/TCPlocalserver hello/UDPlocalserver hello/UDPlocalclient hello/TCPinetserver hello/TCPinetclient 1parralelserver/client 1parralelserver/server 2pool/server 2pool/client 3queue/server 3queue/client 4universalserver/server 4universalserver/tcpclient 4universalserver/udpclient broadcast/server broadcast/client multicast/server multicast/client

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

2pool/server: 2pool/server.c
	gcc $< -o $@

2pool/client: 2pool/client.c
	gcc $< -o $@

3queue/server: 3queue/server.c
	gcc $< -o $@

3queue/client: 3queue/client.c
	gcc $< -o $@

4universalserver/server: 4universalserver/server.c
	gcc $< -o $@ -pthread

4universalserver/server: 4universalserver/tcpclient.c
	gcc $< -o $@

4universalserver/server: 4universalserver/udpclient.c
	gcc $< -o $@

broadcast/server: broadcast/server.c
	gcc $< -o $@

broadcast/client: broadcast/client.c
	gcc $< -o $@

multicast/server: multicast/server.c
	gcc $< -o $@

multicast/client: multicast/client.c
	gcc $< -o $@
