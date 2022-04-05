#include <list>
#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/Canvas.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.hpp"
#include "../lib/Core/MatrixOps.hpp"
#include "../lib/Core/MatrixTransform.hpp"

#include "../lib/Core/Sphere3D.h"

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"

void test_camera_scene_move()
{
	// Setup
	Point3D from(0, 0, 8);
	Point3D to(0, 0, 0);
	Vector3D up(0, 1, 0);

	// Act
	auto t = Camera::ViewTransform(from, to, up);

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
	auto t = Camera::ViewTransform(from, to, up);

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
	auto t = Camera::ViewTransform(from, to, up);

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

void test_camera_render()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	Camera camera(11, 11, M_PI / 2, Point3D(0, 0, -5), Point3D(0, 0, 0), Vector3D(0, 1, 0));
	InMemoryCanvas<11, 11> canvas;

	// Act
	camera.Render(scene, canvas);

	// Assert
	assert(Color3D(0.38066, 0.47583, 0.2855) == canvas.Get(5, 5));
}

void run_camera_tests()
{
	test_camera_scene_move();

	test_camera_scale();

	test_camera_transform();

	test_camera_pixel_size();

	test_camera_pixel_size2();

	test_camera_cast_ray();

	test_camera_render();
}