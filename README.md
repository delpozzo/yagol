# YaGoL (Yet another Game of Life)

## About

YaGoL is an interactive Game of Life sandbox. It is written in C and uses the SDL 2.0 library for graphics and input. YaGoL has been tested to compile and run on Linux, Windows, and macOS.

### Features

- Dynamic grid size that automatically resizes to fill the window
- Choice of cell colors (red, green, blue, purple, yellow, multi)
- Individually toggleable cells
- Generate a random grid or clear the grid for a blank canvas
- Play/stop simulation or iterate through one generation at a time
- Adjustable speed setting
- Two cell sizes: small (16x16) or large (32x32)

![Screenshot](screenshots/yagol-red-small.png?raw=true)
![Screenshot](screenshots/yagol-multi-small.png?raw=true)

[Additional Screenshots Here](https://github.com/delpozzo/yagol/tree/master/screenshots)

## Dependencies

### Linux

To compile YaGoL on Linux you will need a gcc compiler as well as the sdl2 and sdl2_image libraries. Your mileage may vary, but here are some examples of installing these dependencies:

**Arch Linux**

`sudo pacman -S gcc sdl2 sdl2_image`

**Debian / Ubuntu**

`sudo apt-get update`

`sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev`

### Windows

I find it easiest to compile YaGoL on Windows using MSYS2. MSYS2 is a collection of tools and libraries providing you with an easy-to-use environment for building, installing, and running native Windows software.

**Windows 11 / Windows 10 / Windows 8.1**

**Step 1:** Install MSYS2 ([https://www.msys2.org](https://www.msys2.org))

**Step 2:** Launch the `MSYS2 MINGW64` application to bring up a terminal

**Step 3:** In the MSYS2 MINGW64 terminal, install dependencies using the following commands:

`pacman -Syu`

`pacman -S git mingw-w64-x86_64-toolchain mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_image make`

### Apple (macOS)

To compile YaGoL on macOS, I find it easiest to install the SDL dependencies using Homebrew. Homebrew is a free and open-source package management system that simplifies the installation of software on macOS.

**macOS Big Sur (11) (or higher)**

**Step 1:** Install Homebrew ([https://brew.sh](https://brew.sh))

**Step 2:** Launch the Terminal application

**Step 3:** In the terminal, install dependencies via brew using the following command:

`brew install sdl2 sdl2_image`

## Building

### Linux

**Step 1:** Clone the YaGoL repository

`git clone https://github.com/delpozzo/yagol.git`

**Step 2:** Enter into the resulting directory from step 1

`cd /path/to/yagol`

**Step 3:** Compile YaGoL

`make`

**Step 4:** Run YaGoL

`./yagol`

### Windows

**Step 1:** Launch the `MSYS2 MINGW64` application to bring up a terminal

**Step 2:** Clone the YaGoL repository

`git clone https://github.com/delpozzo/yagol.git`

**Step 3:** Enter into the resulting directory from step 2

`cd /path/to/yagol`

**Step 4:** Compile YaGoL

`make`

**Step 5:** Run YaGoL

`./yagol.exe`

### Apple (macOS)

**Step 1:** Launch the Terminal application

**Step 2:** Clone the YaGoL repository

`git clone https://github.com/delpozzo/yagol.git`

**Step 3:** Enter into the resulting directory from step 2

`cd /path/to/yagol`

**Step 4:** Compile YaGoL

`make`

**Step 5:** Run YaGoL

`./yagol`

## Instructions

YaGoL launches by default in a 1024x768 window. This window can be resized and it can even be stretched to span multiple displays. The grid will automatically grow or shrink to fill the window.

The starting grid is a random seed of red cells at 3X speed. You can press the play button to start the simulation, or customize the grid using the controls below.

### Controls

- **Grid Cells** - When the simulation is stopped, cells can be individually toggled on or off (alive or dead).
- **Play/Stop** - Play or stop the game of life simulation.
- **Step** - Iterate one generation at a time.
- **Clear** - Clears the grid by setting all cells to dead.
- **Random** - Randomly seed the grid with live cells.
- **Color** - Change cell color. Choice of red, green, blue, purple, yellow, or multi (random colors).
- **Spd** - Change simulation speed (1X to 5X). Default is 3X.
- **Size** - Change cell size to small (16x16) or large (32x32). Default is small.
- **Quit** - Exit the YaGoL application.

## FAQ

**The application won't launch and/or I am getting "Unable to load image" errors!**

This is due to the fact that YaGoL currently uses a relative path for loading the sprites in the `images/` directory. It's on my to-do list to come up with a solution so this won't be a problem in the future. In the meantime, enter the yagol directory first, then run the application:

`cd /path/to/yagol`

`./yagol`

You can create a shell script to automate this which can be called from menu/desktop shortcuts:

yagol.sh example:
```
#!/bin/sh

cd /path/to/yagol
./yagol
```

Don't forget to set the execute bit on the shell script you create:

`chmod +x yagol.sh`

**What is the maximum number of cells that YaGoL can handle?**

The maximum number of cells is defined in grid.c:

```
#define MAXCELLSX 550
#define MAXCELLSY 550
```

This results in a total of 302,500 cells which should be enough to fill an 8K display with small (16x16) cells, or two 8K displays with large (32x32) cells.

Feel free to play around with the MAXCELLS values. Just keep in mind that if you increase these values more memory will be required by the application.

**What is the Game of Life?**

(From the [Wikipedia article](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life))

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

- Any live cell with two or three live neighbours survives.
- Any dead cell with three live neighbours becomes a live cell.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.

## License

YaGoL Copyright (C) 2023 Mike Del Pozzo

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

See [LICENSE](LICENSE) for details.
