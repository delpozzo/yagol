// ###########################################################################
//          Title: YaGoL Input Subsystem
//         Author: Mike Del Pozzo
//    Description: Handles the mouse, buttons, and grid input for YaGoL.
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

#ifndef INPUT_H
#define INPUT_H

#include "graphics.h"

typedef struct BUTTON_S
{
    Sprite *sprite;
    SDL_Rect box;
    int clicked;
} Button;

void initInput();
int loadButtonSprites();
void positionButtons(int x, int y);
void updateInput();
void updateButtons();
void updateGridInput();
void drawButtons();
int mouseCollide(SDL_Rect *box);
void closeInput();

#endif

