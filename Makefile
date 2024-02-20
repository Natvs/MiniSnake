
mygame.exe: main.o grid.o player.o goal.o gamedatas.o colors.o
	gcc -o mygame.exe main.o gamedatas.o grid.o player.o goal.o colors.o $(shell pkg-config --cflags --libs sdl2)

main.o: src/main.c include/main.h include/colors.h
	gcc -c -Wall src/main.c $(shell pkg-config --cflags --libs sdl2)

gamedatas.o: src/gamedatas.c include/gamedatas.h
	gcc -c -Wall src/gamedatas.c $(shell pkg-config --cflags --libs sdl2)

grid.o: src/grid.c include/grid.h
	gcc -c -Wall src/grid.c $(shell pkg-config --cflags --libs sdl2)

player.o: src/player.c include/player.h include/colors.h
	gcc -c -Wall src/player.c $(shell pkg-config --cflags --libs sdl2)

goal.o: src/goal.c include/goal.h
	gcc -c -Wall src/goal.c $(shell pkg-config --cflags --libs sdl2)

colors.o: src/colors.c include/colors.h
	gcc -c -Wall src/colors.c $(shell pkg-config --cflags --libs sdl2)

clean-fast:
	rm -f *.o include/*h.gch

clean: clean-fast
	rm -f mygame.exe

run: mygame.exe clean-fast
	./mygame.exe

