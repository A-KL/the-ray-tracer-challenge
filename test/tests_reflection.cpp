#include <iostream>
#include <list>
#include <tuple>
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

/* Reflection  */

// Test #2: Compute the reflectv Vector
//
// Show that the prepare_computations() function precomputes the reflectv vector.
//
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

// Test #3: Strike a Nonreflective Surface
//
// Show that when a ray strikes a nonreflective surface, the reflected_color() function returns the color black.
//
void test_reflected_color_nonreflective_material()
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

// Test #4: Strike a Reflective Surface
//
// Show that reflected_color() returns the color via reflection when the struck surface is reflective.
//
void test_reflected_color_reflective_material()
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

// Test #5: Update the shade_hit Function
// 
// Show that shade_hit() incorporates the reflected color into the final color
//
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

// Test #6: Avoid Infinite Recursion
//
// Show that shade_hit() recursively reflects the scene
//
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
	auto color = scene.ColorAt(ray); // should terminate successfully
}

// Test #7: Limit Recursion
//
// Show that reflected_color() returns without effect when invoked at the limit of its recursive threshold.
//
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

/* Transparency and Refraction */

// Test #2: Determining n1 and n2
//
// Show that prepare_computations() determines n1 and n2 correctly at six different points of intersection
//
void test_prepare_computations_finds_n1_n2()
{
	// Input
	std::tuple<int, float, float> test_cases[] = {
		std::make_tuple(0, 1.0, 1.5),
		std::make_tuple(1, 1.5, 2.0),
		std::make_tuple(2, 2.0, 2.5),
		std::make_tuple(3, 2.5, 2.5),
		std::make_tuple(4, 2.5, 1.5),
		std::make_tuple(5, 1.5, 1.0)
	};

	// Set up
	Material3D glass = Material3D::Glass;

	Sphere3D a(
		Matrix4d::Scale(2, 2, 2), 
		glass.With([](Material3D& m) -> void { m.RefractiveIndex = 1.5; }));

	Sphere3D b(
		Matrix4d::Translate(0, 0, -0.25), 
		glass.With([](Material3D& m) -> void { m.RefractiveIndex = 2.0; }));

	Sphere3D c(
		Matrix4d::Translate(0, 0, 0.25), 
		glass.With([](Material3D& m) -> void { m.RefractiveIndex = 2.5; }));

	Ray3D ray(
		Point3D(0, 0, -4), 
		Vector3D(0, 0, 1));

	std::vector<Intersection> intersections = {
		Intersection(2, a),
		Intersection(2.75, b),
		Intersection(3.25, c),
		Intersection(4.75, b),
		Intersection(5.25, c),
		Intersection(6, a)
	};

	for(auto& [index, n1, n2] : test_cases)
	{
		// Act
		auto comps = Computation::Prepare(intersections[index], ray, intersections);

		// Assert
		assert(comps.N1 == n1);
		assert(comps.N2 == n2);
	}

	//std::cout << "test_prepare_computations_finds_n1_n2() passed." << std::endl;
}

// Test #3: Computing under_point
//
// Show that prepare_computations() computes a new attribute, under_point, which lies just beneath the intersected surface.
//
void test_computing_under_point()
{
	// Set up
	Sphere3D shape(
		Matrix4d::Translate(0, 0, 1), 
		Material3D::Glass);

	Ray3D ray(
		Point3D(0, 0, -5), 
		Vector3D(0, 0, 1));

	Intersection intersection(5, shape);

	std::vector<Intersection> intersections = {
		intersection
	};

	// Act
	auto computation = Computation::Prepare(intersection, ray, intersections);

	// Assert
	assert(computation.UnderPosition.Z() > (Mathf<double>::Epsilon() / 2.0));
	assert(computation.Position.Z() < computation.UnderPosition.Z());

	// std::cout << "test_computing_under_point() passed." << std::endl;
}

// Test #4: Finding the Refracted Color of an Opaque Object
//
// Introduce a new function, refracted_color(world, comps, remaining), and show that it returns the color black when the hit applies to an opaque object.
//
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

	const std::vector<Intersection> intersections 
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

// Test #5: Finding the Refracted Color at the Maximum Recursive Depth
//
// Show that refracted_color() returns the color black when invoked at the maximum recursive depth, when there are no remaining recursive calls available.
//
void test_refracted_color_at_maximum_depth()
{	
	// Default world
	Scene3D scene;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Material3D material1(SolidColor3D(0.8, 1.0, 0.6), 0.1, 0.7, 0.2);

	auto m = material1
		.With([](Material3D& m) -> void { m.Transparency = 1.0;  m.RefractiveIndex = 1.5;});

	Sphere3D sphere1(material1);
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	scene.Lights.push_back(&light);
	scene.Shapes.push_back(&sphere1);
	scene.Shapes.push_back(&sphere2);

	// Setup
	auto first_shape = *scene.Shapes.begin();

	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));

	const std::vector<Intersection> intersections 
	{ 
		Intersection(4, first_shape),
		Intersection(6, first_shape) 
	};
	
	// Act
	auto computation = Computation::Prepare(intersections[0], ray, intersections);

	auto c = scene.RefractedAt(computation, 0);

	// Assert
	assert(c == Color3D::Black);
}

