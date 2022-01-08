#include <iostream>
#include <list>
#include <cassert>

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"

#include "ray-tracer/Matrix.h"
#include "ray-tracer/Matrix.cpp"

#include "tests.h"

//#include "ray-tracer/matrix_basic.h"

template<class TItem, int TSizeX, int TSizeY>
const TItem matrix_cofactor(
	const Matrix<TItem, TSizeX, TSizeY>& matrix, int row, int col)
{
	TItem minor = matrix_minor(matrix, row, col);
	
	return ((row + col) % 2) ? -minor : minor;
}

template<class TItem, int TSizeX, int TSizeY>
const TItem matrix_minor(
	const Matrix<TItem, TSizeX, TSizeY>& matrix, int row, int col)
{
	Matrix<TItem, TSizeX - 1, TSizeY - 1> result;

	matrix_remove(matrix, row, col, result);

	return matrix_determinant(result);
}

template<class TItem, int TSizeX, int TSizeY>
const TItem matrix_determinant(
	const Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	TItem determinant = 0;
	
	for (int col = 0; col < TSizeY; col++)
	{
		determinant += matrix.Data[0][col] * matrix_cofactor(matrix, 0, col);
	}
	
	return determinant;
}

template<class TItem>
const TItem matrix_determinant(
	const Matrix<TItem, 2, 2>& matrix)
{
	return matrix.Data[0][0] * matrix.Data[1][1] - matrix.Data[0][1] * matrix.Data[1][0];
}

template<class TItem>
const TItem matrix_determinant(
	const Matrix<TItem, 1, 1>& matrix)
{
	return matrix.Data[0][0];
}

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