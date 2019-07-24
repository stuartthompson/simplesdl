#pragma once

#include <SDL.h>
#include "Circle.h"
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
    void clearScreen(const Color& color) const;

    /**
     * Sets the draw color to the specified color.
     * 
     * @param color The color to set.
     */
    void setDrawColor(const Color& color) const;

    /**
     * Draws a 2D plane to the render buffer.
     * 
     * @param plane The plane to render.
     * @param color The color to use to render the plane.
     */
    void drawPlane2D(const Plane2D& plane, Color color) const;
    
    /**
     * Draws a circle to the render buffer.
     * 
     * @param circle The circle to draw.
     */
    void drawCircle(const Circle& circle) const;

    /**
     * Renders contents of render buffer to the screen.
     */
    void render() const;

private:
    SDL_Color toSDLColor(const Color& color) const;
    
    SDL_Renderer* renderer_;
};
