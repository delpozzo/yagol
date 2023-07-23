// ###########################################################################
//          Title: YaGoL Input Subsystem
//         Author: Mike Del Pozzo
//    Description: Handles the mouse, buttons, and grid input for YaGoL.
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

#include "input.h"
#include "grid.h"

#define BUTTONSPACINGX 16
#define BUTTONXSTART 0
#define BUTTONYOFFSET 35

extern int gQuit;
extern int gGridColor;
extern int gPlay;
extern int gSpeed;
extern int gCellSize;
extern int gWinWidth;
extern int gWinHeight;

SDL_Event e;

int gMouseX = 0;
int gMouseY = 0;

Sprite *highlightButtonSprite = NULL;
Sprite *playButtonSprite = NULL;
Sprite *stopButtonSprite = NULL;
Sprite *stepButtonSprite = NULL;
Sprite *clearButtonSprite = NULL;
Sprite *randomButtonSprite = NULL;
Sprite *redButtonSprite = NULL;
Sprite *greenButtonSprite = NULL;
Sprite *blueButtonSprite = NULL;
Sprite *purpleButtonSprite = NULL;
Sprite *yellowButtonSprite = NULL;
Sprite *multiButtonSprite = NULL;
Sprite *speed1ButtonSprite = NULL;
Sprite *speed2ButtonSprite = NULL;
Sprite *speed3ButtonSprite = NULL;
Sprite *speed4ButtonSprite = NULL;
Sprite *speed5ButtonSprite = NULL;
Sprite *sizeSmButtonSprite = NULL;
Sprite *sizeLgButtonSprite = NULL;
Sprite *quitButtonSprite = NULL;

Button playButton;
Button stepButton;
Button clearButton;
Button randomButton;
Button colorButton;
Button speedButton;
Button sizeButton;
Button quitButton;

Button *highlightButton = NULL;

void initInput()
{
    // Quit if there is a problem loading button sprites
    if(loadButtonSprites())
    {
        gQuit = 1;
        return;
    }

    // Configure play button
    if(gPlay)
    {
        playButton.sprite = stopButtonSprite;
    }
    else
    {
        playButton.sprite = playButtonSprite;
    }
    playButton.box.w = playButton.sprite->w;
    playButton.box.h = playButton.sprite->h;
    playButton.clicked = 0;

    // Configure step button
    stepButton.sprite = stepButtonSprite;
    stepButton.box.w = stepButton.sprite->w;
    stepButton.box.h = stepButton.sprite->h;
    stepButton.clicked = 0;

    // Configure clear button
    clearButton.sprite = clearButtonSprite;
    clearButton.box.w = clearButton.sprite->w;
    clearButton.box.h = clearButton.sprite->h;
    clearButton.clicked = 0;

    // Configure random button
    randomButton.sprite = randomButtonSprite;
    randomButton.box.w = randomButton.sprite->w;
    randomButton.box.h = randomButton.sprite->h;
    randomButton.clicked = 0;

    // Configure color button
    switch(gGridColor)
    {
        case REDCELL: colorButton.sprite = redButtonSprite;
            break;
        case GREENCELL: colorButton.sprite = greenButtonSprite;
            break;
        case BLUECELL: colorButton.sprite = blueButtonSprite;
            break;
        case PURPLECELL: colorButton.sprite = purpleButtonSprite;
            break;
        case YELLOWCELL: colorButton.sprite = yellowButtonSprite;
            break;
        case RANDOMCELL: colorButton.sprite = multiButtonSprite;
            break;
    }
    colorButton.box.w = colorButton.sprite->w;
    colorButton.box.h = colorButton.sprite->h;
    colorButton.clicked = 0;

    // Configure speed button
    switch(gSpeed)
    {
        case SPD1: speedButton.sprite = speed1ButtonSprite;
            break;
        case SPD2: speedButton.sprite = speed2ButtonSprite;
            break;
        case SPD3: speedButton.sprite = speed3ButtonSprite;
            break;
        case SPD4: speedButton.sprite = speed4ButtonSprite;
            break;
        case SPD5: speedButton.sprite = speed5ButtonSprite;
            break;
    }
    speedButton.box.w = speedButton.sprite->w;
    speedButton.box.h = speedButton.sprite->h;
    speedButton.clicked = 0;

    // Configure size button
    switch(gCellSize)
    {
        case SMALL: sizeButton.sprite = sizeSmButtonSprite;
            break;
        case LARGE: sizeButton.sprite = sizeLgButtonSprite;
            break;
    }
    sizeButton.box.w = sizeButton.sprite->w;
    sizeButton.box.h = sizeButton.sprite->h;
    sizeButton.clicked = 0;

    // Configure quit button
    quitButton.sprite = quitButtonSprite;
    quitButton.box.w = quitButton.sprite->w;
    quitButton.box.h = quitButton.sprite->h;
    quitButton.clicked = 0;

    // Set button positions
    positionButtons(BUTTONXSTART, gWinHeight - BUTTONYOFFSET);
}

