#include <iostream>
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
#include "../lib/Light3D.h"

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