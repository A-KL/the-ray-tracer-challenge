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
#include "../lib/Core/Plane3D.hpp"
#include "../lib/Core/Light3D.h"

#include "../lib/Core/Intersection.h"
#include "../lib/Core/Ray3D.h"
#include "../lib/Core/RayTracer.h"
#include "../lib/Core/Computation.h"

#include "../lib/Core/Scene3D.h"

#include "tests.h"

void test_precomoute_reflection_vector()
{
	// Set up
	Plane3D sphere;
	Ray3D ray(Point3D(0, 1, -1), Vector3D(0, -sqrt(2)/2.0, sqrt(2)/2.0));
	Intersection interception(sqrt(2), sphere);

	// Act
	auto result = Computation::Prepare(interception, ray);

	// Assert
	assert(Vector3D(0.0, sqrt(2) / 2.0, sqrt(2) / 2.0) == result.Reflection);
}

void test_nonreflective_material()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Material3D mat(SolidColor3D(1, 1, 1), 1); // ambient -> 1

	Sphere3D sphere1(Material3D(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5), mat);

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	Ray3D ray(Point3D::Origin, Vector3D(0, 0, 1));
	Intersection interception(1, sphere2);

	// Act
	auto comp = Computation::Prepare(interception, ray);
	auto result = scene.ReflectedAt(comp);

	// Assert
	assert(Color3D::Black == result);
}

void test_reflective_material()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));
	Plane3D sphere3(Matrix4d::Translate(0, -1, 0), Material3D(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);
	scene.Shapes.push_back(&sphere3);

	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
	Intersection interception(sqrt(2), sphere3);

	// Act
	auto comp = Computation::Prepare(interception, ray);
	auto result = scene.ReflectedAt(comp);

	// Assert
	assert(Color3D(0.19033, 0.2379, 0.14274) == result);
}

void test_reflective_material_shade_hit()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material3D(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));
	Plane3D sphere3(Matrix4d::Translate(0, -1, 0), Material3D(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);
	scene.Shapes.push_back(&sphere3);

	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, -sqrt(2)/2.0, sqrt(2) / 2.0));
	Intersection interception(sqrt(2), sphere3);

	// Act
	auto comp = Computation::Prepare(interception, ray);
	auto result = scene.ShadeHit(comp);

	// Assert
	assert(Color3D(0.87677, 0.92436, 0.82918) == result);
}


void run_reflection_tests()
{
	test_precomoute_reflection_vector();

	test_nonreflective_material();

	test_reflective_material();

	test_reflective_material_shade_hit();
}