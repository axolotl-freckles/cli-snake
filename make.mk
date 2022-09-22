DEBUG_FLAGS = -Wall -g -Og -static-pie -I./inc -L./libs
FINAL_FLAGS = -Wall -Os -static-pie -I./inc -L./libs #-DRELEASE

SOURCE_DIR = ./source

debug  : dsnake.exe
release:  snake.exe

dsnake.exe : ./source/main.cpp ./obj/dmenu.o ./obj/dgame.o
	g++ -c ./source/main.cpp -o ./obj/dmain.o $(DEBUG_FLAGS)
	g++ ./obj/dmain.o ./obj/dmenu.o ./obj/dgame.o -o dsnake.exe -L./libs -ldclirender -ldshittykeyboardlistener

snake.exe : ./source/main.cpp ./obj/menu.o ./obj/game.o
	g++ -c ./source/main.cpp -o ./obj/main.o $(FINAL_FLAGS)
	g++ ./obj/main.o ./obj/menu.o ./obj/game.o -o snake.exe -L./libs -lclirender -lshittykeyboardlistener

./obj/dmenu.o : ./source/menu/menu.cpp ./inc/menu.h
	g++ -c ./source/menu/menu.cpp -o ./obj/dmenu.o $(DEBUG_FLAGS)

./obj/menu.o : ./source/menu/menu.cpp ./inc/menu.h
	g++ -c ./source/menu/menu.cpp -o ./obj/menu.o $(FINAL_FLAGS)

./obj/dgame.o : ./source/game.cpp ./inc/game.h ./libs/libdclirender.a ./libs/libdshittykeyboardlistener.a
	g++ -c ./source/game.cpp -o ./obj/dgame.o $(DEBUG_FLAGS)

./obj/game.o : ./source/game.cpp ./inc/game.h ./libs/libclirender.a ./libs/libshittykeyboardlistener.a
	g++ -c ./source/game.cpp -o ./obj/game.o $(FINAL_FLAGS)

./libs/libdclirender.a : ./inc/clirender.h ./source/libs/clirender.c
	gcc -c ./source/libs/clirender.c -o ./obj/dclirender.o $(DEBUG_FLAGS)
	ar rcs ./libs/libdclirender.a ./obj/dclirender.o

./libs/libclirender.a : ./inc/clirender.h ./source/libs/clirender.c
	gcc -c ./source/libs/clirender.c -o ./obj/clirender.o $(FINAL_FLAGS)
	ar rcs ./libs/libclirender.a ./obj/clirender.o

./libs/libdshittykeyboardlistener.a : ./inc/shittykeyboardlistener.h ./source/libs/shittykeyboardlistener.c
	gcc -c ./source/libs/shittykeyboardlistener.c -o ./obj/dshittykeyboardlistener.o $(DEBUG_FLAGS)
	ar rcs ./libs/libdshittykeyboardlistener.a ./obj/dshittykeyboardlistener.o

./libs/libshittykeyboardlistener.a : ./inc/shittykeyboardlistener.h ./source/libs/shittykeyboardlistener.c
	gcc -c ./source/libs/shittykeyboardlistener.c -o ./obj/shittykeyboardlistener.o $(FINAL_FLAGS)
	ar rcs ./libs/libshittykeyboardlistener.a ./obj/shittykeyboardlistener.o
