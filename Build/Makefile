CFLAGS = -c -fPIC -ansi -pedantic -Wall -Werror -lm -O3

All: Clean Main Map Tree Run

Run:
	gcc ../Clean/*.o -o ../Main/Main -lm

Main:
	gcc $(CFLAGS) ../Source/Main.c -I../Headers -o ../Clean/Main.o

Map:
	gcc $(CFLAGS) ../Source/Map.c -I../Headers -o ../Clean/Map.o

Tree:
	gcc $(CFLAGS) ../Source/Tree.c -I../Headers -o ../Clean/Tree.o

Clean:
	rm -rf ../Clean/* ../Main/*
