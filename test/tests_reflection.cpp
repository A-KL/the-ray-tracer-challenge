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

void test_precompute_reflection_vector()
{
	// Set up
	Plane3D shape;
	Ray3D ray(Point3D(0, 1, -1), Vector3D(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
	Intersection interception(sqrt(2), shape);

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

	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
	Intersection interception(sqrt(2), sphere3);

	// Act
	auto comp = Computation::Prepare(interception, ray);
	auto result = scene.ShadeHit(comp);

	// Assert
	assert(Color3D(0.87677, 0.92436, 0.82918) == result);
}

void test_reflective_material_recursion()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(0, 0, 0), Color3D(1, 1, 1));

	Plane3D lower(Matrix4d::Translate(0, -1, 0), Material3D(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 1));
	Plane3D upper(Matrix4d::Translate(0, 1, 0), Material3D(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 1));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&lower);
	scene.Shapes.push_back(&upper);

	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 1, 0));

	// Act
	auto color = scene.ColorAt(ray);
}

void test_reflective_material_limit_recursion()
{
	// Setup
	Scene3D scene;
	Light3D light(Point3D(0, 0, 0), Color3D::White);

	Plane3D shape(Matrix4d::Translate(0, -1, 0), Material3D(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&shape);

	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
	Intersection interception(sqrt(2), shape);

	// Act
	auto computation = Computation::Prepare(interception, ray);
	auto result = scene.ReflectedAt(computation, 0);

	// Assert
	assert(Color3D::Black == result);
}

void test_reflective_n1_n2_intersections()
{
	// Setup
	auto default_material = Material3D::Glass;

	double n1_results[] { 1.0, 1.5, 2.0, 2.5, 2.5, 1.5 };
	double n2_results[] { 1.5, 2.0, 2.5, 2.5, 1.5, 1.0 };
	
	Sphere3D glass_sphere_a(
		Matrix4d::Scale(2, 2, 2), 
		default_material.With([](Material3D& m) -> void { m.RefractiveIndex = 1.5; }));

	Sphere3D glass_sphere_b(
		Matrix4d::Translate(0, 0, -0.25), 
		default_material.With([](Material3D& m) -> void { m.RefractiveIndex = 2.0; }));

	Sphere3D glass_sphere_c(
		Matrix4d::Translate(0, 0, 0.25),
		default_material.With([](Material3D& m) -> void { m.RefractiveIndex = 2.5; }));

	std::vector<const Intersection> interceptions {
		{ 2.00, glass_sphere_a },
		{ 2.75, glass_sphere_b },
		{ 3.25, glass_sphere_c },
		{ 4.75, glass_sphere_b },
		{ 5.25, glass_sphere_c },
		{ 6.00, glass_sphere_a },
	 };

	// Act
	Ray3D ray(Point3D(0, 0, -4), Vector3D(0, 0, 1));

	for (auto i = 0; i < interceptions.size(); i++) {
		auto computation = Computation::Prepare(interceptions[i], ray, interceptions);

		// Assert
		assert(computation.N1 == n1_results[i]);
		assert(computation.N2 == n2_results[i]);
	}
}

void test_reflective_under_point_is_offset_below_surface()
{
	// Setup
	Sphere3D shape(Matrix4d::Translate(0, 0, 1), Material3D::Glass);

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	Intersection intersection(5, shape);
	std::vector<const Intersection> intersections { intersection };

	// Act
	auto computation = Computation::Prepare(intersection, ray, intersections);

	// Assert
	assert(computation.UnderPosition.Z() > (Mathf<double>::Epsilon() / 2.0));
	assert(computation.Position.Z() < computation.UnderPosition.Z());
}

void test_refractive_color_with_opaque_surface()
{	
	// Default world
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

    Material3D material1(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2);
	Material3D material2(SolidColor3D(1, 1, 1), 1);

	Sphere3D sphere1(material1);
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5), material2);

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	// Setup
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	auto first_shape = *scene.Shapes.begin();

	std::vector<const Intersection> intersections 
	{ 
		Intersection(4, first_shape),
		Intersection(6, first_shape) 
	};
	
	// Act
	auto computation = Computation::Prepare(intersections[0], ray, intersections);

	auto c = scene.RefractedAt(computation, 5);

	// Assert
	assert(c == Color3D::Black);
}