// Test #6: Finding the Refracted Color under Total Internal Reflection
//
// Show that refracted_color() returns the color black when the conditions are right for total internal reflection.
//
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

	const std::vector<Intersection> intersections 
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

// Test #7: Finding the Refracted Color
//
// Show that refracted_color() in all other cases will spawn a secondary ray in the correct direction, and return its color
//
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

	const std::vector<Intersection> intersections 
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

// Test #8: Handling Refraction in shade_hit
//
// Show that your shade_hit() function handles refraction.
//
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
		0.0, /* reflective */
		0.5, /* transparency */
		1.5  /* refractive index */
	);

	Plane3D floor(
		Matrix4d::Translate(0, -1, 0), floor_material
	);

	Material3D ball_material(
		SolidColor3D(1, 0, 0), 
		0.5 /* ambient */
	);

	Sphere3D ball(
		Matrix4d::Translate(0, -3.5, -0.5), ball_material
	);

	scene.Shapes.push_back(&floor);
	scene.Shapes.push_back(&ball);

	Ray3D ray(
		Point3D(0, 0, -3), 
		Vector3D(0, (-sqrt(2.0)/2.0), 
		(sqrt(2.0)/2.0))
	);

	const std::vector<Intersection> intersections 
	{ 
		Intersection(sqrt(2.0), floor)
	};

	// Act
	auto computation = Computation::Prepare(intersections[0], ray, intersections);
	auto c = scene.ShadeHit(computation, 5);

	// Assert
	assert(c == Color3D(0.93642, 0.68642, 0.68642));
}

/* Fresnel Effect */

// Test #1: Determine Reflectance under Total Internal Reflection
//
// Show that schlick() returns a 1 when conditions are right for total internal reflection.
//
void test_reflection_schlick_approximation_under_total_internal_reflection()
{
	// Setup
	Sphere3D glass_sphere(Material3D::Glass);
	Ray3D ray(Point3D(0, 0, sqrt(2.0)/2.0), Vector3D(0, 1, 0));
	const std::vector<Intersection> intersections 
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

// Test #2: Determine Reflectance of a Perpendicular Ray
//
// Show that reflectance (via schlick()) is small when a ray strikes the surface at a perpendicular angle.
//
void test_reflection_schlick_approximation_with_perpendicular_viewing_angle()
{
	// Setup
	Sphere3D glass_sphere(Material3D::Glass);
	Ray3D ray(Point3D(0, 0, 0), Vector3D(0, 1, 0));
	const std::vector<Intersection> intersections 
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

// Test #3: Determine Reflectance when n2 > n1
//
// Show that reflectance (via schlick()) is significant when n2 > n1 and the ray strikes the surface at a small angle.
//
void test_reflection_n2_more_n1()
{
	// Setup
	Sphere3D glass_sphere(Material3D::Glass);
	Ray3D ray(Point3D(0, 0.99, -2), Vector3D(0, 0, 1));
	const std::vector<Intersection> intersections 
	{ 
		Intersection(1.8589, glass_sphere)
	};

	auto computation = Computation::Prepare(intersections[0], ray, intersections);

	// Act
	auto reflectance = computation.SchlickValue();

	// Assert
	assert(Mathf<double>::Approximately(reflectance, 0.48873));
}

// Test #4: Employ Reflectance When Combining Reflection and Refraction
//
// Show that the schlick() reflectance value is used by shade_hit() when a material is both transparent and reflective.
//
void test_reflectance_when_combining_reflection_refraction()
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
	Ray3D ray(Point3D(0, 0, -3), Vector3D(0, (-sqrt(2.0)/2.0), (sqrt(2.0)/2.0)));

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

	scene.Shapes.push_back(&floor);

	Material3D ball_material(
		SolidColor3D(1.0, 0, 0),
		0.5, /* ambient */
		0.9, /* diffuse */
		0.2, /* specular */
		200, 
		0.0, /* reflective */
		0.0, /* transparency */
		1.0  /* refractive index */
	);

	Sphere3D ball(Matrix4d::Translate(0, -3.5, -0.5), ball_material);

	scene.Shapes.push_back(&ball);

	const std::vector<Intersection> intersections 
	{ 
		Intersection(sqrt(2.0), floor)
	};

	auto computation = Computation::Prepare(intersections[0], ray, intersections);

	// Act
	auto c = scene.ShadeHit(computation, 5);

	// Assert
	assert(c == Color3D(0.93391, 0.69643, 0.69243));
}

/* Run all reflection tests */

void run_reflection_tests()
{
	/* Reflection  */

	test_precompute_reflection_vector();

	test_reflected_color_nonreflective_material();

	test_reflected_color_reflective_material();

	test_reflective_material_shade_hit();

	test_reflective_material_recursion();

	test_reflective_material_limit_recursion();

  /* Transparency and Refraction */

	test_prepare_computations_finds_n1_n2();

	test_computing_under_point();

	test_refractive_color_with_opaque_surface();

	test_refracted_color_at_maximum_depth();

	test_refractive_color_under_total_internal_reflection();

	test_refractive_color_with_refracted_ray();

  test_refractive_shade_hit_transparent_material();

	/* Fresnel Effect  */

	test_reflection_schlick_approximation_under_total_internal_reflection();

	test_reflection_schlick_approximation_with_perpendicular_viewing_angle();	

	test_reflection_n2_more_n1();

	test_reflectance_when_combining_reflection_refraction();
}