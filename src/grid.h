// ###########################################################################
//          Title: YaGoL Grid Subsystem
//         Author: Mike Del Pozzo
//    Description: Implements Conway's Game of Life rules and handles all
//                 grid/cell related tasks.
//        Version: 1.0.0
//           Date: 21 May 2020
//        License: GPLv3 (see LICENSE)
//
//    YaGoL Copyright (C) 2020 Mike Del Pozzo
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
// ###########################################################################

#ifndef GRID_H
#define GRID_H

#include "graphics.h"

enum CELLCOLORS
{
    REDCELL = 0,
    GREENCELL = 1,
    BLUECELL = 2,
    PURPLECELL = 3,
    YELLOWCELL = 4,
    RANDOMCELL = 5
};

enum CELLSIZE
{
    SMALL = 2,
    LARGE = 1
};

enum GRIDSPEED
{
    SPD1 = 200,
    SPD2 = 100,
    SPD3 = 75,
    SPD4 = 50,
    SPD5 = 25
};

typedef struct CELL_S
{
    Sprite *sprite[2];
    SDL_Rect box;
    int alive;
} Cell;

void initGrid();
int loadGridSprites();
void resizeGrid();
void clearGrid();
void clearCells();
void updateGrid();
void drawGrid();
Cell* selectedCell();
int countLiveNeighbors(int x, int y);
void setGridColor(int color);

#endif

