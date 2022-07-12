#include <iostream>
#include <list>
#include <cassert>

#include "../lib/Core/Mathf.h"

#include "../lib/Core/Color3D.h"
#include "../lib/Core/Canvas.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.hpp"
#include "../lib/Core/MatrixOps.hpp"
#include "../lib/Core/MatrixTransform.hpp"

#include "../lib/Core/Environment.h"
#include "../lib/Core/Projectile.h"

#include "../lib/Core/Material3D.h"
#include "../lib/Core/Object3D.h"
#include "../lib/Core/Shape3D.h"
#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Plane3D.hpp"
#include "../lib/Core/Intersection.h"
#include "../lib/Core/Ray3D.h"
#include "../lib/Core/Light3D.h"
#include "../lib/Core/Computation.h"
#include "../lib/Core/RayTracer.h"
#include "../lib/Core/Scene3D.h"
#include "../lib/Core/Camera.h"

#include "examples.h"

void run_projectile_demo(Canvas& canvas)
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

void run_clock_demo(Canvas& canvas)
{
	const double offset_x = canvas.Witdth() / 2;
	const double offset_y = canvas.Height() / 2;
	const double size = 100;
	const double count = 12;

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
			Color3D::Green);

		location = rotate * location;
	}

	canvas.Update();
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

			auto intersects = sphere.Intersect(ray);

			if (!ray_hit(intersects).empty())
			{
				canvas.DrawPoint(x, y, shadow);
			}
		}
	}

	canvas.Update();
}

void run_light_demo(Canvas& canvas)
{
	const double w = canvas.Witdth();
	const double h = canvas.Height();
	const double wall_size = 7.0;
	const double wall_position_z = 10.0;
	const double pixel_size = wall_size / w;
	const double half = wall_size / 2;

	Sphere3D sphere(Matrix4d::Scale(1), Material3D(SolidColor3D(1, 0.2, 1)));
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

			auto intersects = sphere.Intersect(ray);
			auto intersections = ray_hit(intersects);

			if (!intersections.empty())
			{
				auto intersection = intersections.begin();
				auto point = ray.Position(intersection->Value);
				auto normal = intersection->Shape->NormalAt(point);
				auto camera = -ray.Direction;
				auto color = light.Compute(intersection->Shape->Material, *intersection->Shape, point, camera, normal);

				canvas.DrawPoint(x, y, color);
			}
		}
		canvas.Update();

	}
}

void run_scene_demo(Canvas& canvas)
{
	const int w = canvas.Witdth(); //100
	const int h = canvas.Height(); //50

	auto left_wall_location = 
		Matrix4d::Translate(0, 0, 5) * 
		Matrix4d::RotateY(-M_PI/4) * Matrix4d::RotateX(M_PI/2) *
		Matrix4d::Scale(10, 0.01, 10);


	auto right_wall_location =
		Matrix4d::Translate(0, 0, 5) *
		Matrix4d::RotateY(M_PI / 4) * Matrix4d::RotateX(M_PI / 2) *
		Matrix4d::Scale(10, 0.01, 10);

	Material3D floor_material(SolidColor3D(1, 0.9, 0.9), 0.1, 0.9, 0);

	Sphere3D floor(Matrix4d::Scale(10, 0.01, 10), floor_material);
	Sphere3D left_wall(left_wall_location, floor_material);
	Sphere3D right_wall(right_wall_location, floor_material);

	// -----------------------------------------------------------------------------

	Sphere3D middle(Matrix4d::Translate(-0.5, 1, 0.5), Material3D(SolidColor3D(0.1, 1, 0.5), 0.1, 0.7, 0.3));

	Sphere3D right(Matrix4d::Translate(1.5, 0.5, -0.5) * Matrix4d::Scale(0.5), Material3D(SolidColor3D(0.5, 1, 0.1), 0.1, 0.7, 0.3));

	Sphere3D left(Matrix4d::Translate(-1.5, 0.33, -0.75) * Matrix4d::Scale(0.33), Material3D(SolidColor3D(1, 0.8, 0.1), 0.1, 0.7, 0.3));

	// -----------------------------------------------------------------------------

	Light3D main_light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Camera main_camera(w, h, M_PI/3, Point3D(0, 1.5, -5), Point3D(0, 1, 0), Vector3D(0, 1, 0));

	// -----------------------------------------------------------------------------

	Scene3D scene;

	scene.Lights.push_back(&main_light);

	scene.Shapes.push_back(&floor);
	scene.Shapes.push_back(&left_wall);
	scene.Shapes.push_back(&right_wall);

	scene.Shapes.push_back(&middle);
	scene.Shapes.push_back(&right);
	scene.Shapes.push_back(&left);

	main_camera.Render(scene, canvas);
}

