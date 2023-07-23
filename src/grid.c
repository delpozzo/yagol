// ###########################################################################
//          Title: YaGoL Grid Subsystem
//         Author: Mike Del Pozzo
//    Description: Implements Conway's Game of Life rules and handles all
//                 grid/cell related tasks.
//        Version: 1.0.1
//           Date: 23 July 2023
//        License: GPLv3 (see LICENSE)
//
//    YaGoL Copyright (C) 2023 Mike Del Pozzo
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
// ###########################################################################

#include "grid.h"
#include "input.h"

#define MAXCELLSX 550
#define MAXCELLSY 550
#define CELLSPACINGX 2
#define CELLSPACINGY 2

extern int gWinWidth;
extern int gWinHeight;
extern int gQuit;

Sprite *deadSprite = NULL;
Sprite *redSprite = NULL;
Sprite *greenSprite = NULL;
Sprite *blueSprite = NULL;
Sprite *purpleSprite = NULL;
Sprite *yellowSprite = NULL;
Sprite *highlightSprite = NULL;

int gLoopEdges = 0; // Edge looping needs refinement, disabled for now
int gGridColor = REDCELL; // Default grid color is red
int gPlay = 0; // Game is stopped by default on launch
int gSpeed = SPD3; // Default speed is 3
int gCellSize = SMALL; // Default cell size is small

Cell CurrentGrid[MAXCELLSX][MAXCELLSY];
Cell NextGrid[MAXCELLSX][MAXCELLSY];

int gridSizeX;
int gridSizeY;

void initGrid()
{
    // Quit if there is a problem loading grid sprites
    if(loadGridSprites())
    {
        gQuit = 1;
        return;
    }

    for(int x = 0; x < MAXCELLSX; x++)
    {
        for(int y = 0; y < MAXCELLSY; y++)
        {
            CurrentGrid[x][y].sprite[0] = deadSprite;
            CurrentGrid[x][y].box.w = CurrentGrid[x][y].sprite[0]->w;
            CurrentGrid[x][y].box.h = CurrentGrid[x][y].sprite[0]->h;
            CurrentGrid[x][y].box.x = (CELLSPACINGX * (x+1)) + (CurrentGrid[x][y].box.w * x);
            CurrentGrid[x][y].box.y = (CELLSPACINGY * (y+1)) + (CurrentGrid[x][y].box.h * y);
            CurrentGrid[x][y].alive = rand() % 2;
        }
    }

    memcpy(NextGrid, CurrentGrid, sizeof(CurrentGrid));

    resizeGrid();
    setGridColor(gGridColor);
}

int loadGridSprites()
{
    if(gCellSize == LARGE)
    {
        deadSprite = loadSprite("images/ledOffLG.png");
        redSprite = loadSprite("images/ledRedLG.png");
        greenSprite = loadSprite("images/ledGreenLG.png");
        blueSprite = loadSprite("images/ledBlueLG.png");
        purpleSprite = loadSprite("images/ledPurpleLG.png");
        yellowSprite = loadSprite("images/ledYellowLG.png");
        highlightSprite = loadSprite("images/ledHighlightLG.png");
    }
    else
    {
        deadSprite = loadSprite("images/ledOff.png");
        redSprite = loadSprite("images/ledRed.png");
        greenSprite = loadSprite("images/ledGreen.png");
        blueSprite = loadSprite("images/ledBlue.png");
        purpleSprite = loadSprite("images/ledPurple.png");
        yellowSprite = loadSprite("images/ledYellow.png");
        highlightSprite = loadSprite("images/ledHighlight.png");
    }

    // Return 1 if there is a problem loading any of the grid sprites
    if(deadSprite == NULL || redSprite == NULL || greenSprite == NULL || blueSprite == NULL
    || purpleSprite == NULL || yellowSprite == NULL || highlightSprite == NULL)
    {
        return 1;
    }
    else // Return 0 for success
    {
        return 0;
    }
}

void resizeGrid()
{
    if(deadSprite != NULL)
    {
        gridSizeX = gWinWidth / (deadSprite->w + CELLSPACINGX);
        if(gridSizeX > MAXCELLSX)
        {
            gridSizeX = MAXCELLSX;
        }

        gridSizeY = (gWinHeight / (deadSprite->h + CELLSPACINGY)) - gCellSize;
        if(gridSizeY > MAXCELLSY)
        {
            gridSizeY = MAXCELLSY;
        }
    }
}

void clearGrid()
{
    for(int x = 0; x < MAXCELLSX; x++)
    {
        for(int y = 0; y < MAXCELLSY; y++)
        {
            CurrentGrid[x][y].sprite[0] = NULL;
            CurrentGrid[x][y].sprite[1] = NULL;
            CurrentGrid[x][y].alive = 0;
        }
    }

    memcpy(NextGrid, CurrentGrid, sizeof(CurrentGrid));

    deadSprite = NULL;
    redSprite = NULL;
    greenSprite = NULL;
    blueSprite = NULL;
    purpleSprite = NULL;
    yellowSprite = NULL;
    highlightSprite = NULL;
}

