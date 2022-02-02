#include <iostream>
#include <list>
#include <cassert>

#include "../lib/ray-tracer-core/Primitive3D.h"
#include "../lib/ray-tracer-core/Vector3D.h"
#include "../lib/ray-tracer-core/Point3D.h"

#include "../lib/ray-tracer-core/Mathf.h"

#include "../lib/ray-tracer-core/Matrix.hpp"
#include "../lib/ray-tracer-core/MatrixOps.hpp"
#include "../lib/ray-tracer-core/MatrixTransform.hpp"

#include "../lib/ray-tracer-core/Ray3D.h"
#include "../lib/ray-tracer-core/Sphere3D.h"

#include "tests.h"

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
	Matrix4d m1_inverse = m1.inverse();

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
	Matrix<int, 3, 3> identity = Matrix<int, 3, 3>::identity();

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
	assert(m1_error.inverse() == matrix_zero_4d);
	assert(m0.inverse() != matrix_zero_4d);
	assert((a * b * b.inverse()) == a);
}

void test_matrix_shearing()
{
	// Set up
	Matrix4d m0 = Matrix4d::shearing(1, 0, 0, 0, 0, 0);
	Matrix4d m1 = Matrix4d::shearing(0, 1, 0, 0, 0, 0);
	Matrix4d m2 = Matrix4d::shearing(0, 0, 0, 1, 0, 0);

	Point3D point(2, 3, 4);

	// Act
	Primitive3D<double> result = m0 * point;

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

void test_sphere()
{
	Sphere3D sphere;

	assert(1, sphere.R());
}

int ray_intersect(const Object3D& object, const Ray3D& ray)
{
	Vector3D object_to_ray = ray.Location() - object.Location();

	float a = Vector3D::Dot(ray.Direction(), ray.Direction());

	float b = 2 * Vector3D::Dot(ray.Direction(), object_to_ray);

	float c = Vector3D::Dot(object_to_ray, object_to_ray) - 1;

	float d = powf(b, 2) - 4 * a * c;

	if (d < 0)
	{
		return 0;
	}

	float t1 = (-b - sqrtf(d)) / (2 * a);
	float t2 = (-b + sqrtf(d)) / (2 * a);
	//Intersections<2> result();

	return 2;
}

void test_ray_intersect()
{
	Ray3D ray(Point3D(0, 1, -5), Vector3D(0, 0, 1));
	Sphere3D sphere;

	int res = ray_intersect(sphere, ray);

	assert(2, res);
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

	test_sphere();

	test_ray_intersect();
}