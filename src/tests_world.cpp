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

#include "../lib/World3D.h"

#include "tests.h"

void test_world_default()
{
	// Setup
	World3D world;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	// Act
	world.Lights.push_back(light);
	world.Shapes.push_back(sphere1);
	world.Shapes.push_back(sphere2);

	// Assert
	assert(1 == world.Lights.size());
	assert(2 == world.Shapes.size());
}

void test_world_intersection()
{
	// Setup
	World3D world;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	world.Lights.push_back(light);
	world.Shapes.push_back(sphere1);
	world.Shapes.push_back(sphere2);

	// Act
	auto intersections = ray_intersect(world.Shapes, ray);

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
	World3D world;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	world.Lights.push_back(light);
	world.Shapes.push_back(sphere1);
	world.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Intersection intersection(4, sphere1);

	// Act
	auto computation = Computation::Prepare(intersection, ray);
	auto result = shade_hit(world.Lights, computation);

	// Assert
	assert(Color3D(0.38066, 0.47583, 0.2855) == result);
}

void test_world_shade_inside()
{
	// Setup
	World3D world;
	Light3D light(Point3D(0, 0.25, 0), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	world.Lights.push_back(light);
	world.Shapes.push_back(sphere1);
	world.Shapes.push_back(sphere2);

	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 0, 1));
	Intersection intersection(0.5, sphere1);

	// Act
	auto computation = Computation::Prepare(intersection, ray);
	auto result = shade_hit(world.Lights, computation);

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



void run_world_tests()
{
	test_world_default();

	test_world_intersection();

	test_computation_creation();

	test_computation_inside();
	
	test_computation_outside();

	test_world_shade_inside();

	test_world_shade();
}