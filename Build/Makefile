All: Clean List Main Map Tree Run

Run:
	gcc ../Clean/*.o -o ../Run/Main

List:
	gcc -c -fPIC -ansi -Wall -Werror -pedantic ../Source/List.c -I../Headers -o ../Clean/List.o

Main:
	gcc -c -fPIC -ansi -Wall -Werror -pedantic ../Source/Main.c -I../Headers -o ../Clean/Main.o

Map:
	gcc -c -fPIC -ansi -Wall -Werror -pedantic ../Source/Map.c -I../Headers -o ../Clean/Map.o

Tree:
	gcc -c -fPIC -ansi -Wall -Werror -pedantic ../Source/Tree.c -I../Headers -o ../Clean/Tree.o

Clean:
	rm -rf ../Clean/* ../Run/*
