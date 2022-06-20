#include <iostream>
#include <list>
#include <vector>
#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Color3D.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.hpp"
#include "../lib/Core/MatrixOps.hpp"
#include "../lib/Core/MatrixTransform.hpp"

#include "../lib/Core/Material3D.h"

#include "../lib/Core/Shape3D.h"
#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Light3D.h"

#include "../lib/Core/Intersection.h"
#include "../lib/Core/Ray3D.h"
#include "../lib/Core/RayTracer.h"
#include "../lib/Core/Computation.h"

#include "tests.h"

void test_ray_sphere_scale_intersect()
{
	// Set up
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Sphere3D sphere(Matrix4d::Scale(2, 2, 2));

	// Act
	auto res = sphere.Intersect(ray);

	// Assert
	assert(2 == res.size());

	auto first = res.begin();

	assert(3.0 == (first++)->Value);
	assert(7.0 == (first)->Value);
}

void test_ray_sphere_translate_intersect()
{
	// Set up
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Sphere3D sphere(Matrix4d::Translate(5, 0, 0));

	// Act
	auto res = sphere.Intersect(ray);

	// Assert
	assert(0 == res.size());
}

void test_ray_transform()
{
	// Set up
	Ray3D ray(Point3D(1, 2, 3), Vector3D(0, 1, 0));

	auto transform = Matrix4d::Translate(3, 4, 5);

	// Act
	auto result = ray.Transform(transform);

	// Assert
	assert(Point3D(4, 6, 8) == result.Location);
	assert(Vector3D(0, 1, 0) == result.Direction);

	// Set up
	transform = Matrix4d::Scale(2, 3, 4);

	// Act
	auto result2 = ray.Transform(transform);

	// Assert
	assert(Point3D(2, 6, 12) == result2.Location);
	assert(Vector3D(0, 3, 0) == result2.Direction);
}

void test_ray_positive_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(1, sphere),
		intersection2(2, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto results = ray_hit(intersections);

	// Assert
	assert(intersection1 == *results.begin());
}

void test_ray_some_negative_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(-1, sphere),
		intersection2(1, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto results = ray_hit(intersections);

	// Assert
	assert(intersection2 == *results.begin());
}

void test_ray_some_all_negative_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(-2, sphere),
		intersection2(-1, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto results = ray_hit(intersections);

	// Assert
	assert(results.empty());
}

void test_ray_mixed_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(5, sphere),
		intersection2(7, sphere),
		intersection3(-3, sphere),
		intersection4(2, sphere);

	std::list<Intersection> intersections1 = {
		intersection1,
		intersection2,
		intersection3,
		intersection4
	};

	// Act
	auto results = ray_hit(intersections1);

	// Assert
	assert(intersection4 == *results.begin());
}

void test_ray_intersect()
{
	// Set up
	Ray3D ray(Point3D(0, 1, -5), Vector3D(0, 0, 1));
	Sphere3D sphere;

	// Act
	auto res = sphere.Intersect(ray);

	// Assert
	assert(2 == res.size());

	auto first = res.begin();

	assert(5.0 == first->Value);
	assert(5.0 == (first++)->Value);


	// Set up
	Ray3D ray2(Point3D(0, 0, 0), Vector3D(0, 0, 1));

	// Act
	res = sphere.Intersect(ray2);

	// Assert
	assert(2 == res.size());

	first = res.begin();

	assert(-1.0 == (first++)->Value);
	assert(1.0 == (first)->Value);


	// Set up
	Ray3D ray3(Point3D(0, 2, -5), Vector3D(0, 0, 1));

	// Act
	res = sphere.Intersect(ray3);

	// Assert
	assert(0 == res.size());
}

void test_sphere_default_transform()
{
	// Set up
	Sphere3D sphere;

	// Assert
	assert(Matrix4d::Identity() == sphere.Transformation);
}

void test_sphere_set_transform()
{
	// Set up
	Sphere3D sphere(Matrix4d::Translate(2, 3, 4));

	// Assert
	assert(Matrix4d::Translate(2, 3, 4) == sphere.Transformation);
}

void run_ray_tests()
{
	test_sphere_default_transform();

	test_sphere_set_transform();

	test_ray_intersect();

	test_ray_positive_hits();

	test_ray_some_negative_hits();

	test_ray_some_all_negative_hits();

	test_ray_mixed_hits();

	test_ray_transform();

	test_ray_sphere_scale_intersect();

	test_ray_sphere_translate_intersect();
}