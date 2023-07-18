cserv:
	gcc -g -Wall ServerPacketFwd.c -o ServerPacketFwd.out

rserv:
	./ServerPacketFwd.out 12005

ccli:
	gcc -g -Wall ClientPacketGen.c -o ClientPacketGen.out

rcli:
	./ClientPacketGen.out "127.0.0.1" 12005 300 8 30