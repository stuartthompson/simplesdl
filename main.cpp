/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <cstdlib>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double PI = 3.14159265358979323846;

void clearScreen(SDL_Renderer *renderer)
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void drawLine(SDL_Renderer *renderer, SDL_Point from, SDL_Point to, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

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
				SDL_RenderDrawPoint(renderer, from.x, y);
			}
		}
		else
		// Line is drawn bottom to top so have to decrement from to (origin is top-left in SDL)
		{
			for (y = from.y; y >= to.y; y--)
			{
				SDL_RenderDrawPoint(renderer, from.x, y);
			}
		}
	}
	else if (dy == 0) // Horizontal line
	{
		if (from.x <= to.x) // Line is drawn left to right so have to increment from to (origin is top-left in SDL)
		{
			for (x = from.x; x <= to.x; x++)
			{
				SDL_RenderDrawPoint(renderer, x, from.y);
			}
		}
		else // Line is drawn right to left so have to decrement from to (origin is top-left in SDL)
		{
			for (x = from.x; x >= to.x; x--)
			{
				SDL_RenderDrawPoint(renderer, x, from.y);
			}
		}
	}
	// Sloped line
	else
	{
		// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
		float slope = dy / dx;

		// Plot for integer values of x
		// Find quadrant
		if (from.x <= to.x) // Line is moving to the right
		{
			for (x = from.x; x <= to.x; x++)
			{
				y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		else // Line is moving to the left
		{
			for (x = from.x; x >= to.x; x--)
			{
				y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		
	}
}

// Draws a line from a given point using an angle and a line length
void drawLineAtAngle(SDL_Renderer *renderer, SDL_Point from, float angle, float length, SDL_Color color) {
	// Given the angle and hypotenuse, calculate the height and width of the triangle
	// sin (angle) = width / hypotenuse (soh)
	// width = hypotenuse * sin(angle)

	// Convert angle to radians
	float angleInRadians = angle * (PI / 180);

	float width = length * sin(angleInRadians);
	float height = length * cos(angleInRadians);

	// The "to" point is just the from point with height and width added
	SDL_Point to = {from.x + (int)width, from.y + (int)height};
	drawLine(renderer, from, to, color);
}

float calcLineLength(SDL_Point from, SDL_Point to) {
	// c = sqrt(a^2 + b^2)
	float dx = std::abs(from.x - to.x);
	float dy = std::abs(from.y - to.y);
	return sqrt(dx*dx + dy*dy);
}

void drawPlane(SDL_Renderer *renderer, SDL_Point from, SDL_Point to, SDL_Color color, bool showNormal)
{
	//drawLine(renderer, from, to, color);
	if (showNormal)
	{
		// Find line mid-point
		// Find line at 90 degree angle
		// Draw line
	}
}

void drawLineWithPixels(SDL_Renderer *renderer, int xFrom, int xTo, int colorRed)
{
	// Set render color
	SDL_SetRenderDrawColor(renderer, colorRed, 0, 0, 255);

	// Draw a line using points
	for (int x = xFrom; x < xTo; x++)
	{
		SDL_RenderDrawPoint(renderer, x, 200);
	}
}

void pixelLineRenderLoop(SDL_Renderer *renderer)
{
	// Draw 255 "frames"
	for (int col = 0; col < 255; col++)
	{
		clearScreen(renderer);

		// Draw a line with pixels
		drawLineWithPixels(renderer, 100, 500, col);

		// Render
		SDL_RenderPresent(renderer);

		// Wait a few milliseconds
		SDL_Delay(5);
	}
}

void renderUsingTexture(SDL_Renderer *renderer, SDL_Texture *texture)
{
	Uint32 *pixel;
	Uint32 *pixels = nullptr;
	int pitch = 0;

	int red = 0;
	int blue = 0;
	int green = 0;

	// Draw 255 "frames"
	for (int col = 0; col < 255; col++)
	{
		clearScreen(renderer);

		SDL_LockTexture(texture,
						NULL, // NULL means the *whole texture* here.
						(void **)&pixels,
						&pitch);

		for (int row = 0; row < SCREEN_HEIGHT; ++row)
		{
			SDL_PixelFormat pixelFormat;
			pixelFormat.format = SDL_PIXELFORMAT_BGR888;

			red = col;

			Uint32 color = SDL_MapRGB(&pixelFormat, red, green, blue);
			Uint32 pixelPosition = row * (pitch / sizeof(unsigned int)) + col;
			pixels[pixelPosition] = color;
		}
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_UnlockTexture(texture);

		// Render
		SDL_RenderPresent(renderer);

		SDL_Delay(5);
	}
}

// Tests the drawline function by plotting some axis and different slope lines in all quadrants
void testDrawLine(SDL_Renderer *renderer)
{
	clearScreen(renderer);

	drawLine(renderer, {100, 100}, {200, 100}, {255, 0, 0, 255}); // + x-axis
	drawLine(renderer, {100, 100}, {100, 0}, {0, 255, 0, 255});   // + y-axis
	drawLine(renderer, {100, 100}, {0, 100}, {255, 0, 0, 255});   // - x-axis
	drawLine(renderer, {100, 100}, {100, 200}, {0, 255, 0, 255}); // - y-axis

	drawLine(renderer, {100, 100}, {200, 0}, {0, 0, 255, 255}); // - up and right (at 1:30 on a clock face)
	drawLine(renderer, {100, 100}, {200, 200}, {0, 0, 255, 255}); // - down and right (at 4:30 on a clock face)
	drawLine(renderer, {100, 100}, {0, 200}, {0, 0, 255, 255}); // - down and left (at 7:30 on a clock face)
	drawLine(renderer, {100, 100}, {0, 0}, {0, 0, 255, 255}); // - up and left (at 10:30 on a clock face)

	drawLine(renderer, {100, 100}, {150, 0}, {255, 0, 255, 255}); // - up and right (at 1:00 on a clock face)
	drawLine(renderer, {100, 100}, {200, 50}, {255, 0, 255, 255}); // - up and right (at 3:00 on a clock face)
	drawLine(renderer, {100, 100}, {200, 150}, {255, 0, 255, 255}); // - down and right (at 4:00 on a clock face)
	drawLine(renderer, {100, 100}, {150, 200}, {255, 0, 255, 255}); // - down and right (at 5:00 on a clock face)
	drawLine(renderer, {100, 100}, {50, 200}, {255, 0, 255, 255}); // - down and left (at 7:00 on a clock face)
	drawLine(renderer, {100, 100}, {0, 150}, {255, 0, 255, 255}); // - down and left (at 8:00 on a clock face)
	drawLine(renderer, {100, 100}, {0, 50}, {255, 0, 255, 255}); // - up and left (at 10:00 on a clock face)
	drawLine(renderer, {100, 100}, {50, 0}, {255, 0, 255, 255}); // - up and left (at 11:00 on a clock face)
	
	drawLine(renderer, {100, 100}, {125, 0}, {255, 255, 196, 255}); // something like 12:30
	drawLine(renderer, {100, 100}, {200, 75}, {255, 255, 196, 255}); // something like 2:30
	drawLine(renderer, {100, 100}, {200, 125}, {255, 255, 196, 255}); // something like 3:30
	drawLine(renderer, {100, 100}, {125, 200}, {255, 255, 196, 255}); // something like 5:30
	drawLine(renderer, {100, 100}, {75, 200}, {255, 255, 196, 255}); // something like 6:30
	drawLine(renderer, {100, 100}, {0, 125}, {255, 255, 196, 255}); // something like 8:30
	drawLine(renderer, {100, 100}, {0, 75}, {255, 255, 196, 255}); // something like 9:30
	drawLine(renderer, {100, 100}, {75, 0}, {255, 255, 196, 255}); // something like 11:30

	drawLineAtAngle(renderer, {300, 300}, 135, 75, {255, 255, 255, 255});

	// Render
	SDL_RenderPresent(renderer);
}

void testDrawPlane(SDL_Renderer *renderer)
{
	clearScreen(renderer);

	// Render
	SDL_RenderPresent(renderer);
}

int main(int argc, char *args[])
{
	// Window and renderer
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *texture = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window and get renderer
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

		// Create a texture to draw to slope
		texture =
			SDL_CreateTexture(
				renderer,
				SDL_PIXELFORMAT_BGRA8888,
				SDL_TEXTUREACCESS_STREAMING,
				SCREEN_WIDTH,
				SCREEN_HEIGHT);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Render some frames drawing lines
			//pixelLineRenderLoop(renderer);

			// Render some frames using a texture
			//renderUsingTexture(renderer, texture);

			// Test drawLine
			testDrawLine(renderer);

			//testDrawPlane(renderer);

			// Wait a second
			SDL_Delay(5000);
		}
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}