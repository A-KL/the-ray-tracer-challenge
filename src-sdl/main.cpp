#define SDL_MAIN_HANDLED

#include <chrono>
#include <SDL.h>

#include "SDLCanvas.h"
#include "SDLWindowRenderer.h"

#include "../test/tests.h"
#include "examples.h"

int main()
{
#ifdef _DEBUG
	run_tests();
#endif
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;

	SDLWindowRenderer canvas("The Ray Tracer Challenge", 665, 500, 32); //320*240

	auto start_time = std::chrono::high_resolution_clock::now();

	//run_projectile_demo(canvas);

	//run_clock_demo(canvas);

	//run_shadow_demo(canvas);

	//run_light_demo(canvas);
	
	//run_scene_demo(canvas);

	//run_scene_plane_demo(canvas);

	run_scene_patterns_demo(canvas);

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