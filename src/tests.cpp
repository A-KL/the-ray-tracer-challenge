#include <iostream>
#include <list>
#include <cassert>

#include "../lib/graphics/Color.h"

#include "../lib/ray-tracer-core/Mathf.h"
#include "../lib/ray-tracer-core/Color3D.h"
#include "../lib/ray-tracer-core/Primitive3D.h"
#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "../lib/ray-tracer-core/Ray3D.h"
#include "../lib/ray-tracer-core/Material.h"
#include "../lib/ray-tracer-core/Sphere3D.h"
#include "../lib/ray-tracer-core/Intersection.h"
#include "../lib/ray-tracer-core/Light3D.h"
#include "../lib/ray-tracer-core/RayTracer.h"

#include "tests.h"

void test_vector_dot()
{
	// Set up
	Vector3D vector1(1, 2, 3);
	Vector3D vector2(2, 3, 4);

	// Act
	auto result = vector1.Dot(vector2);

	// Assert
	assert(20 == result);
}

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

void test_vector_reflect()
{
	// Set up
	Vector3D v1(0, -1, 0);
	Vector3D normal(sqrt(2) / 2, sqrt(2) / 2, 0);

	// Act
	auto result = Vector3D::Reflect(v1, normal);

	// Assert
	assert(Vector3D(1, 0, 0) == result);
}

void run_tests()
{
	run_matrix_tests();

	run_ray_tests();

	run_color_tests();

	run_light_tests();

	test_vector_dot();

	test_normal_at_origin();

	test_normal_at_translate();

	test_normal_at_scale();

	test_normal_at_rotate();

	test_normal_at_scale_rotate();

	test_vector_reflect();
}