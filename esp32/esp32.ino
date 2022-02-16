
#include <M5GFX.h>
#include <list>

#include "Mathf.h"

#include "Color3D.h"
#include "Canvas.h"
#include "M5StackCanvas.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Environment.h"
#include "Projectile.h"

#include "Ray3D.h"
#include "Sphere3D.h"
#include "Intersection.h"

#include "RayTracer.h"

M5GFX display;
M5StackCanvas canvas(display, 16);
//#include <M5UnitOLED.h>
//M5UnitOLED display; // default setting
//M5UnitOLED display ( 21, 22, 400000 ); // SDA, SCL, FREQ

//#include <M5UnitLCD.h>
//M5UnitLCD display;  // default setting
//M5UnitLCD display  ( 21, 22, 400000 ); // SDA, SCL, FREQ

Point3D start(0, 1, 0);
Vector3D velocity(1, 1.8, 0);

Projectile proj(start, velocity.Normalize() * 6.25);
Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

void setup(void)
{ 
    canvas.Init();
	display.waitDisplay();
}

void run_shadow_demo(Canvas& canvas)
{
	const double w = canvas.Witdth();
	const double h = canvas.Height();
	const double wall_size = 7.0;
	const double wall_position_z = 10.0;
	const double pixel_size = wall_size / w;
	const double half = wall_size / 2;

	Sphere3D sphere;
	Point3D ray_origin(0, 0, -5);

	auto opaque = Color3D::Black;
	auto background = Color3D::Red;
	auto shadow = opaque * background;

	canvas.Clear(background);

	for (int y = 0; y < h; y++)
	{
		double world_y = half - pixel_size * y;

		for (int x = 0; x < w; x++)
		{
			double world_x = -half + pixel_size * x;

			Point3D point_to_render(world_x, world_y, wall_position_z);
			Ray3D ray(ray_origin, (point_to_render - ray_origin).Normalize());

			auto intersects = ray_intersect(sphere, ray);

			if (ray_hit(intersects) != Intersection::Empty)
			{
				canvas.DrawPoint(x, y, shadow);
			}
		}
	}

	canvas.Update();
}

void run_gravity_demo(Canvas& canvas)
{

  Point3D p = proj.Position();

  canvas.DrawPoint(p.X(), canvas.Height() - p.Y(), Color3D::Red);

  proj = proj.Tick(env);

  canvas.Update();
}

void loop(void)
{ 
	//run_shadow_demo(canvas);
	run_gravity_demo(canvas);

  delay(10);
}
