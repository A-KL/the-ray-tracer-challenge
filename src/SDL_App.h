#define SDL_MAIN_HANDLED

#include <chrono>
#include <SDL2/SDL.h>

#include "SDLCanvas.h"

void Run(Canvas& canvas);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;

    auto renderer = SDL_CreateWindow(
		"The Ray Tracer Challenge",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		665, 
        500, 0);

    auto canvas = SDLCanvas(renderer, 32);

	auto start_time = std::chrono::high_resolution_clock::now();

    Run(canvas);

    auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

    std::cout << time / std::chrono::milliseconds(1) << "ms to run.\n";

	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);
	} 
	while (event.type != SDL_QUIT);

	SDL_Quit();

	return 0;
}