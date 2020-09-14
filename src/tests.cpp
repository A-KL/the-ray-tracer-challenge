#include "tests.h"

#include <iostream>
#include <list>
#include <cassert>

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"

#include "ray-tracer/Matrix.h"
#include "ray-tracer/Matrix.cpp"

//#include "ray-tracer/matrix_basic.h"

#pragma once

template<class TItem, int TSizeX, int TSizeY>
void matrix_remove(
	const Matrix<TItem, TSizeX, TSizeY>& matrix,
	int row, int col,
	Matrix<TItem, TSizeX - 1, TSizeX - 1>& result)
{
	int x, y, x1, y1;

	for (x = 0, x1 = 0; x < TSizeX; x++)
	{
		if (x == row)
			continue;

		for (y = 0, y1 = 0; y < TSizeY; y++)
		{
			if (y == col)
				continue;

			result.Data[x1][y1] = matrix.Data[x][y];
			y1++;
		}
		x1++;
	}
}

template<class TItem, int TSizeX, int TSizeY>
void matrix_identity(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	int x, y;

	for (x = 0; x < TSizeX; x++)
	{
		for (y = 0; y < TSizeY; y++)
		{
			matrix.Data[x][y] = (x == y);
		}
	}
}

template<class TItem, int TSizeX, int TSizeY>
void matrix_inverse(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	//???
}

template<class TItem, int TSizeX, int TSizeY>
void matrix_mul(
	const Matrix<TItem, TSizeX, TSizeY>& matrix1,
	const Matrix<TItem, TSizeX, TSizeY>& matrix2,
	Matrix<TItem, TSizeX, TSizeY>& result)
{
	int x, y, j;

	for (x = 0; x < TSizeX; x++)
	{
		for (y = 0; y < TSizeY; y++)
		{
			result.Data[x][y] = 0;

			for (j = 0; j < TSizeY; j++)
			{
				result.Data[x][y] += matrix1.Data[x][j] * matrix2.Data[j][y];
			}
		}
	}
}

template<class TItem>
void matrix_mul(
	const Matrix<TItem, 3, 3>& matrix,
	const Vector3D& other,
	Vector3D& result)
{
	result.X = matrix.Data[0][0] * other.X + matrix.Data[1][0] * other.Y + matrix.Data[2][0] * other.Z;
	result.Y = matrix.Data[0][1] * other.X + matrix.Data[1][1] * other.Y + matrix.Data[2][1] * other.Z;
	result.Z = matrix.Data[0][2] * other.X + matrix.Data[1][2] * other.Y + matrix.Data[2][2] * other.Z;
}

template<class TItem, int TSize>
void matrix_mul(
	const Matrix<TItem, TSize, TSize>& matrix,
	const TItem other[],
	TItem result[])
{
	int x, index;

	for (index = 0; index < TSize; index++)
	{
		result[index] = 0;

		for (x = 0; x < TSize; x++)
		{
			result[index] += (other[x] * matrix.Data[x][index]);
		}
	}
}

template<class TItem, int TSizeX, int TSizeY>
void matrix_transpose(
	const Matrix<TItem, TSizeX, TSizeY>& matrix,
	Matrix<TItem, TSizeX, TSizeY>& result)
{
	int x, y;

	for (x = 0; x < TSizeX; x++)
	{
		for (y = 0; y < TSizeY; y++)
		{
			result.Data[y][x] = matrix.Data[y][x];
		}
	}
}

template<class TItem>
void matrix_translate(
	TItem x,
	TItem y,
	TItem z,
	Matrix<TItem, 4, 4>& result)
{
	result.Data[3][0] = x;
	result.Data[3][1] = y;
	result.Data[3][2] = z;
}

template<class TItem>
void matrix_scaling(
	TItem x,
	TItem y,
	TItem z,
	Matrix<TItem, 4, 4>& result)
{
	result.Data[3][0] = x;
	result.Data[3][1] = y;
	result.Data[3][2] = z;
}

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
	Matrix2<int> m2{
		 1, 5,
		-3, 2	
	};

	Matrix3<int> m3{
		 1, 2, 6,
		-5, 8,-4,
		 2, 6, 4
	};

	Matrix4<int> m4{
		-2,-8, 3, 5,
		-3, 1, 7, 3,
		 1, 2,-9, 6,
		-6, 7, 7,-9
	};

	// Assert
	assert(17 == m2.Determinant());

	assert(56 == m3.Cofactor(0, 0));
	assert(12 == m3.Cofactor(0, 1));
	assert(-46 == m3.Cofactor(0, 2));
	assert(-196 == m3.Determinant());

	assert(690 == m4.Cofactor(0, 0));
	assert(447 == m4.Cofactor(0, 1));
	assert(210 == m4.Cofactor(0, 2));
	assert(51 == m4.Cofactor(0, 3));
	//assert(-4071 == m4.Determinant());
}

void test_matrix_minor()
{
	// Set up
	Matrix3<int> m0 {
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	Matrix2<int> sub;

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
	Matrix3<int> m0 {
		3, 5, 0,
		2,-1,-7,
		6,-1, 5
	};

	// Assert
	assert(-12 == m0.Minor(0, 0));
	assert(-12 == m0.Cofactor(0, 0));

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