void clearCells()
{
    for(int x = 0; x < MAXCELLSX; x++)
    {
        for(int y = 0; y < MAXCELLSY; y++)
        {
            CurrentGrid[x][y].alive = 0;
        }
    }

    memcpy(NextGrid, CurrentGrid, sizeof(CurrentGrid));
}

void updateGrid()
{
    for(int y = 0; y < gridSizeY; y++)
    {
        for(int x = 0; x < gridSizeX; x++)
        {
            int n = countLiveNeighbors(x, y);
            int c = CurrentGrid[x][y].alive;

            // A live cell dies unless it has exactly 2 or 3 live neighbors
            // A dead cell remains dead unless it has exactly 3 live neighbors
            NextGrid[x][y].alive = (c && (n == 2 || n == 3)) || (!c && n == 3);
        }
    }

    // Copy next grid to current grid
    memcpy(CurrentGrid, NextGrid, sizeof(CurrentGrid));

    // Delay based on gSpeed if playing
    if(gPlay)
    {
        SDL_Delay(gSpeed);
    }
}

void drawGrid()
{
    for(int x = 0; x < gridSizeX; x++)
    {
        for(int y = 0; y < gridSizeY; y++)
        {
            drawSprite(CurrentGrid[x][y].sprite[CurrentGrid[x][y].alive], CurrentGrid[x][y].box.x, CurrentGrid[x][y].box.y, 0, SDL_FLIP_NONE);

            if(!gPlay && mouseCollide(&CurrentGrid[x][y].box))
            {
                drawSprite(highlightSprite, CurrentGrid[x][y].box.x - CELLSPACINGX, CurrentGrid[x][y].box.y - CELLSPACINGY, 0, SDL_FLIP_NONE);
            }
        }
    }
}

Cell* selectedCell()
{
    for(int x = 0; x < gridSizeX; x++)
    {
        for(int y = 0; y < gridSizeY; y++)
        {
            if(mouseCollide(&CurrentGrid[x][y].box))
            {
                return &CurrentGrid[x][y];
            }
        }
    }

    return NULL;
}

int countLiveNeighbors(int x, int y)
{
    // The number of live neighbors
    int value = 0;

    // This nested loop enumerates the 9 cells in the specified cells neighborhood
    for(int j = -1; j <= 1; j++)
    {
        // If gLoopEdges is set to 0 and y+j is off the board, continue
        if((!gLoopEdges && y + j < 0) || y + j >= gridSizeY)
        {
            continue;
        }

        // Loop around the edges if y+j is off the board
        int k = (y + j + gridSizeY) % gridSizeY;

        for(int i = -1; i <= 1; i++)
        {
            // If gLoopEdges is set to 0 and x+i is off the board, continue
            if((!gLoopEdges && x + i < 0) || x + i >= gridSizeX)
            {
                continue;
            }

            // Loop around the edges if x+i is off the board
            int h = (x + i + gridSizeX) % gridSizeX;

            // Count the neighbor cell at (h,k) if it is alive
            value += CurrentGrid[h][k].alive ? 1 : 0;
        }
    }

    // Subtract 1 if (x,y) is alive since we counted it as a neighbor
    return value - (CurrentGrid[x][y].alive ? 1 : 0);
}

void setGridColor(int color)
{
    gGridColor = color;

    for(int x = 0; x < MAXCELLSX; x++)
    {
        for(int y = 0; y < MAXCELLSY; y++)
        {
            switch(color)
            {
                case REDCELL: CurrentGrid[x][y].sprite[1] = redSprite;
                    break;
                case GREENCELL: CurrentGrid[x][y].sprite[1] = greenSprite;
                    break;
                case BLUECELL: CurrentGrid[x][y].sprite[1] = blueSprite;
                    break;
                case PURPLECELL: CurrentGrid[x][y].sprite[1] = purpleSprite;
                    break;
                case YELLOWCELL: CurrentGrid[x][y].sprite[1] = yellowSprite;
                    break;
                case RANDOMCELL:
                    switch(rand() % 5)
                    {
                        case REDCELL: CurrentGrid[x][y].sprite[1] = redSprite;
                            break;
                        case GREENCELL: CurrentGrid[x][y].sprite[1] = greenSprite;
                            break;
                        case BLUECELL: CurrentGrid[x][y].sprite[1] = blueSprite;
                            break;
                        case PURPLECELL: CurrentGrid[x][y].sprite[1] = purpleSprite;
                            break;
                        case YELLOWCELL: CurrentGrid[x][y].sprite[1] = yellowSprite;
                            break;
                    }
                    break;
            }
        }
    }

    memcpy(NextGrid, CurrentGrid, sizeof(CurrentGrid));
}