void run_scene_plane_demo(Canvas& canvas)
{
	const int w = canvas.Witdth(); //100
	const int h = canvas.Height(); //50

	auto left_wall_location =
		Matrix4d::Translate(0, 0, 5) *
		Matrix4d::RotateY(-M_PI / 4) * Matrix4d::RotateX(M_PI / 2) *
		Matrix4d::Scale(10, 0.01, 10);


	auto right_wall_location =
		Matrix4d::Translate(0, 0, 5) *
		Matrix4d::RotateY(M_PI / 4) * Matrix4d::RotateX(M_PI / 2) *
		Matrix4d::Scale(10, 0.01, 10);

	Material3D floor_material(SolidColor3D(1, 0.9, 0.9), 0.1, 0.9, 0);
	Plane3D floor(Matrix4d::Scale(10, 0.01, 10), floor_material);

	// -----------------------------------------------------------------------------

	Sphere3D middle(Matrix4d::Translate(-0.5, 1, 0.5), Material3D(SolidColor3D(0.1, 1, 0.5), 0.1, 0.7, 0.3));

	Sphere3D right(Matrix4d::Translate(1.5, 0.5, -0.5) * Matrix4d::Scale(0.5), Material3D(SolidColor3D(0.5, 1, 0.1), 0.1, 0.7, 0.3));

	Sphere3D left(Matrix4d::Translate(-1.5, 0.33, -0.75) * Matrix4d::Scale(0.33), Material3D(SolidColor3D(1, 0.8, 0.1), 0.1, 0.7, 0.3));

	// -----------------------------------------------------------------------------

	Light3D main_light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Camera main_camera(w, h, M_PI / 3, Point3D(0, 1.5, -5), Point3D(0, 1, 0), Vector3D(0, 1, 0));

	// -----------------------------------------------------------------------------

	Scene3D scene;

	scene.Lights.push_back(&main_light);

	scene.Shapes.push_back(&floor);

	scene.Shapes.push_back(&middle);
	scene.Shapes.push_back(&right);
	scene.Shapes.push_back(&left);

	main_camera.Render(scene, canvas);
}

void run_scene_patterns_demo(Canvas& canvas)
{
	const int w = canvas.Witdth(); //100
	const int h = canvas.Height(); //50

	// -----------------------------------------------------------------------------
	auto floor_location = 
		Matrix4d::Scale(10, 0.01, 10);

	auto wall_location =
		Matrix4d::RotateX(M_PI / 2) *
		Matrix4d::Translate(0, 4, 0) *
		Matrix4d::Scale(10, 0.01, 10);

	// -----------------------------------------------------------------------------
	CheckersColor3D blackGrayCheckers(Color3D::DarkGray, Color3D::Gray, Matrix4d::Scale(0.1, 0.1, 0.1));
	StripeColor3D blackGrayStripes(Color3D::DarkGray, Color3D::Gray, Matrix4d::Scale(0.09, 0.09, 0.09) * Matrix4d::RotateY(M_PI / 6));

	GradientColor3D redYellowGradient(Color3D::Red, Color3D::Yellow, Matrix4d::Scale(2, 2, 2) ); //* Matrix4d::RotateY(-M_PI / 2) * Matrix4d::RotateY(-M_PI / 2)

	RingColor3D greenRadial(Color3D::LightGreen, Color3D::DarkGreen, Matrix4d::Scale(0.12, 0.12, 0.12) * Matrix4d::RotateX(-M_PI / 3) * Matrix4d::RotateZ(M_PI / 6));

	//auto gradientStripes = StripeColor3D(Color3D::Green, Color3D::White); // BlendedColor3D(StripeColor3D(Color3D::Green, Color3D::White), StripeColor3D(Color3D::Black, Color3D::White));

	Material3D floor_material(blackGrayCheckers, 0.1, 0.9, 0);
	Material3D wall_material(blackGrayStripes, 0.1, 0.9, 0);

	Material3D middle_shape_material(greenRadial, 0.1, 0.7, 0.3);
	Material3D right_shape_material(redYellowGradient, 0.1, 0.7, 0.3);

	// -----------------------------------------------------------------------------

	Plane3D floor(floor_location, floor_material);
	Plane3D wall(wall_location, wall_material);

	// -----------------------------------------------------------------------------

	Sphere3D middle(Matrix4d::Translate(-0.5, 1, 0.5), middle_shape_material);
	Sphere3D right(Matrix4d::Translate(1.5, 0.5, -0.5) * Matrix4d::Scale(0.5), right_shape_material);

	// -----------------------------------------------------------------------------

	Light3D main_light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Camera main_camera(w, h, M_PI / 3, Point3D(0, 1.5, -5), Point3D(0, 1, 0), Vector3D(0, 1, 0));

	// -----------------------------------------------------------------------------

	Scene3D scene;

	scene.Lights.push_back(&main_light);

	scene.Shapes.push_back(&floor);
	scene.Shapes.push_back(&wall);

	scene.Shapes.push_back(&middle);
	scene.Shapes.push_back(&right);

	main_camera.Render(scene, canvas);
}