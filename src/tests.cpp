#include <iostream>
#include <list>
#include <cassert>

#include "../lib/ray-tracer-core/Mathf.h"

#include "../lib/ray-tracer-core/Primitive3D.h"
#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "../lib/ray-tracer-core/Ray3D.h"
#include "../lib/ray-tracer-core/Sphere3D.h"
#include "../lib/ray-tracer-core/Intersection.h"

#include "../lib/ray-tracer-core/RayTracer.h"

#include "tests.h"
#include "../lib/graphics/Color.h"

using namespace std;

void test_matrix_scaling()
{
	// Set up
	Matrix4d m0 = Matrix4d::Scale(2, 3, 4);

	// Act
	Primitive3D<double> result0 = m0 * Point3D(-4, 6, 8);

	// Assert
	assert(Point3D(-8, 18, 32) == result0);
}

void test_matrix_rotate_quarter()
{
	// Set up
	Matrix4d quarter = Matrix4d::RotateX(M_PI / 2);

	Point3D point(0, 1, 0);

	// Act
	Primitive3D<double> result = quarter * point;

	// Assert
	assert(Point3D(0, 0, 1) == result);
}

void test_matrix_rotate_pi()
{
	// Set up
	Matrix4d quarter = Matrix4d::RotateX(M_PI);

	Point3D point(0, 1, 0);

	// Act
	Primitive3D<double> result = quarter * point;

	// Assert
	assert(Point3D(0, -1, 0) == result);
}

void test_matrix_rotate_half_quarter()
{
	// Set up
	Matrix4d quarter = Matrix4d::RotateX(M_PI / 4);

	Point3D point(0, 1, 0);

	// Act
	Primitive3D<double> result = quarter * point;

	// Assert
	assert(Point3D(0, sqrt(2) / 2.0, sqrt(2) / 2.0) == result);
}

void test_matrix_translation()
{
	// Set up
	Matrix4d m0 = Matrix4d::Translate(5, -3, 2);

	// Act
	Primitive3D<double> result0 = m0 * Point3D(-3, 4, 5);

	// Assert
	assert(Point3D(2, 1, 7) == result0);


	// Set up
	Matrix4d m1 = Matrix4d::Translate(5, -3, 2);
	Matrix4d m1_inverse = m1.Inverse();

	// Act
	Primitive3D<double> result1 = m1_inverse * Point3D(-3, 4, 5);

	// Assert
	assert(Point3D(-8, 7, 3) == result1);


	// Set up
	Matrix4d m2 = Matrix4d::Translate(5, -3, 2);

	// Act
	Primitive3D<double> result2 = m0 * Vector3D(-3, 4, 5);

	// Assert
	assert(Vector3D(-3, 4, 5) == result2);
}

void test_matrix_mul_tuple()
{
	// Set up
	Matrix4 m0{
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1
	};

	int tuple[4] = { 1, 2, 3, 1 };
	int tuple_mul[4];

	// Act
	matrix_mul(m0, tuple, tuple_mul);

	// Assert
	assert(18 == tuple_mul[0]);
	assert(24 == tuple_mul[1]);
	assert(33 == tuple_mul[2]);
	assert(1 == tuple_mul[3]);
}

