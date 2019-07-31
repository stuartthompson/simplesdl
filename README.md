# Simple SDL
Exploring SDL to render 2D and 3D graphics scenes.
The primary purpose of this project is to learn more about lower level graphics programming.

## Compiling on Linux
g++ main.cpp -D_REENTRANT -I/usr/local/include/SDL2 -I/usr/local/include/zenixel -L/usr/local/lib -lSDL2 -lSDL2_ttf -lzenixel -std=c++11

## Compiling on OSX
g++ main.cpp -D_THREAD_SAFE -I/usr/local/include/SDL2 -I/usr/local/include/zenixel -L/usr/local/lib -lSDL2 -lSDL2_ttf -lzenixel -std=c++11

## Zenixel
The graphics library Zenixel is available from https://github.com/stuartthompson/zenixel.git