int loadButtonSprites()
{
    // Load button sprites
    highlightButtonSprite = loadSprite("images/buttonHighlight.png");
    playButtonSprite = loadSprite("images/buttonPlay.png");
    stopButtonSprite = loadSprite("images/buttonStop.png");
    stepButtonSprite = loadSprite("images/buttonStep.png");
    clearButtonSprite = loadSprite("images/buttonClear.png");
    randomButtonSprite = loadSprite("images/buttonRandom.png");
    redButtonSprite = loadSprite("images/buttonRed.png");
    greenButtonSprite = loadSprite("images/buttonGreen.png");
    blueButtonSprite = loadSprite("images/buttonBlue.png");
    purpleButtonSprite = loadSprite("images/buttonPurple.png");
    yellowButtonSprite = loadSprite("images/buttonYellow.png");
    multiButtonSprite = loadSprite("images/buttonMulti.png");
    speed1ButtonSprite = loadSprite("images/buttonSpeed1.png");
    speed2ButtonSprite = loadSprite("images/buttonSpeed2.png");
    speed3ButtonSprite = loadSprite("images/buttonSpeed3.png");
    speed4ButtonSprite = loadSprite("images/buttonSpeed4.png");
    speed5ButtonSprite = loadSprite("images/buttonSpeed5.png");
    sizeSmButtonSprite = loadSprite("images/buttonSizeSm.png");
    sizeLgButtonSprite = loadSprite("images/buttonSizeLg.png");
    quitButtonSprite = loadSprite("images/buttonQuit.png");

    // Return 1 if there is a problem loading any of the button sprites
    if(highlightButtonSprite == NULL || playButtonSprite == NULL || stopButtonSprite == NULL || stepButtonSprite == NULL
    || clearButtonSprite == NULL || randomButtonSprite == NULL || redButtonSprite == NULL || greenButtonSprite == NULL
    || blueButtonSprite == NULL || purpleButtonSprite == NULL || yellowButtonSprite == NULL || multiButtonSprite == NULL
    || speed1ButtonSprite == NULL || speed2ButtonSprite == NULL || speed3ButtonSprite == NULL || speed4ButtonSprite == NULL
    || speed5ButtonSprite == NULL || sizeSmButtonSprite == NULL || sizeLgButtonSprite == NULL || quitButtonSprite == NULL)
    {
        return 1;
    }
    else // Return 0 for success
    {
        return 0;
    }
}

