all: orbit

orbit: main.o game.o
	gcc main.o game.o -o orbit -I include -L lib -l SDL2-2.0.0 -l SDL2_image

main.o: main.c game.h
	gcc -c main.c

game.o: game.c game.h
	gcc -c game.c

clean:
	rm -f *.o orbit