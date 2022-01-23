#define SDL_MAIN_HANDLED

// #define NDEBUG

#include <iostream>
#include <list>
#include <cassert>

#include <SDL.h>

#include "../lib/graphics/Color.h"
#include "../lib/graphics/SDLRenderer.h"

#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"
#include "../lib/ray-tracer-core/Projectile.h"

#include "tests.h"

using namespace std;

int main()
{
#ifdef _DEBUG
	run_tests();
#endif

	Point3D start(0, 1, 0);
	Vector3D velocity(1, 1.8, 0);

	cout << start << endl;
	cout << velocity << endl;

	Projectile proj(start, velocity.Normalize() * 11.25);
	Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

	Color<Rgba> c = Rgba::Blue;

	// init SDL
	SDL_Init(SDL_INIT_VIDEO);

	const int h = 550;
	const int w = 900;

	SDL_Window* window = SDL_CreateWindow(
		"The Ray Tracer Challenge",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w, h, 0);

	SDLRenderer renderer(window);
	SDL_Event event;

	renderer.Clear();

	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);

		Point3D p = proj.Position();

		renderer.DrawPoint(p.X(), h - p.Y(), c.Raw);

		// render window
		renderer.Update();

		proj = proj.Tick(env);

	} while (event.type != SDL_QUIT);

	// cleanup SDL

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}