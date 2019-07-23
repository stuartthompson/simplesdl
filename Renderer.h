#pragma once

#include <SDL.h>
#include "Plane2D.h"

class Renderer
{
public: 
    Renderer(SDL_Renderer* renderer);

    /**
     * Clears the screen to the specified color.
     * 
     * @param color The color to clean the screen to.
     */
    void clearScreen(SDL_Color color) const;

    /**
     * Draws a 2D plane to the render buffer.
     * 
     * @param plane The plane to render.
     * @param color The color to use to render the plane.
     */
    void drawPlane2D(const Plane2D& plane, SDL_Color color) const;
    
    /**
     * Renders contents of render buffer to the screen.
     */
    void render() const;

private:
    SDL_Renderer* renderer_;
};
