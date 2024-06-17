#define SDL_MAIN_HANDLED

#include <chrono>
#include <SDL2/SDL.h>

#include "SDLCanvas.h"

void Run(Canvas& canvas);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;

    auto window = SDL_CreateWindow(
		"The Ray Tracer Challenge",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 
        480, 
		SDL_WINDOW_RESIZABLE ); //| SDL_WINDOW_METAL

	if (window == NULL) {
		fprintf(stderr, "ERROR: can't create window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

    auto canvas = SDLCanvas(window, 32);

	// if (canvas == NULL) {
	// 	fprintf(stderr, "ERROR: can't create renderer: %s\n", SDL_GetError());
	// 	return EXIT_FAILURE;
	// }

	auto start_time = std::chrono::high_resolution_clock::now();

    Run(canvas);

	canvas.Update(true);

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