#pragma once

#include <SDL.h>

struct Color
{
    unsigned char r, g, b, a;

    SDL_Color toSDLColor() const { return { r, g, b, a }; }
};


const Color COLOR_WHITE = Color({255, 255, 255, 255});
const Color COLOR_BLACK = Color({0, 0, 0, 0});
const Color COLOR_GRAY = {128, 128, 128, 255};
const Color COLOR_RED = Color({255, 0, 0, 255});
const Color COLOR_GREEN = Color({0, 255, 0, 255});
const Color COLOR_BLUE = Color({0, 0, 255, 255});
const Color COLOR_PURPLE = {255, 0, 255, 255};
const Color COLOR_YELLOW = {255, 255, 0, 255};
const Color COLOR_CYAN = {0, 255, 255, 255};