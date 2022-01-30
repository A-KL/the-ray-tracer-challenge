#define SDL_MAIN_HANDLED

// #define NDEBUG

#include <iostream>
#include <list>
#include <cassert>

#include <SDL.h>

#include "../lib/graphics/Color.h"
#include "../lib/graphics/SDLRenderer.h"

#include "../lib/ray-tracer-core/Mathf.h"

#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"
#include "../lib/ray-tracer-core/Projectile.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "tests.h"

using namespace std;

const int h = 550;
const int w = 900;

void run_projectile_demo(SDLRenderer& renderer)
{
	SDL_Event event;

	Point3D start(0, 1, 0);
	Vector3D velocity(1, 1.8, 0);

	cout << start << endl;
	cout << velocity << endl;

	Projectile proj(start, velocity.Normalize() * 11.25);
	Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

	Color<Rgba> c = Rgba::Blue;

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
}

void run_clock_demo(SDLRenderer& renderer)
{
	SDL_Event event;

	const double offset_x = renderer.Witdth() / 2;
	const double offset_y = renderer.Height() / 2;
	const double size = 100;
	const double count = 12;

	Color<Rgba> c = Rgba::Red;
	Color<Rgba> green = Rgba::Green;

	Point3D origin(0, 0, 0);

	Matrix4d translate = Matrix4d::Translate(0, 1, 0);
	Matrix4d rotate = Matrix4d::RotateZ(M_PI / (count / 2));

	Primitive3D<double> location = translate * origin;

	//renderer.DrawLine(
	//	offset_x + -size,
	//	offset_y + 0, 
	//	offset_x + size,
	//	offset_y + 0, 
	//	green.Raw);

	//renderer.DrawLine(
	//	offset_x + 0, 
	//	offset_y  + -size,
	//	offset_x + 0, 
	//	offset_y + size,
	//	green.Raw);

	for (char i = 0; i < count; i++)
	{
		renderer.DrawPoint(
			offset_x + location.X() * size,
			offset_y + location.Y() * size,
			c.Raw);

		location = rotate * location;
	}

	renderer.Update();

	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);
	} while (event.type != SDL_QUIT);
}

int main()
{
#ifdef _DEBUG
	run_tests();
#endif

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"The Ray Tracer Challenge",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w, h, 0);

	SDLRenderer renderer(window);
	renderer.Clear();

	//run_projectile_demo(renderer);

	run_clock_demo(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}