#include <iostream>
#include <list>
#include <cassert>

#include "../lib/ray-tracer-core/Mathf.h"

#include "../lib/ray-tracer-core/Color3D.h"

#include "../lib/ray-tracer-core/Primitive3D.h"
#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "../lib/ray-tracer-core/Material.h"
#include "../lib/ray-tracer-core/Light3D.h"

#include "tests.h"

void test_light_behind_camera()
{
	// Set up
	Material material(Color3D(1, 1, 1));
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, -10), Color3D(1, 1, 1));

	// Act
	auto result = light.Compute(material, Point3D(0, 0, 0), camera, normal);

	// Assert
	assert(Color3D(1.9, 1.9, 1.9) == result);
}

void test_light_45_camera()
{
	// Set up
	Material material(Color3D(1, 1, 1));
	Vector3D camera(0, sqrt(2) * 0.5, - sqrt(2) * 0.5);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, -10), Color3D(1, 1, 1));

	// Act
	auto result = light.Compute(material, Point3D(0, 0, 0), camera, normal);

	// Assert
	assert(Color3D(1.0, 1.0, 1.0) == result);
}

void test_light_45_camera_reverse()
{
	// Set up
	Material material(Color3D(1, 1, 1));
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 10, -10), Color3D(1, 1, 1));

	// Act
	auto result = light.Compute(material, Point3D(0, 0, 0), camera, normal);

	// Assert
	assert(Color3D(0.7364, 0.7364, 0.7364) == result);
}

void test_light_camera_reflection()
{
	// Set up
	Material material(Color3D(1, 1, 1));
	Vector3D camera(0, - sqrt(2) * 0.5, -sqrt(2) * 0.5);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 10, -10), Color3D(1, 1, 1));

	// Act
	auto result = light.Compute(material, Point3D(0, 0, 0), camera, normal);

	// Assert
	assert(Color3D(1.6364, 1.6364, 1.6364) == result);
}

void test_light_behind()
{
	// Set up
	Material material(Color3D(1, 1, 1));
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, 10), Color3D(1, 1, 1));

	// Act
	auto result = light.Compute(material, Point3D(0, 0, 0), camera, normal);

	// Assert
	assert(Color3D(0.1, 0.1, 0.1) == result);
}

void run_light_tests()
{
	test_light_behind_camera();

	test_light_45_camera();

	test_light_45_camera_reverse();

	test_light_camera_reflection();

	test_light_behind();
}