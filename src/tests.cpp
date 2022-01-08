#include <iostream>
#include <list>
#include <cassert>

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"

#include "ray-tracer/Matrix.h"
#include "ray-tracer/MatrixOps.hpp"

#include "tests.h"

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
	Matrix<int, 3, 3> m0 {
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
	Matrix<int, 3, 3> m0 {
		1,2,3,
		4,5,6,
		7,8,9
	};

	Matrix<int, 3, 3> m1 {
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
	Matrix<int, 3, 3> m0 {
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
	Matrix<int, 2, 2> m2 {
		 1, 5,
		-3, 2	
	};

	Matrix<int, 3, 3> m3 {
		 1, 2, 6,
		-5, 8,-4,
		 2, 6, 4
	};

	Matrix<int, 4, 4> m4 {
		-2,-8, 3, 5,
		-3, 1, 7, 3,
		 1, 2,-9, 6,
		-6, 7, 7,-9
	};

	// Assert
	assert(17 == matrix_determinant(m2));

	assert(56 == matrix_cofactor(m3, 0, 0));
	assert(12 == matrix_cofactor(m3, 0, 1));
	assert(-46 == matrix_cofactor(m3, 0, 2));
    assert(-196 == matrix_determinant(m3));

	assert(690 == matrix_cofactor(m4, 0, 0));
	assert(447 == matrix_cofactor(m4, 0, 1));
	assert(210 == matrix_cofactor(m4, 0, 2));
	assert(51 == matrix_cofactor(m4, 0, 3));
	assert(-4071 == matrix_determinant(m4));
}

void test_matrix_minor()
{
	// Set up
	Matrix3 m0 {
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	Matrix2 sub;

	matrix_remove(m0, 1, 0, sub);

	int d_sub = matrix_determinant(sub);

	int minor = matrix_minor(m0, 1, 0);

	// Assert
	assert(25 == d_sub);
	assert(25 == minor);
}

void test_matrix_cofactor()
{
	// Set up
	Matrix<int, 3, 3> m0 {
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	// Assert
	assert(-12 == matrix_minor(m0, 0, 0));
	assert(-12 == matrix_cofactor(m0, 0, 0));

	assert(25 == matrix_minor(m0, 1, 0));
	assert(-25 == matrix_cofactor(m0, 1, 0));
}

void test_matrix_inverse()
{
	// Set up
	Matrix<float, 4, 4> invertable {
		-8,-5, 9, 2,
		 7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0,-9,-4
	};

	Matrix<float, 4, 4> inverted_result{
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692,  0.12308,  0.02564,  0.03077,
		 0.35897,  0.35897,  0.43590,  0.92308,
		 0.69231, -0.69231, -0.76923, -1.92308
	};

	Matrix<float, 4, 4> noninvertable{
		 -4, 2,-2,-3,
		  9, 6, 2, 6,
		  0,-5, 1,-5,
		  0, 0, 0, 0
	};

	Matrix<float, 4, 4> a {
		 3, -9,  7,  3,
		 3, -8,  2, -9,
		-4,  4,  4,  1,
		-6,  5, -1,  1
	};


	Matrix<float, 4, 4> b {
		 8,  2, 2, 2,
		 3, -1, 7, 0,
		 7,  0, 5, 4,
		 6, -2, 0, 5
	};

	Matrix<float, 4, 4> inverted, c, b_inverted, a_result;

	//Act
	matrix_mul(a, b, c);
	matrix_inverse(b, b_inverted);
	matrix_mul(c, b_inverted, a_result);

	// Assert
	assert(!matrix_inverse(noninvertable, inverted));
	assert(matrix_inverse(invertable, inverted));
	assert(inverted_result == inverted);

	assert(a_result == a);
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
}