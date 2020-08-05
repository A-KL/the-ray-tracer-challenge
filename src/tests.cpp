#include "tests.h"

#include <iostream>
#include <list>
#include <cassert>

#include <SDL.h>

#include "renderer/Color.h"
#include "renderer/SDLRenderer.h"

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"
#include "ray-tracer/Matrix.h"

using namespace std;

void test_matrix_translation()
{
	Matrix<int, 4, 4> transform;

	matrix_identity(transform);
	matrix_translate(5, -3, 2, transform);

	int point[4] = { -3, 4, 5, 1 };
	int result[4];

	matrix_mul(transform, point, result);

	assert(2 == result[0]);
	assert(1 == result[1]);
	assert(7 == result[2]);
}

void test_matrix_mul_tuple()
{
	Matrix<int, 3, 3> m0 = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	int tuple[3] = { 2, 2, 2 };

	int tuple_mul[3];

	matrix_mul(m0, tuple, tuple_mul);

	assert(24 == tuple_mul[0]);
	assert(30 == tuple_mul[1]);
	assert(36 == tuple_mul[2]);
}

void test_matrix_mul()
{
	// Set up

	Matrix<int, 3, 3> m0 = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> m1 = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> identity;
	matrix_identity(identity);

	Matrix<int, 3, 3> mux;
	matrix_mul(m0, m1, mux);

	Matrix<int, 3, 3> mux2;
	matrix_mul(mux, identity, mux2);

	Matrix<int, 2, 2> sub;
	matrix_remove(m0, 2, 2, sub);

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

	Matrix<int, 3, 3> m0 = {
		1,5,0,
		-3,2,7,
		0,6,-3
	};

	Matrix<int, 2, 2> sub;

	matrix_remove(m0, 0, 2, sub);

	// Assert

	assert(-3 == sub.Data[0][0]);
	assert(2 == sub.Data[0][1]);
	assert(0 == sub.Data[1][0]);
	assert(6 == sub.Data[1][1]);
}

void test_matrix_determinant()
{
	// Set up

	Matrix<int, 2, 2> m0 = {
		1,5,
		-3,2
	};

	// Assert

	assert(17 == m0.Determinant());
}

void test_matrix_minor()
{
	// Set up

	Matrix<int, 3, 3> m0 = {
		3,5,0,
		2,-1,-7,
		6,-1,5
	};

	Matrix<int, 2, 2> sub;

	matrix_remove(m0, 1, 0, sub);

	int d_sub = sub.Determinant();

	int minor = m0.Minor(1, 0);

	// Assert

	assert(25 == d_sub);
	assert(25 == minor);
}

void test_matrix_cofactor()
{
	// Set up

	Matrix<int, 3, 3> m0 = {
		3,5,0,
		2,-1,-7,
		6,-1,5
	};

	// Assert

	assert(-12 == m0.Minor(0, 0));
	assert(-12 == m0.Cofactor(0,0));

	assert(25 == m0.Minor(1, 0));
	assert(-25 == m0.Cofactor(1, 0));
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
}