#include <iostream>
#include "../math/math.h"
#include "Renderer.h"

Renderer::Renderer(SDL_Renderer *renderer)
{
	this->renderer_ = renderer;
}

void Renderer::clearScreen(const Color& color) const
{
	this->setDrawColor(color); // Set screen clear color
	SDL_RenderClear(this->renderer_); // Clear screen
}

void Renderer::setDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
}

void Renderer::drawPoint2D(const Point2D& point) const 
{
	this->setDrawColor(point.color);
	SDL_RenderDrawPoint(this->renderer_, point.location.x, point.location.y);
}

void Renderer::drawLine2D(const Line2D &line) const
{
	this->setDrawColor(line.color);

	Vector2D from = line.plane.start();
	Vector2D to = line.plane.end();

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
		if (slope > 1)
		{
			xInc = 1 / slope;
		}
		if (slope < -1)
		{
			xInc = -1 / slope;
		}

		// Plot for integer values of x
		// Find quadrant
		if (slope <= 1 && slope >= -1)
		{
			// Line is more horizontal than vertical so plot using x increments
			if (from.x <= to.x) 
			{
				// Line is moving to the right
				for (x = from.x; x <= to.x; x++)
				{
					y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
					SDL_RenderDrawPoint(this->renderer_, x, y);
				}
			}
			else 
			{	
				// Line is moving to the left
				for (x = from.x; x >= to.x; x--)
				{
					y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
					SDL_RenderDrawPoint(this->renderer_, x, y);
				}
			}
		} 
		else 
		{
			// Line is more vertical than horizontal so plot using y increments
			if (from.y <= to.y) 
			{
				// Line is moving down
				for (y = from.y; y <= to.y; y++)
				{
					// x = (y-c) / m
					x = ((y - from.y)/ slope)  + from.x;
					SDL_RenderDrawPoint(this->renderer_, x, y);
				}
			}
			else 
			{
				// Line is moving up
				for (y = from.y; y >= to.y; y--)
				{
					// x = (y-c) / m
					x = ((y - from.y)/ slope) + from.x;
					SDL_RenderDrawPoint(this->renderer_, x, y);
				}
			}
		}
	}
}

void Renderer::drawCircle(const Circle& circle) const
{
	this->setDrawColor(circle.color);

	// Loop through 360 degrees
	for (int deg = 0; deg < 360; deg++)
	{
		// Vector describing the radius to draw
		Vector2D r = Vector2D::fromPolar(degreesToRadians(deg), circle.radius); // Next radius to draw
		Vector2D endPoint = circle.center + r; // Endpoint is center point + vector described by the current radius being drawn
		if (circle.fill)
		{
			SDL_RenderDrawLine(this->renderer_, circle.center.x, circle.center.y, endPoint.x, endPoint.y);
		}
		else 
		{
			SDL_RenderDrawPoint(this->renderer_, endPoint.x, endPoint.y);
		}
	}
}

void Renderer::render() const
{
	SDL_RenderPresent(this->renderer_);
}
