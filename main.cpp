/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
	float dx, dy = 0;
	float fromx, tox;
	if (from.x > to.x)
	{
		fromx = to.x; // Ensure we're drawing left to right
		tox = from.x;
		dx = from.x - to.x;
	}
	else
	{
		fromx = from.x;
		tox = to.x;
		dx = to.x - from.x;
	}
	int fromy, toy;
	if (from.y > to.y)
	{
		fromy = to.y;
		toy = from.y;
		dy = from.y - to.y;
	}
	else
	{
		fromy = from.y;
		toy = to.y;
		dy = to.y - from.y;
	}

	// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
	float x, y;

	// Horizontal and vertical lines are plotted differently
	if (dx == 0)
	{
		for (y = fromy; y <= toy; y++)
		{
			SDL_RenderDrawPoint(renderer, fromx, y);
		}
	}
	else if (dy == 0)
	{
		for (x = fromx; x <= tox; x++)
		{
			SDL_RenderDrawPoint(renderer, x, fromy);
		}
	}
	else
	{
		// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
		float slope = dx / dy;

		// Plot for integer values of x
		for (x = fromx; x <= tox; x++)
		{
			y = (slope * (x - fromx)) + fromy; // Plot the point using y = mx + c
			SDL_RenderDrawPoint(renderer, x, y);
		}
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

		// Create a texture to draw to
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

			clearScreen(renderer);

			drawLine(renderer, {100, 200}, {200, 200}, {255, 0, 0, 255});   // x-axis
			drawLine(renderer, {100, 100}, {100, 200}, {0, 255, 0, 255});   // y-axis
			drawLine(renderer, {100, 200}, {150, 250}, {0, 0, 255, 255});   // slope = 1
			drawLine(renderer, {100, 200}, {110, 250}, {255, 0, 255, 255}); // slope < 1
			drawLine(renderer, {100, 200}, {190, 250}, {0, 255, 255, 255}); // slope > 1

			// Render
			SDL_RenderPresent(renderer);

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