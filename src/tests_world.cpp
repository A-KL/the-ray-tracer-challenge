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

#include "../lib/Sphere3D.h"
#include "../lib/Light3D.h"

#include "../lib/Ray3D.h"
#include "../lib/Intersection.h"
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

void run_world_tests()
{
	test_world_default();

	test_world_intersection();
}