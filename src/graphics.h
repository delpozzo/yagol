// ###########################################################################
//          Title: YaGoL Graphics Subsystem
//         Author: Mike Del Pozzo
//    Description: Handles all graphics-related items for YaGoL including
//                 the SDL2 window, renderer, loading/drawing sprites, and
//                 background tiling.
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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct SPRITE_S
{
    SDL_Texture *image;
    char filename[64];
    int w;
    int h;
    int used;
} Sprite;

int initGraphics(char *windowTitle);
void initSpriteList();
Sprite* loadSprite(char *filename);
void freeSprite(Sprite *sprite);
void drawSprite(Sprite *sprite, int x, int y, double rot, SDL_RendererFlip flip);
void drawBackground(Sprite *sprite);
int checkWindowSize();
void closeGraphics();

#endif

