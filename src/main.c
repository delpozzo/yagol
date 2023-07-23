// ###########################################################################
//          Title: YaGoL (Yet another Game of Life)
//         Author: Mike Del Pozzo
//    Description: Interactive Game of Life sandbox with a retro LED style.
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

#include <time.h>
#include "graphics.h"
#include "grid.h"
#include "input.h"

extern SDL_Renderer *gRenderer;
extern int gQuit;
extern int gPlay;

Sprite *bgSprite = NULL;

void loop()
{
    clearScreen();
    drawBackground(bgSprite);
    if(gPlay)
    {
        updateGrid();
    }
    drawGrid();
    updateInput();
    drawButtons();
    nextFrame();
}

int main(int argc, char * argv[])
{
    time_t t;
    srand((unsigned) time(&t));

    if(initGraphics("YaGoL v1.0.1"))
    {
        initInput();
        initGrid();
        bgSprite = loadSprite("images/bgTile1.png");

        while(!gQuit)
        {
            loop();
        }

        bgSprite = NULL;
    }

    clearGrid();
    closeInput();
    closeGraphics();
    SDL_Quit();

    return 0;
}

