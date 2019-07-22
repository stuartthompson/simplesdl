# Simple SDL
Exploring SDL to render 2D graphics.

## Compiling on Linux
g++ main.gpp -D_REENTRANT -I/usr/include/SDL2 -lSDL2

## Compiling on OSX
g++ main.cpp -D_THREAD_SAFE -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2 -std=c++11