void test_refractive_color_under_total_internal_reflection()
{	
	// Default world
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

    Material3D material1(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200, 0.0, 1.0, 1.5);
	Material3D material2(SolidColor3D(1, 1, 1), 1);

	Sphere3D sphere1(material1);
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5), material2);

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	// Setup
	Ray3D ray(Point3D(0, 0, sqrt(2.0)/2.0), Vector3D(0, 1, 0));

	std::vector<const Intersection> intersections 
	{ 
		Intersection(-sqrt(2.0)/2.0, sphere1),
		Intersection(sqrt(2.0)/2.0, sphere1) 
	};

	// Act
	//  NOTE: this time you're inside the sphere, so you need
	//  to look at the second intersection, xs[1], not xs[0]
	auto computation = Computation::Prepare(intersections[1], ray, intersections);

	auto c = scene.RefractedAt(computation, 5);

	// Assert
	assert(c == Color3D::Black);
}

void test_refractive_color_with_refracted_ray()
{	
	// Default world
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

    Material3D material1(TestPattern(), 1.0, 0.7, 0.2);
	Material3D material2(SolidColor3D(1, 1, 1), 0.1, 0.9, 0.9, 200, 0.0, 1.0, 1.5);

	Sphere3D sphere1(material1);
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5), material2);

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	// Setup
	Ray3D ray(Point3D(0, 0, 0.1), Vector3D(0, 1, 0));

	std::vector<const Intersection> intersections 
	{ 
		Intersection(-0.9899, sphere1),
		Intersection(-0.4899, sphere2),
		Intersection(0.4899, sphere2),
		Intersection(0.9899, sphere1)
	};

	// Act
	auto computation = Computation::Prepare(intersections[2], ray, intersections);
	auto c = scene.RefractedAt(computation, 5);

	// Assert
	assert(c == Color3D(0, 0.99888, 0.04725));
}

void test_refractive_shade_hit_transparent_material()
{	
	// Default world
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

    Material3D material1(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2);

	Sphere3D sphere1(material1);
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	// Setup
	Material3D floor_material(
		SolidColor3D(),
		0.1, /* ambient */
		0.9, /* diffuse */
		0.2, /* specular */
		200, 
		0.5, /* reflective */
		0.5, /* transparency */
		1.5  /* refractive index */
	);

	Plane3D floor(Matrix4d::Translate(0, -1, 0), floor_material);

	Material3D ball_material(
		SolidColor3D(1, 0, 0), 
		0.5 /* ambient */
	);

	Sphere3D ball(Matrix4d::Translate(0, -3.5, -0.5), ball_material);

	scene.Shapes.push_back(&floor);
	scene.Shapes.push_back(&ball);

	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, (-sqrt(2.0)/2.0), (sqrt(2.0)/2.0)));

	std::vector<const Intersection> intersections 
	{ 
		Intersection(sqrt(2.0), floor)
	};

	// Act
	auto computation = Computation::Prepare(intersections[0], ray, intersections);
	auto c = scene.ShadeHit(computation, 5);

	// Assert
	std::cout << c << std::endl;
	// TODO: FIX IT
	//assert(c == Color3D(0.93642, 0.68642, 0.68642));
}

void test_reflection_schlick_approximation_under_total_internal_reflection()
{
	// Setup
	Sphere3D glass_sphere(Material3D::Glass);
	Ray3D ray(Point3D(0, 0, sqrt(2.0)/2.0), Vector3D(0, 1, 0));
	std::vector<const Intersection> intersections 
	{ 
		Intersection(-sqrt(2.0)/2.0, glass_sphere),
		Intersection(sqrt(2.0)/2.0, glass_sphere) 
	};

	auto computation = Computation::Prepare(intersections[1], ray, intersections);

	// Act
	auto reflectance = computation.SchlickValue();

	// Assert
	assert(reflectance == 1.0);
}

void test_reflection_schlick_approximation_with_perpendicular_viewing_angle()
{
	// Setup
	Sphere3D glass_sphere(Material3D::Glass);
	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 1, 0));
	std::vector<const Intersection> intersections 
	{ 
		Intersection(-1.0, glass_sphere),
		Intersection(1.0, glass_sphere) 
	};

	auto computation = Computation::Prepare(intersections[1], ray, intersections);

	// Act
	auto reflectance = computation.SchlickValue();

	// Assert
	assert(Mathf<double>::Approximately(reflectance, 0.04));
}

void run_reflection_tests()
{
	test_precompute_reflection_vector();

	test_nonreflective_material();

	test_reflective_material();

	test_reflective_material_shade_hit();

	test_reflective_material_recursion();

	test_reflective_material_limit_recursion();

	test_reflective_n1_n2_intersections();

	test_reflective_under_point_is_offset_below_surface();

	test_refractive_color_with_opaque_surface();

	test_refractive_color_under_total_internal_reflection();

	test_refractive_color_with_refracted_ray();

	test_refractive_shade_hit_transparent_material();

	test_reflection_schlick_approximation_under_total_internal_reflection();

	test_reflection_schlick_approximation_with_perpendicular_viewing_angle();
}