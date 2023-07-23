# ###########################################################################
#          Title: YaGoL Makefile
#         Author: Mike Del Pozzo
#    Description: The gcc Makefile for YaGoL.
#                 Note: sdl2 and sdl2_image libraries are required.
#        Version: 1.0.1
#           Date: 23 July 2023
#        License: GPLv3 (see LICENSE)
#
#    YaGoL Copyright (C) 2023 Mike Del Pozzo
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    any later version.
# ###########################################################################

CC = gcc
VPATH=./src
OBJ = main.o graphics.o grid.o input.o
SDL_CFLAGS = `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2_image
LFLAGS = -g -o yagol
CFLAGS = -g -Wall -pedantic

all: $(OBJ)
	gcc $(OBJ) $(LFLAGS) $(SDL_LDFLAGS)

clean:
	rm *.o yagol

main.o: main.c
graphics.o: graphics.h graphics.c
grid.o: grid.h grid.c
intput.o: input.h input.c

.c.o:
	gcc $(CFLAGS) $(SDL_CFLAGS) -c $<

