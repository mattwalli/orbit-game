all: main.c
	gcc main.c -o orbit -I include -L lib -l SDL2-2.0.0