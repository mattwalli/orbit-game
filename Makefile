all: main.c
	gcc main.c game.c -o orbit -I include -L lib -l SDL2-2.0.0 -l SDL2_image