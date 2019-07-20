/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	// Window and renderer
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		// Create window and get renderer
		SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			// Set render color
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
			// Draw a point
			SDL_RenderDrawPoint(renderer, 100, 100);

			// Render
			SDL_RenderPresent(renderer);

			// Wait a few seconds
			SDL_Delay( 5000 );
		}
	}

	// Destroy window
	SDL_DestroyWindow( window );

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}