void test_matrix_mul()
{
	// Set up
	Matrix<int, 3, 3> m0{
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> m1{
		1,2,3,
		4,5,6,
		7,8,9
	};

	// Act
	Matrix<int, 3, 3> identity = Matrix<int, 3, 3>::Identity();

	Matrix<int, 3, 3> mux = m0 * m1;
	Matrix<int, 3, 3> mux2 = mux * identity;

	Matrix<int, 2, 2> sub = m0.remove(2, 2);

	// Assert
	assert(m0 == m1);
	assert(mux == mux);

	assert(1 == sub.Data[0][0]);
	assert(2 == sub.Data[0][1]);
	assert(4 == sub.Data[1][0]);
	assert(5 == sub.Data[1][1]);
}

void test_matrix_remove()
{
	// Set up
	Matrix<int, 3, 3> m0{
		1,5,0,
		-3,2,7,
		0,6,-3
	};

	// Act
	Matrix<int, 2, 2> sub = m0.remove(0, 2);

	// Assert
	assert(-3 == sub.Data[0][0]);
	assert(2 == sub.Data[0][1]);
	assert(0 == sub.Data[1][0]);
	assert(6 == sub.Data[1][1]);
}

void test_matrix_determinant()
{
	// Set up
	Matrix<int, 2, 2> m2{
		 1, 5,
		-3, 2
	};

	Matrix<int, 3, 3> m3{
		 1, 2, 6,
		-5, 8,-4,
		 2, 6, 4
	};

	Matrix<int, 4, 4> m4{
		-2,-8, 3, 5,
		-3, 1, 7, 3,
		 1, 2,-9, 6,
		-6, 7, 7,-9
	};

	// Assert
	assert(17 == m2.determinant());

	assert(56 == m3.cofactor(0, 0));
	assert(12 == m3.cofactor(0, 1));
	assert(-46 == m3.cofactor(0, 2));
	assert(-196 == m3.determinant());

	assert(690 == m4.cofactor(0, 0));
	assert(447 == m4.cofactor(0, 1));
	assert(210 == m4.cofactor(0, 2));
	assert(51 == m4.cofactor(0, 3));
	assert(-4071 == m4.determinant());
}

void test_matrix_minor()
{
	// Set up
	Matrix3 m0{
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	// Act
	Matrix2 sub = m0.remove(1, 0);

	// Assert
	assert(25 == sub.determinant());
	assert(25 == m0.minor(1, 0));
}

void test_matrix_cofactor()
{
	// Set up
	Matrix<int, 3, 3> m0{
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	// Assert
	assert(-12 == m0.minor(0, 0));
	assert(-12 == m0.cofactor(0, 0));

	assert(25 == m0.minor(1, 0));
	assert(-25 == m0.cofactor(1, 0));
}

void test_matrix_inverse()
{
	// Set up
	Matrix4d m0{
		-8,-5, 9, 2,
		 7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0,-9,-4
	};

	Matrix4d m0_inverted{
	   -0.15385, -0.15385, -0.28205, -0.53846,
	   -0.07692,  0.12308,  0.02564,  0.03077,
		0.35897,  0.35897,  0.43590,  0.92308,
		0.69231, -0.69231, -0.76923, -1.92308
	};

	Matrix4d m1_error{
		-4, 2,-2,-3,
		 9, 6, 2, 6,
		 0,-5, 1,-5,
		 0, 0, 0, 0
	};

	Matrix4d a{
		 3,-9, 7, 3,
		 3,-8, 2,-9,
		-4, 4, 4, 1,
		-6, 5,-1, 1
	};

	Matrix4d b{
		 8, 2, 2, 2,
		 3,-1, 7, 0,
		 7, 0, 5, 4,
		 6,-2, 0, 5
	};

	// Assert
	assert(m1_error.Inverse() == matrix_zero_4d);
	assert(m0.Inverse() != matrix_zero_4d);
	assert((a * b * b.Inverse()) == a);
}

void test_matrix_shearing()
{
	// Set up
	Matrix4d m0 = Matrix4d::Shearing(1, 0, 0, 0, 0, 0);
	Matrix4d m1 = Matrix4d::Shearing(0, 1, 0, 0, 0, 0);
	Matrix4d m2 = Matrix4d::Shearing(0, 0, 0, 1, 0, 0);

	Point3D point(2, 3, 4);

	// Act
	auto result = m0 * point;

	// Assert
	assert(Point3D(5, 3, 4) == result);

	// Act
	result = m1 * point;

	// Assert
	assert(Point3D(6, 3, 4) == result);

	// Act
	result = m2 * point;

	// Assert
	assert(Point3D(2, 7, 4) == result);
}



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


void test_sphere_default_transform()
{
	// Set up
	Sphere3D sphere;

	// Assert
	assert(Matrix4d::Identity() == sphere.Transformation());
}

void test_sphere_set_transform()
{
	// Set up
	Sphere3D sphere;
	Matrix4d transform = Matrix4d::Translate(2, 3, 4);

	// Act
	sphere.SetTransformation(transform);

	// Assert
	assert(Matrix4d::Translate(2, 3, 4) == sphere.Transformation());
}

void test_sphere()
{
	test_sphere_default_transform();

	test_sphere_set_transform();
}

void test_ray_intersect()
{	
	// Set up
	Ray3D ray(Point3D(0, 1, -5), Vector3D(0, 0, 1));
	Sphere3D sphere;

	// Act
	auto res  = ray_intersect(sphere, ray);

	// Assert
	assert(2 == res.size());

	auto first = res.begin();

	assert(5.0 == (*first++).T());
	assert(5.0 == (*first).T());


	// Set up
	Ray3D ray2(Point3D(0, 0, 0), Vector3D(0, 0, 1));

	// Act
	res = ray_intersect(sphere, ray2);

	// Assert
	assert(2 == res.size());

	first = res.begin();

	assert(-1.0 == (*first++).T());
	assert(1.0 == (*first).T());


	// Set up
	Ray3D ray3(Point3D(0, 2, -5), Vector3D(0, 0, 1));

	// Act
	res = ray_intersect(sphere, ray3);

	// Assert
	assert(0 == res.size());
}

void test_ray_transform()
{
	// Set up
	Ray3D ray(Point3D(1, 2, 3), Vector3D(0, 1, 0));

	auto transform = Matrix4d::Translate(3, 4, 5);

	// Act
	auto result = ray.Transform(transform);

	// Assert
	assert(Point3D(4, 6, 8) == result.Location());
	assert(Vector3D(0, 1, 0) == result.Direction());

	// Set up
	transform = Matrix4d::Scale(2, 3, 4);

	// Act
	result = ray.Transform(transform);

	// Assert
	assert(Point3D(2, 6, 12) == result.Location());
	assert(Vector3D(0, 3, 0) == result.Direction());
}

void test_ray_positive_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(1, sphere),
		intersection2(2, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto result = ray_hit(intersections);

	// Assert
	assert(intersection1 == result);
}

void test_ray_some_negative_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(-1, sphere),
		intersection2(1, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto result = ray_hit(intersections);

	// Assert
	assert(intersection2 == result);
}

void test_ray_some_all_negative_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(-2, sphere),
		intersection2(-1, sphere);

	std::list<Intersection> intersections = {
		intersection1,
		intersection2
	};

	// Act
	auto result = ray_hit(intersections);

	// Assert
	assert(Intersection::Empty == result);
}

void test_ray_mixed_hits()
{
	// Set up
	Sphere3D sphere;

	Intersection
		intersection1(5, sphere),
		intersection2(7, sphere),
		intersection3(-3, sphere),
		intersection4(2, sphere);

	std::list<Intersection> intersections1 = {
		intersection1,
		intersection2,
		intersection3,
		intersection4
	};

	// Act
	auto result = ray_hit(intersections1);

	// Assert
	assert(intersection4 == result);
}

void test_ray_hits()
{
	test_ray_positive_hits();

	test_ray_some_negative_hits();

	test_ray_some_all_negative_hits();

	test_ray_mixed_hits();
}

void test_ray_sphere_scale_intersect()
{
	// Set up
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Sphere3D sphere;

	// Act
	sphere.SetTransformation(Matrix4d::Scale(2, 2, 2));

	auto res = ray_intersect(sphere, ray);

	// Assert
	assert(2 == res.size());

	auto first = res.begin();

	assert(3.0 == (*first++).T());
	assert(7.0 == (*first).T());
}

void test_ray_sphere_translate_intersect()
{
	// Set up
	Ray3D ray(Point3D(0, 0, -5), Vector3D(0, 0, 1));
	Sphere3D sphere;

	// Act
	sphere.SetTransformation(Matrix4d::Translate(5, 0, 0));

	auto res = ray_intersect(sphere, ray);

	// Assert
	assert(0 == res.size());
}

void test_color_rgb565()
{
	// Set up
	Color<Rgba> red = Rgba::Red;
	Color<Rgba> purple{ 128, 0, 128, 0 };
	Color<Rgba> gray { 128, 128, 128, 0 };

	// Act
	auto red565 = red.Channels.ToRgb565();
	auto purple565 = purple.Channels.ToRgb565();
	auto gray565 = gray.Channels.ToRgb565();

	// Assert
	assert(0xF800 == red565);
	assert(0x780F == purple565);
	assert(0x7BEF == gray565);
}

void run_tests()
{
	test_matrix_mul();

	test_matrix_mul_tuple();

	test_matrix_remove();

	test_matrix_translation();

	test_matrix_determinant();

	test_matrix_minor();

	test_matrix_cofactor();

	test_matrix_inverse();

	test_matrix_scaling();

	test_matrix_rotate_quarter();

	test_matrix_rotate_pi();

	test_matrix_rotate_half_quarter();

	test_matrix_shearing();

	test_vector_dot();

	test_sphere();

	test_ray_intersect();

	test_ray_hits();

	test_ray_transform();

	test_ray_sphere_scale_intersect();

	test_ray_sphere_translate_intersect();

	test_color_rgb565();
}