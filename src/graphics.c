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

#include "graphics.h"

#define MAXSPRITES 50
#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
int gQuit = 0;
int gWinWidth;
int gWinHeight;
int spritesLoaded = 0;

Sprite SpriteList[MAXSPRITES];

int initGraphics(char *windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL)
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 0;
    }

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }

    SDL_GetWindowSize(gWindow, &gWinWidth, &gWinHeight);

    initSpriteList();

    return 1;
}

void initSpriteList()
{
    for(int i = 0; i < MAXSPRITES; i++)
    {
        SpriteList[i].image = NULL;
        strncpy(SpriteList[i].filename, "", 64);
        SpriteList[i].w = 0;
        SpriteList[i].h = 0;
        SpriteList[i].used = 0;
    }
}

Sprite* loadSprite(char *filename)
{
    SDL_Surface *loadedSurface = NULL;

    for(int i = 0; i < MAXSPRITES; i++)
    {
        if(strncmp(filename, SpriteList[i].filename, 64) == 0)
        {
            return &SpriteList[i];
        }
    }

    for(int i = 0; i < MAXSPRITES; i++)
    {
        if(!SpriteList[i].used)
        {
            loadedSurface = IMG_Load(filename);
            if(loadedSurface == NULL)
            {
                printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
                return NULL;
            }

            SpriteList[i].image = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
            loadedSurface = NULL;
            if(SpriteList[i].image == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
                return NULL;
            }

            strncpy(SpriteList[i].filename, filename, 64);
	        SDL_QueryTexture(SpriteList[i].image, NULL, NULL, &SpriteList[i].w, &SpriteList[i].h);
            SpriteList[i].used = 1;

            spritesLoaded++;
            //printf("Sprites loaded: %i\n", spritesLoaded);

            return &SpriteList[i];
        }
    }

    printf("Error: Sprite limit reached");
    return NULL;
}

void freeSprite(Sprite *sprite)
{
    if(sprite->image != NULL)
    {
        SDL_DestroyTexture(sprite->image);
        sprite->image = NULL;

        spritesLoaded--;
        //printf("Sprites loaded: %i\n", spritesLoaded);
    }

    strncpy(sprite->filename, "", 64);
    sprite->w = 0;
    sprite->h = 0;
    sprite->used = 0;
}

void drawSprite(Sprite *sprite, int x, int y, double rot, SDL_RendererFlip flip)
{
    if(sprite == NULL)
    {
        printf("Tried to draw sprite that was null! SDL Error: %s\n", SDL_GetError());
        gQuit = 1;
        return;
    }

    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = sprite->w;
    dest.h = sprite->h;

    SDL_RenderCopyEx(gRenderer, sprite->image, NULL, &dest, rot, NULL, flip);
}

void drawBackground(Sprite *sprite)
{
    if(sprite == NULL)
    {
        printf("Tried to draw bg that was null! SDL Error: %s\n", SDL_GetError());
        gQuit = 1;
        return;
    }

    int xTiles = 1 + (gWinWidth / sprite->w);
    int yTiles = 1 + (gWinHeight / sprite->h);

    for(int i = 0; i < xTiles * yTiles; i++)
    {
        int x = i % xTiles;
        int y = i / xTiles;
        drawSprite(sprite, x * sprite->w, y * sprite->h, 0, SDL_FLIP_NONE);
    }
}

int checkWindowSize()
{
    int width;
    int height;

    SDL_GetWindowSize(gWindow, &width, &height);

    if(gWinWidth != width || gWinHeight != height)
    {
        // set globals and return 1 if window has been resized
        gWinWidth = width;
        gWinHeight = height;
        return 1;
    }

    return 0;
}

void closeGraphics()
{
    for(int i = 0; i < MAXSPRITES; i++)
    {
        freeSprite(&SpriteList[i]);
    }

    if(gRenderer != NULL)
    {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }

    if(gWindow != NULL)
    {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }

    IMG_Quit();
}

