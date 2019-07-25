#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <string>
#include <zen-math.h>
#include <zen-render.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void renderUsingTexture(SDL_Renderer *renderer, SDL_Texture *texture)
{
	// TODO: Archive this technique in case I need it later
	Uint32 *pixel;
	Uint32 *pixels = nullptr;
	int pitch = 0;

	int red = 0;
	int blue = 0;
	int green = 0;

	// Draw 255 "frames"
	for (int col = 0; col < 255; col++)
	{
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
	}
}

void drawScene(const Renderer& renderer, const std::string& sceneName)
{
	Scene scene = Scene();
	scene.load(sceneName);

	scene.render(renderer);
}

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char *args[])
{
	// Window and renderer
	SDL_Window *window = NULL;
	SDL_Renderer *sdlRenderer = NULL;

	SDL_Texture *texture = NULL;
	SDL_Event event;

	Renderer* renderer;

	bool quitting = false;

	int currentTimeVelocity = 0;
	int currentTime = (2*60) + 22;

	uint64_t lastTick = timeSinceEpochMillisec();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window and get renderer
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &sdlRenderer);

		// Initialize SDL TTF (for fonts/text rendering)
		TTF_Init();

		// Create a texture to draw to slope
		// TODO: Archive this
		texture =
			SDL_CreateTexture(
				sdlRenderer,
				SDL_PIXELFORMAT_BGRA8888,
				SDL_TEXTUREACCESS_STREAMING,
				SCREEN_WIDTH,
				SCREEN_HEIGHT);

		// Create renderer
		renderer = new Renderer(sdlRenderer);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			while (!quitting)
			{
				// Game logic
				// Increment current time (only if not incremented in last 100ms)
				uint64_t now = timeSinceEpochMillisec();
				if (now - lastTick > 50) {
					currentTime += currentTimeVelocity;
					lastTick = now;
				}

				// Draw test scene
				drawScene(*renderer, "SinglePoint");

				// Render
				renderer->render();

				// Check for input
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
						case SDLK_q:
							quitting = true;
							break;
						case SDLK_UP:
							currentTimeVelocity = 1;
							break;
						case SDLK_DOWN:
							currentTimeVelocity = -1;
							break;
						default:
							break;
						}
						break;
					case SDL_KEYUP:
						switch (event.key.keysym.sym)
						{
						case SDLK_UP:
							if (currentTimeVelocity > 0)
								currentTimeVelocity = 0;
							break;
						case SDLK_DOWN:
							if (currentTimeVelocity < 0)
								currentTimeVelocity = 0;
							break;
						default:
							break;
						}
					}
				}
			}

			// Delete renderer
			delete renderer;

			// Destroy window
			SDL_DestroyWindow(window);

			// Quit SDL ttf
			TTF_Quit();

			// Quit SDL subsystems
			SDL_Quit();

			return 0;
		}
	}
}