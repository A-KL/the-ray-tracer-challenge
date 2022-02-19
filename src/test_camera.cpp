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

void test_camera_scene_move()
{
	// Setup
	Point3D from(0, 0, 8);
	Point3D to(0, 0, 0);
	Vector3D up(0, 1, 0);

	// Act
	auto t = view_transform(from, to, up);

	// Assert
	assert(t == Matrix4d::Translate(0, 0, -8));
}

void test_camera_scale()
{
	// Setup
	Point3D from(0, 0, 0);
	Point3D to(0, 0, 1);
	Vector3D up(0, 1, 0);

	// Act
	auto t = view_transform(from, to, up);

	// Assert
	assert(t == Matrix4d::Scale(-1, 1, -1));
}

void test_camera_transform()
{
	// Setup
	Point3D from(1, 3, 2);
	Point3D to(4, -2, 8);
	Vector3D up(1, 1, 0);

	auto expected = Matrix4d
	{
		-0.50709, 0.50709, 0.67612, -2.36643,
		0.76772, 0.60609, 0.12122, -2.82843,
		-0.35857, 0.59761, -0.71714, 0,
		0, 0, 0, 1.0
	};

	// Act
	auto t = view_transform(from, to, up);

	// Assert
	assert(expected == t);
}

void run_camera_tests()
{
	test_camera_scene_move();

	test_camera_scale();

	test_camera_transform();
}