void positionButtons(int x, int y)
{
    playButton.box.x = x + BUTTONSPACINGX;
    playButton.box.y = y;

    stepButton.box.x = playButton.box.x + playButton.box.w + BUTTONSPACINGX;
    stepButton.box.y = y;

    clearButton.box.x = stepButton.box.x + stepButton.box.w + BUTTONSPACINGX;
    clearButton.box.y = y;

    randomButton.box.x = clearButton.box.x + clearButton.box.w + BUTTONSPACINGX;
    randomButton.box.y = y;

    colorButton.box.x = randomButton.box.x + randomButton.box.w + BUTTONSPACINGX;
    colorButton.box.y = y;

    speedButton.box.x = colorButton.box.x + colorButton.box.w + BUTTONSPACINGX;
    speedButton.box.y = y;

    sizeButton.box.x = speedButton.box.x + speedButton.box.w + BUTTONSPACINGX;
    sizeButton.box.y = y;

    quitButton.box.x = sizeButton.box.x + sizeButton.box.w + BUTTONSPACINGX;
    quitButton.box.y = y;
}

void updateInput()
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            gQuit = 1;
        }

        if(e.type == SDL_MOUSEMOTION)
        {
            gMouseX = e.motion.x;
            gMouseY = e.motion.y;
        }

        // check if window was resized
        if(checkWindowSize())
        {
            // resize grid to fill new window size
            resizeGrid();

            // and also reposition buttons
            positionButtons(BUTTONXSTART, gWinHeight - BUTTONYOFFSET);
        }

        updateButtons();

        if(!gPlay)
        {
            updateGridInput();
        }
    }
}

void updateButtons()
{
    // Play Button
    if(mouseCollide(&playButton.box))
    {
        highlightButton = &playButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            playButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && playButton.clicked)
        {
            if(gPlay)
            {
                gPlay = 0;
                playButton.sprite = playButtonSprite;
            }
            else
            {
                gPlay = 1;
                playButton.sprite = stopButtonSprite;
            }

            playButton.clicked = 0;
        }
    }
    // Step Button
    else if(mouseCollide(&stepButton.box))
    {
        highlightButton = &stepButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            stepButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && stepButton.clicked)
        {
            if(gPlay)
            {
                gPlay = 0;
                playButton.sprite = playButtonSprite;
            }
            else
            {
                updateGrid();
            }

            stepButton.clicked = 0;
        }
    }
    // Clear Button
    else if(mouseCollide(&clearButton.box))
    {
        highlightButton = &clearButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            clearButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && clearButton.clicked)
        {
            if(gPlay)
            {
                gPlay = 0;
                playButton.sprite = playButtonSprite;
            }

            clearCells();
            clearButton.clicked = 0;
        }
    }
    // Random Button
    else if(mouseCollide(&randomButton.box))
    {
        highlightButton = &randomButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            randomButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && randomButton.clicked)
        {
            if(gPlay)
            {
                gPlay = 0;
                playButton.sprite = playButtonSprite;
            }

            initGrid();
            randomButton.clicked = 0;
        }
    }
    // Color Button
    else if(mouseCollide(&colorButton.box))
    {
        highlightButton = &colorButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            colorButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && colorButton.clicked)
        {
            switch(gGridColor)
            {
                case REDCELL: setGridColor(GREENCELL);
                    colorButton.sprite = greenButtonSprite;
                    break;
                case GREENCELL: setGridColor(BLUECELL);
                    colorButton.sprite = blueButtonSprite;
                    break;
                case BLUECELL: setGridColor(PURPLECELL);
                    colorButton.sprite = purpleButtonSprite;
                    break;
                case PURPLECELL: setGridColor(YELLOWCELL);
                    colorButton.sprite = yellowButtonSprite;
                    break;
                case YELLOWCELL: setGridColor(RANDOMCELL);
                    colorButton.sprite = multiButtonSprite;
                    break;
                case RANDOMCELL: setGridColor(REDCELL);
                    colorButton.sprite = redButtonSprite;
                    break;
            }

            colorButton.clicked = 0;
        }
    }
    // Speed Button
    else if(mouseCollide(&speedButton.box))
    {
        highlightButton = &speedButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            speedButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && speedButton.clicked)
        {
            switch(gSpeed)
            {
                case SPD1: gSpeed = SPD2;
                    speedButton.sprite = speed2ButtonSprite;
                    break;
                case SPD2: gSpeed = SPD3;
                    speedButton.sprite = speed3ButtonSprite;
                    break;
                case SPD3: gSpeed = SPD4;
                    speedButton.sprite = speed4ButtonSprite;
                    break;
                case SPD4: gSpeed = SPD5;
                    speedButton.sprite = speed5ButtonSprite;
                    break;
                case SPD5: gSpeed = SPD1;
                    speedButton.sprite = speed1ButtonSprite;
                    break;
            }

            speedButton.clicked = 0;
        }
    }
    // Size Button
    else if(mouseCollide(&sizeButton.box))
    {
        highlightButton = &sizeButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            sizeButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && sizeButton.clicked)
        {
            switch(gCellSize)
            {
                case SMALL: gCellSize = LARGE;
                    gPlay = 0;
                    playButton.sprite = playButtonSprite;
                    sizeButton.sprite = sizeLgButtonSprite;
                    initGrid();
                    break;
                case LARGE: gCellSize = SMALL;
                    gPlay = 0;
                    playButton.sprite = playButtonSprite;
                    sizeButton.sprite = sizeSmButtonSprite;
                    initGrid();
                    break;
            }

            sizeButton.clicked = 0;
        }
    }
    // Quit Button
    else if(mouseCollide(&quitButton.box))
    {
        highlightButton = &quitButton;

        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            quitButton.clicked = 1;
        }

        if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && quitButton.clicked)
        {
            gQuit = 1;
            quitButton.clicked = 0;
        }
    }
    else
    {
        highlightButton = NULL;
    }
}

