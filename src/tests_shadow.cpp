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

void test_no_shadow()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
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

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
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

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
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