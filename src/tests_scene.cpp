#include <list>
#include <cassert>

#include "../lib/Mathf.h"
#include "../lib/Color3D.h"

#include "../lib/Primitive3D.h"
#include "../lib/Vector3D.h"
#include "../lib/Point3D.h"

#include "../lib/Matrix.hpp"
#include "../lib/MatrixOps.hpp"
#include "../lib/MatrixTransform.hpp"

#include "../lib/Material.h"

#include "../lib/Sphere3D.h"
#include "../lib/Light3D.h"

#include "../lib/Ray3D.h"
#include "../lib/Intersection.h"
#include "../lib/Computation.h"
#include "../lib/RayTracer.h"

#include "../lib/Scene3D.h"

#include "tests.h"

void test_world_default()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	// Act
	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	// Assert
	assert(1 == scene.Lights.size());
	assert(2 == scene.Shapes.size());
}

void test_world_intersection()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	// Act
	auto intersections = ray_intersect(scene.Shapes, ray);

	// Assert
	assert(4 == intersections.size());

	auto iter = intersections.begin();

	assert(4 == (iter++)->Value);
	assert(4.5 == (iter++)->Value);
	assert(5.5 == (iter++)->Value);
	assert(6 == (iter)->Value);
}

void test_world_shade()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Intersection intersection(4, sphere1);

	// Act
	auto computation = Computation::Prepare(intersection, ray);
	auto result = scene.ShadeHit(computation);

	// Assert
	assert(Color3D(0.38066, 0.47583, 0.2855) == result);
}

void test_world_shade_inside()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(0, 0.25, 0), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 0, 1));
	Intersection intersection(0.5, sphere2);

	// Act
	auto computation = Computation::Prepare(intersection, ray);
	auto result = scene.ShadeHit(computation);

	// Assert
	assert(Color3D(0.90498, 0.90498, 0.90498) == result);
}

void test_computation_creation()
{
	// Setup
	Sphere3D sphere;
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Intersection intersection(4, sphere);

	// Act
	auto computation = Computation::Prepare(intersection, ray);

	// Assert
	assert((Shape3D)sphere == *computation.Intersect.Shape);
	assert(Point3D(0, 0, -1) == computation.Position);
	assert(Vector3D(0, 0, -1) == computation.Camera);
	assert(Vector3D(0, 0, -1) == computation.Normal);
}

void test_computation_outside()
{
	// Setup
	Sphere3D sphere;
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Intersection intersection(4, sphere);

	// Act
	auto computation = Computation::Prepare(intersection, ray);

	// Assert
	assert(!computation.IsInside);
}

void test_computation_inside()
{
	// Setup
	Sphere3D sphere;
	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 0, 1));
	Intersection intersection(1, sphere);

	// Act
	auto computation = Computation::Prepare(intersection, ray);

	// Assert
	assert(computation.IsInside);
	assert(Point3D(0, 0, 1) == computation.Position);
	assert(Vector3D(0, 0, -1) == computation.Camera);
	assert(Vector3D(0, 0, -1) == computation.Normal);
}

void test_computation_z()
{
	// Setup
	Sphere3D sphere(Matrix4d::Translate(0, 0, 1));
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Intersection intersection(5, sphere);

	// Act
	auto computation = Computation::Prepare(intersection, ray);

	// Assert
	assert((-DBL_EPSILON / 2) > computation.OverPosition.Z());
	assert(computation.Position.Z() > computation.OverPosition.Z());
}

void test_scene_color_at_miss()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 1, 0));

	// Act
	auto result = scene.ColorAt(ray);

	// Assert
	assert(Color3D(0, 0, 0) == result);
}

void test_scene_color_at_hit()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	// Act
	auto result = scene.ColorAt(ray);

	// Assert
	assert(Color3D(0.38066, 0.47583, 0.2855) == result);
}

void test_scene_color_at_behind()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Point3D(0, 0, 0), Matrix4d::Scale(0.5, 0.5, 0.5), Material(1, 1, 1, 1, 0.7, 0.2));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, 0.75), Vector3D(0, 0, -1));

	// Act
	auto result = scene.ColorAt(ray);

	// Assert
	assert(sphere2.Mat.Color == result);
}

void run_scene_tests()
{
	test_world_default();

	test_world_intersection();

	test_computation_creation();

	test_computation_inside();

	test_computation_outside();

	test_computation_z();

	test_world_shade();

	test_world_shade_inside();

	test_scene_color_at_miss();

	test_scene_color_at_hit();

	test_scene_color_at_behind();
}