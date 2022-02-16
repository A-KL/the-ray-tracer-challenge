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

#include "tests.h"

void test_normal_at_translate()
{
	// Set up
	Sphere3D sphere(Matrix4d::Translate(0, 1, 0));

	// Act
	auto res = sphere.NormalAt(Point3D(0, 1.70711, -0.70711));

	// Assert
	assert(Vector3D(0, 0.70711, -0.70711) == res);
}

void test_normal_at_rotate()
{
	// Set up
	auto transform = Matrix4d::RotateZ(M_PI / 2);
	Sphere3D sphere(transform);

	// Act
	auto res = sphere.NormalAt(Point3D(1, 0, 0));

	// Assert
	assert(Vector3D(1, 0, 0) == res);
}

void test_normal_at_origin()
{
	// Set up
	Sphere3D sphere;

	// Act
	auto normal = sphere.NormalAt(Point3D(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

	// Assert
	assert(normal == normal.Normalize());
}

void test_normal_at_scale()
{
	// Set up
	auto transform = Matrix4d::Scale(1, 0.5, 1);
	Sphere3D sphere(transform);

	// Act
	auto res = sphere.NormalAt(Point3D(0, 0.5, 0));

	// Assert
	assert(Vector3D(0, 1, 0) == res);
}

void test_normal_at_scale_rotate()
{
	// Set up
	auto scale = Matrix4d::Scale(1, 0.5, 1);
	auto rotate = Matrix4d::RotateZ(3.14159265358979 / 5.0);
	auto transform = scale * rotate;

	Sphere3D sphere(transform);

	// Act
	auto res = sphere.NormalAt(Point3D(0, sqrt(2.0) * 0.5, sqrt(2.0) * -0.5));

	// Assert
	assert(Vector3D(0.0, 0.97014, -0.24254) == res);
}

void run_normal_tests()
{
	test_normal_at_origin();

	test_normal_at_translate();

	test_normal_at_scale();

	test_normal_at_rotate();

	test_normal_at_scale_rotate();
}