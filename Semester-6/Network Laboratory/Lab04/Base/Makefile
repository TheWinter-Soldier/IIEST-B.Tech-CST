cserv:
	gcc -g -Wall ServerPacketFwd.c -o ServerPacketFwd.out

rserv:
	./ServerPacketFwd.out 9001

ccli:
	gcc -g -Wall ClientPacketGen.c -o ClientPacketGen.out

rcli:
	./ClientPacketGen.out "127.0.0.1" 9001 200 2 40