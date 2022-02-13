#define SDL_MAIN_HANDLED

// #define NDEBUG

#include <iostream>
#include <list>
#include <cassert>

#include <SDL.h>

#include "../lib/graphics/Color.h"
#include "../lib/graphics/Canvas.h"
#include "../lib/graphics/SDLCanvas.h"
#include "../lib/graphics/SDLWindowRenderer.h"

#include "../lib/ray-tracer-core/Mathf.h"

#include "../lib/ray-tracer-core/Primitive3D.h"
#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "../lib/ray-tracer-core/Environment.h"
#include "../lib/ray-tracer-core/Projectile.h"

#include "../lib/ray-tracer-core/Ray3D.h"
#include "../lib/ray-tracer-core/Light3D.h"
#include "../lib/ray-tracer-core/Sphere3D.h"
#include "../lib/ray-tracer-core/Intersection.h"

#include "tests.h"

#include "../lib/ray-tracer-core/RayTracer.h"

using namespace std;

const int h = 550;
const int w = 550;

void run_projectile_demo(Canvas& canvas)
{
	SDL_Event event;

	Point3D start(0, 1, 0);
	Vector3D velocity(1, 1.8, 0);

	Projectile proj(start, velocity.Normalize() * 11.25);
	Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

	Color<Rgba> c = Rgba::Blue;

	canvas.Clear();

	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);

		Point3D p = proj.Position();

		canvas.DrawPoint(p.X(), h - p.Y(), c.Raw);
		canvas.Update();

		proj = proj.Tick(env);
	} 
	while (event.type != SDL_QUIT);
}

void run_clock_demo(Canvas& canvas)
{
	const double offset_x = canvas.Witdth() / 2;
	const double offset_y = canvas.Height() / 2;
	const double size = 100;
	const double count = 12;

	Color<Rgba> c = Rgba::Red;
	Color<Rgba> green = Rgba::Green;

	Point3D origin(0, 0, 0);

	Matrix4d translate = Matrix4d::Translate(0, 1, 0);
	Matrix4d rotate = Matrix4d::RotateZ(M_PI / (count / 2));

	Primitive3D<double> location = translate * origin;

	canvas.Clear();

	for (char i = 0; i < count; i++)
	{
		canvas.DrawPoint(
			offset_x + location.X() * size,
			offset_y + location.Y() * size,
			c.Raw);

		location = rotate * location;
	}

	canvas.Update();
}

void run_shadow_demo(Canvas& canvas)
{
	const double wall_size = 7.0;
	const double wall_position_z = 10.0;
	const double pixel_size = wall_size / w;
	const double half = wall_size / 2;

	Sphere3D sphere;
	Point3D ray_origin(0, 0, -5);

	Color<Rgba> opaque = Rgba::Black;
	Color<Rgba> background = Rgba::Red;
	Color<Rgba> shadow = { opaque.Channels * background.Channels };

	canvas.Clear(background.Raw);

	for (int y = 0; y < h; y++)
	{
		double world_y = half - pixel_size * y;

		for (int x = 0; x < w; x++)
		{
			double world_x =  - half + pixel_size * x;

			Point3D point_to_render(world_x, world_y, wall_position_z);
			Ray3D ray(ray_origin, (point_to_render - ray_origin).Normalize());

			auto intersects = ray_intersect(sphere, ray);

			if (ray_hit(intersects) != Intersection::Empty)
			{
				canvas.DrawPoint(x, y, shadow.Raw);
			}
		}
	}

	canvas.Update();
}

int main()
{
#ifdef _DEBUG
	run_tests();
#endif
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;
	SDLWindowRenderer canvas("The Ray Tracer Challenge", w, h, 32);

	//run_projectile_demo(canvas);

	//run_clock_demo(canvas);

	run_shadow_demo(canvas);
	
	do
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);
	} 
	while (event.type != SDL_QUIT);

	SDL_Quit();

	return 0;
}