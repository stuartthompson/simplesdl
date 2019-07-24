#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include "Angle.h"
#include "Renderer.h"
#include "Vector2D.h"

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE = {0, 0, 255, 255};
const SDL_Color COLOR_PURPLE = {255, 0, 255, 255};
const SDL_Color COLOR_YELLOW = {255, 255, 0, 255};
const SDL_Color COLOR_CYAN = {0, 255, 255, 255};
const SDL_Color COLOR_GRAY = {128, 128, 128, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};

// calculates the end-point of a vector expressed as an origin, angle, and magnitude
Vector2D calcEndpoint(Vector2D origin, float angle, float magnitude)
{
	// Given the angle and hypotenuse, calculate the height and width of the triangle
	// sin(angle) = width / hypotenuse (soh)      therefore: width = hypotenuse * sin(angle)
	// cos(angle) = width / hypotenuse (cah)      therefore: height = hypotenuse * cos(angle)

	// Degrees to radians is    rad = deg * (PI/180)
	float angleInRadians = degreesToRadians(angle);

	float width = magnitude * sin(angleInRadians);
	float height = magnitude * cos(angleInRadians);

	return {origin.x + (int)width, origin.y + (int)height};
}

float calcLineLength(Vector2D from, Vector2D to)
{
	// c = sqrt(a^2 + b^2)   (pythagorean theorem)
	float dx = std::abs(from.x - to.x);
	float dy = std::abs(from.y - to.y);
	return sqrt(dx * dx + dy * dy);
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

void drawClock(
	const Renderer& renderer, Vector2D origin, int radius, int hourMarkerLength, int hourHandLength,
	int minuteHandLength, int hours, int minutes, SDL_Color borderColor, SDL_Color markerColor, SDL_Color hourHandColor, SDL_Color minuteHandColor)
{
	renderer.drawCircle(origin, radius, borderColor);
	// Draw hour markers
	for (float hour = 0; hour < 12; hour++)
	{
		float angle = 180 - ((360 / 12) * hour); // Add 360/12 degrees each increment (1 marker per hour)
		Vector2D hourMarkerStart = Vector2D::fromPolar(degreesToRadians(angle), radius - hourMarkerLength) + origin;
		Vector2D hourMarkerEnd = Vector2D::fromPolar(degreesToRadians(angle), hourMarkerLength) + hourMarkerStart;
		renderer.drawPlane2D(Plane2D(hourMarkerStart, hourMarkerEnd), markerColor);
	}
	// Draw hands
	float hourHandAngle = (hours * (360 / 12)) - 90;
	// Adjust hour handle angle for partial hour
	float percentThroughHour = (float)minutes / (float)60;
	hourHandAngle = hourHandAngle + ((360 / 12) * percentThroughHour);
	renderer.drawPlane2D(Plane2D(origin, Vector2D::fromPolar(degreesToRadians(hourHandAngle), hourHandLength) + origin), hourHandColor);
	float minuteHandAngle = (minutes * (360 / 60)) - 90;
	renderer.drawPlane2D(Plane2D(origin, Vector2D::fromPolar(degreesToRadians(minuteHandAngle), minuteHandLength) + origin), minuteHandColor);
}

void renderFrame(const Renderer& renderer, int currentTime)
{
	// Clear screen
	renderer.clearScreen(COLOR_BLACK);

	// Draw clock
	int hours = currentTime / 60;
	int minutes = currentTime - (hours * 60);
	drawClock(renderer, {400, 400}, 75, 8, 40, 55, hours, minutes, COLOR_YELLOW, COLOR_GRAY, COLOR_CYAN, COLOR_RED);

	// Draw a circle
	renderer.drawCircle({300, 100}, 50, {255, 255, 128, 255}, true);

	// Draw a line
	renderer.drawPlane2D(Plane2D({400, 100}, {450, 120}), COLOR_RED); // + x-axis

	// Draw a line at an angle
	Vector2D start = Vector2D(400, 200);
	Vector2D end = Vector2D::fromPolar(0, 50) + start;   
	renderer.drawPlane2D(Plane2D(start, end), COLOR_GREEN);

	// Draw lines in various directions
	Vector2D starburstOrigin = Vector2D({100, 100});
	for (int i = 0; i <= 360; i += 10) {
		renderer.drawPlane2D(Plane2D(starburstOrigin, degreesToRadians((float)i), 100), COLOR_YELLOW);
	}
	
	// Render
	renderer.render();
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

		// Create a texture to draw to slope
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

				// Render current frame
				renderFrame(*renderer, currentTime);

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

			// Quit SDL subsystems
			SDL_Quit();

			return 0;
		}
	}
}