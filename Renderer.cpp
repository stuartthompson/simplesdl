#include "Renderer.h"
#include <iostream>

Renderer::Renderer(SDL_Renderer* renderer)
{
	this->renderer_ = renderer;
}

void Renderer::clearScreen(SDL_Color color) const
{
	// Clear screen
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
	SDL_RenderClear(this->renderer_);
}

void Renderer::drawPlane2D(const Plane2D& plane, SDL_Color color) const
{
    SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);

    Vector2D from = plane.start();
    Vector2D to = plane.end();

	std::cout << "Start: (" << from.x << ", " << from.y << ")  End: (" << to.x << ", " << to.y << ")" << std::endl;

	// Figure out whether x or y is covering more distance (i.e is the slope more horizontal or vertical)
	float dx = from.x - to.x;
	float dy = from.y - to.y;

	// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
	float x, y;

	// Horizontal and vertical lines are plotted differently
	if (dx == 0) // Vertical line
	{
		if (from.y <= to.y) // Line is drawn top to bottom so have to increment from to (origin is top-left in SDL)
		{
			for (y = from.y; y <= to.y; y++)
			{
				SDL_RenderDrawPoint(this->renderer_, from.x, y);
			}
		}
		else
		// Line is drawn bottom to top so have to decrement from to (origin is top-left in SDL)
		{
			for (y = from.y; y >= to.y; y--)
			{
				SDL_RenderDrawPoint(this->renderer_, from.x, y);
			}
		}
	}
	else if (dy == 0) // Horizontal line
	{
		if (from.x <= to.x) // Line is drawn left to right so have to increment from to (origin is top-left in SDL)
		{
			for (x = from.x; x <= to.x; x++)
			{
				SDL_RenderDrawPoint(this->renderer_, x, from.y);
			}
		}
		else // Line is drawn right to left so have to decrement from to (origin is top-left in SDL)
		{
			for (x = from.x; x >= to.x; x--)
			{
				SDL_RenderDrawPoint(this->renderer_, x, from.y);
			}
		}
	}
	// Sloped line
	else
	{
		// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
		float slope = dy / dx;

		// Draw more than one segment per x-pixel if slope is greater than 1 or less than -1 (fills in near-vertical lines)
		float xInc = 1;
		if (slope > 1) {
			xInc = 1 / slope;
		}
		if (slope < -1) {
			xInc = -1 / slope;
		}

		// Plot for integer values of x
		// Find quadrant
		if (from.x <= to.x) // Line is moving to the right
		{
			for (x = from.x; x <= to.x; x+=xInc)
			{
				y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
				SDL_RenderDrawPoint(this->renderer_, x, y);
			}
		}
		else // Line is moving to the left
		{
			for (x = from.x; x >= to.x; x-=xInc)
			{
				y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
				SDL_RenderDrawPoint(this->renderer_, x, y);
			}
		}
	}
}

void Renderer::render() const
{
	SDL_RenderPresent(this->renderer_);
}
