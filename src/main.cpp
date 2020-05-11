#define SDL_MAIN_HANDLED

// #define NDEBUG

#include <iostream>
#include <list>
#include <cassert>

#include <SDL.h>

#include "renderer/Color.h"
#include "renderer/SDLRenderer.h"

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"
#include "ray-tracer/Matrix.h"

using namespace std;


void run_tests()
{
	// Set up

	Matrix<int, 3, 3> m0 = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> m1 = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> identity = Matrix<int, 3, 3>::Identity;


	Matrix<int, 3, 3> mux;
	matrix_mul(m0, m1, mux);

	Matrix<int, 3, 3> mux2;
	matrix_mul(mux, identity, mux2);

	Matrix<int, 2, 2> sub;
	matrix_sub(m0, sub);

	// Assert

	assert(m0 == m1);

	assert(mux == mux);

	assert(1 == sub.Data[0][0]);
	assert(2 == sub.Data[0][1]);
	assert(4 == sub.Data[1][0]);
	assert(5 == sub.Data[1][1]);


	int tuple[3] = { 2, 2, 2 };

	int tuple_mul[3];

	matrix_mul(m0, tuple, tuple_mul);

	int i0 = tuple_mul[0];
	int i1 = tuple_mul[1];
	int i2 = tuple_mul[2];

	// int d0 = sub.Determinant();
	// int d = sub.Minor(2,2);
}

int main()
{
	run_tests();

	Point3D start(0, 1, 0);
	Vector3D velocity(1, 1.8, 0);

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