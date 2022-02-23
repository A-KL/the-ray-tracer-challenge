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

#include "../lib/Camera.h"

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

void test_camera_pixel_size()
{
	// Setup
	Camera camera(200, 125, M_PI / 2, Matrix4d::Identity());

	// Assert
	assert(Mathf<double>::Approximately(0.01, camera.PixelSize()));
}

void test_camera_pixel_size2()
{
	// Setup
	Camera camera(125, 200, M_PI / 2, Matrix4d::Identity());

	// Assert
	assert(Mathf<double>::Approximately(0.01, camera.PixelSize()));
}
void test_camera_cast_ray()
{
	// Setup
	Matrix4d transform = Matrix4d::RotateY(M_PI / 4) * Matrix4d::Translate(0, -2, 5);
	Camera camera(201, 101, M_PI / 2, transform);

	// Act
	auto ray = camera.CastRay(100, 50);

	// Assert
	assert(Point3D(0, 2, -5) == ray.Location);
	assert(Vector3D(sqrt(2)/2, 0, -sqrt(2) / 2) == ray.Direction);
}

void run_camera_tests()
{
	test_camera_scene_move();

	test_camera_scale();

	test_camera_transform();

	test_camera_pixel_size();

	test_camera_pixel_size2();

	test_camera_cast_ray();
}