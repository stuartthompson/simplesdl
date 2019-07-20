/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	//The surface contained by the window
	//SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

		//window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			// screenSurface = SDL_GetWindowSurface( window );

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
			SDL_RenderDrawPoint(renderer, 100, 100);

			//Fill the surface white
			// SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			SDL_RenderPresent(renderer);
			//Update the surface
			//SDL_UpdateWindowSurface( window );

			//Wait two seconds
			SDL_Delay( 5000 );
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}