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
		SDL_Texture *buffer = SDL_CreateTexture(renderer,
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
			// Draw 255 "frames"
			for (int col = 0; col < 255; col++)
			{

				clearScreen(renderer);

				drawLineWithPixels(renderer, 100, 500, col);

				// Render
				SDL_RenderPresent(renderer);

				// Wait a few milliseconds
				SDL_Delay(5);
			}

			// Wait a second
			SDL_Delay(1000);
		}
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}