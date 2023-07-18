Compile: Utilities.h Utilities.c Interface.h FileSystem.c Problem.c
	gcc -O3 -c Utilities.c
	gcc -O3 -c FileSystem.c
	gcc -Wall -c Problem.c

link: Utilities.o FileSystem.o Problem.o
	gcc Utilities.o FileSystem.o Problem.o -o Problem.out

run: Problem.out
	clear
	rm dd1
	./Problem.out