void updateGridInput()
{
    Cell *cell = selectedCell();

    if(cell != NULL)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(cell->alive)
            {
                cell->alive = 0;
            }
            else
            {
                cell->alive = 1;
            }
        }
    }
}

void drawButtons()
{
    drawSprite(playButton.sprite, playButton.box.x, playButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(stepButton.sprite, stepButton.box.x, stepButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(clearButton.sprite, clearButton.box.x, clearButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(randomButton.sprite, randomButton.box.x, randomButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(colorButton.sprite, colorButton.box.x, colorButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(speedButton.sprite, speedButton.box.x, speedButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(sizeButton.sprite, sizeButton.box.x, sizeButton.box.y, 0, SDL_FLIP_NONE);
    drawSprite(quitButton.sprite, quitButton.box.x, quitButton.box.y, 0, SDL_FLIP_NONE);

    // Draw border around button if it is moused over
    if(highlightButton != NULL)
    {
        drawSprite(highlightButtonSprite, highlightButton->box.x, highlightButton->box.y, 0, SDL_FLIP_NONE);
    }
}

int mouseCollide(SDL_Rect *box)
{
    if((gMouseX > box->x) && (gMouseX < box->x + box->w) && (gMouseY > box->y) && (gMouseY < box->y + box->h))
    {
        return 1;
    }

    return 0;
}

void closeInput()
{
    playButton.sprite = NULL;
    playButtonSprite = NULL;
    stopButtonSprite = NULL;

    stepButton.sprite = NULL;
    stepButtonSprite = NULL;

    clearButton.sprite = NULL;
    clearButtonSprite = NULL;

    randomButton.sprite = NULL;
    randomButtonSprite = NULL;

    colorButton.sprite = NULL;
    redButtonSprite = NULL;
    greenButtonSprite = NULL;
    blueButtonSprite = NULL;
    purpleButtonSprite = NULL;
    yellowButtonSprite = NULL;
    multiButtonSprite = NULL;

    speedButton.sprite = NULL;
    speed1ButtonSprite = NULL;
    speed2ButtonSprite = NULL;
    speed3ButtonSprite = NULL;
    speed4ButtonSprite = NULL;
    speed5ButtonSprite = NULL;

    sizeButton.sprite = NULL;
    sizeSmButtonSprite = NULL;
    sizeLgButtonSprite = NULL;

    quitButton.sprite = NULL;
    quitButtonSprite = NULL;

    highlightButton = NULL;
    highlightButtonSprite = NULL;
}

