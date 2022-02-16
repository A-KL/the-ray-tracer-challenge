
#include <M5GFX.h>
#include <list>

#include "Mathf.h"

#include "Color3D.h"
#include "Canvas.h"

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
#include "Material.h"
#include "Light3D.h"
#include "RayTracer.h"

#include "M5StackCanvas.h"

M5GFX display;
M5StackCanvas canvas(display);
//#include <M5UnitOLED.h>
//M5UnitOLED display; // default setting
//M5UnitOLED display ( 21, 22, 400000 ); // SDA, SCL, FREQ

//#include <M5UnitLCD.h>
//M5UnitLCD display;  // default setting
//M5UnitLCD display  ( 21, 22, 400000 ); // SDA, SCL, FREQ

void run_shadow_demo(Canvas& canvas)
{
	const int w = canvas.Height();
	const int h = canvas.Height();
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
		canvas.Update();
	}
}

void run_gravity_demo(Canvas& canvas)
{
	const double w = canvas.Witdth();
	const double h = canvas.Height();

	Point3D start(0, 1, 0);
	Vector3D velocity(1, 1.8, 0);

	Projectile proj(start, velocity.Normalize() * 11.25);
	Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

	canvas.Clear();

	while (true)
	{
		auto p = proj.Position();

		canvas.DrawPoint(p.X(), h - p.Y(), Color3D::Blue);
		canvas.Update();

		proj = proj.Tick(env);

		if (p.Y() < 0)
		{
			break;
		}
	} 
}

void run_light_demo(Canvas& canvas)
{
	const double w = canvas.Witdth();
	const double h = canvas.Height();
	const double wall_size = 7.0;
	const double wall_position_z = 10.0;
	const double pixel_size = wall_size / w;
	const double half = wall_size / 2;

	Sphere3D sphere(Point3D(0, 0, 0), Matrix4d::Scale(1, 1, 1), Material(1, 0.2, 1), 1);
	Light3D light(Point3D(-10, 10, -10), Color3D::White);

	Point3D ray_origin(0, 0, -5);

	canvas.Clear();

	for (int y = 0; y < h; y++)
	{
		double world_y = half - pixel_size * y;

		for (int x = 0; x < w; x++)
		{
			double world_x = -half + pixel_size * x;

			Point3D point_to_render(world_x, world_y, wall_position_z);
			Ray3D ray(ray_origin, (point_to_render - ray_origin).Normalize());

			auto intersects = ray_intersect(sphere, ray);
			auto intersection = ray_hit(intersects);

			if (intersection != Intersection::Empty)
			{
				auto point = ray.Position(intersection.T());
				auto normal = intersection.Object()->NormalAt(point);
				auto camera = -ray.Direction();
				auto color = light.Compute(intersection.Object()->GetMaterial(), point, camera, normal);

				canvas.DrawPoint(x, y, color);
			}
		}
		canvas.Update();

	}
}

void setup(void)
{ 
    canvas.Init();
	display.waitDisplay();
	//run_gravity_demo(canvas);
	//run_shadow_demo(canvas);

	run_light_demo(canvas);
}

void loop(void)
{ 
  delay(10);
}
