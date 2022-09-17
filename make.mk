DEBUG_FLAGS = -Wall -g -O0 -static-pie -I./inc -L./libs
FINAL_FLAGS = -Wall -O3 -static-pie -I./inc -L./libs -DRELEASE

SOURCE_DIR = ./source

debug : dsnake.exe

dsnake.exe : ./source/main.cpp ./obj/menu.o ./obj/game.o
	g++ -c ./source/main.cpp -o ./obj/main.o $(DEBUG_FLAGS)
	g++ ./obj/main.o ./obj/menu.o ./obj/game.o -o dsnake.exe -L./libs -lclirender -lshittykeyboardlistener

./obj/menu.o : ./source/menu/menu.cpp ./inc/menu.h
	g++ -c ./source/menu/menu.cpp -o ./obj/menu.o $(DEBUG_FLAGS)

./obj/game.o : ./source/game.cpp ./inc/game.h ./libs/libclirender.a ./libs/libshittykeyboardlistener.a
	g++ -c ./source/game.cpp -o ./obj/game.o $(DEBUG_FLAGS)

./libs/libclirender.a : ./inc/clirender.h ./source/libs/clirender.c
	gcc -c ./source/libs/clirender.c -o ./obj/clirender.o $(DEBUG_FLAGS)
	ar rcs ./libs/libclirender.a ./obj/clirender.o


./libs/libshittykeyboardlistener.a : ./inc/shittykeyboardlistener.h ./source/libs/shittykeyboardlistener.c
	gcc -c ./source/libs/shittykeyboardlistener.c -o ./obj/shittykeyboardlistener.o $(DEBUG_FLAGS)
	ar rcs ./libs/libshittykeyboardlistener.a ./obj/shittykeyboardlistener.o
