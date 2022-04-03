#include <list>
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

#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Light3D.h"

#include "../lib/Core/Ray3D.h"
#include "../lib/Core/Intersection.h"
#include "../lib/Core/Computation.h"
#include "../lib/Core/RayTracer.h"

#include "../lib/Core/Scene3D.h"

#include "tests.h"

void test_no_shadow()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Point3D point(0, 10, 0);

	// Act
	auto result = light.InShadow(point, scene.Shapes);

	// Assert
	assert(false == result);
}

void test_shadow()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Point3D point(10, -10, 10);

	// Act
	auto result = light.InShadow(point, scene.Shapes);

	// Assert
	assert(true == result);
}

void test_no_shadow2()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(light);
	scene.Shapes.push_back(sphere1);
	scene.Shapes.push_back(sphere2);

	Point3D point(-20, 20, -20);

	// Act
	auto result = light.InShadow(point, scene.Shapes);

	// Assert
	assert(false == result);
}

void run_shadow_tests()
{
	test_no_shadow();

	test_shadow();

	test_no_shadow2();
}