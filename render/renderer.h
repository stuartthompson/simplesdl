#pragma once

#include <SDL.h>
#include "circle.h"
#include "line2d.h"
#include "point2d.h"

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
     * Draws a 2D point to the render buffer.
     * 
     * @param point The point to draw.
     */
    void drawPoint2D(const Point2D& point) const;

    /**
     * Draws a 2D line to the render buffer.
     * 
     * @param line The line to render.
     */
    void drawLine2D(const Line2D& line) const;
    
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
    SDL_Renderer* renderer_;
};
