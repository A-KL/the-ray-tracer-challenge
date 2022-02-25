#define SDL_MAIN_HANDLED

#include <SDL.h>

#include "SDLCanvas.h"
#include "SDLWindowRenderer.h"

#include "tests.h"
#include "examples.h"

int main()
{
#ifdef _DEBUG
	run_tests();
#endif
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;

	SDLWindowRenderer canvas("The Ray Tracer Challenge", 550, 550, 32);

	//run_projectile_demo(canvas);

	//run_clock_demo(canvas);

	//run_shadow_demo(canvas);

	//run_light_demo(canvas);
	
	run_scene_demo(canvas);

	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);
	} 
	while (event.type != SDL_QUIT);

	SDL_Quit();

	return 0;
}