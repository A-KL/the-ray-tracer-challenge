#pragma once

#define _USE_MATH_DEFINES
#include <cassert>
#include <math.h> 
#include "Mathf.h"

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
void matrix_zero(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	memset(matrix.Data, 0, (TSizeX * TSizeY * sizeof(TItem)));
}

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
void matrix_identity(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	assert(TSizeX == TSizeY);

	matrix_zero(matrix);

	for (unsigned x = 0; x < TSizeX; x++)
	{
		matrix.Data[x][x] = true;
	}
}

template<typename TItem>
void matrix_translate(
	TItem x,
	TItem y,
	TItem z,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][3] = x;
	result.Data[1][3] = y;
	result.Data[2][3] = z;
}

template<typename TItem>
void matrix_scale(
	TItem x,
	TItem y,
	TItem z,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][0] = x;
	result.Data[1][1] = y;
	result.Data[2][2] = z;
}

template<typename TItem>
void matrix_rotate_x(
	double r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);
	//r * PI / 180
	result.Data[1][1] = Mathf::ToZeroIfClose(cos(r));
	result.Data[1][2] = -Mathf::ToZeroIfClose(sin(r));
	result.Data[2][1] = Mathf::ToZeroIfClose(sin(r));
	result.Data[2][2] = Mathf::ToZeroIfClose(cos(r));
}

template<typename TItem>
void matrix_rotate_y(
	float r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][0] = Mathf::ToZeroIfClose(cos(r));
	result.Data[0][2] = Mathf::ToZeroIfClose(sin(r));
	result.Data[2][0] = -Mathf::ToZeroIfClose(sin(r));
	result.Data[2][2] = Mathf::ToZeroIfClose(cos(r));
}

template<typename TItem>
void matrix_rotate_z(
	float r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][0] = Mathf::ToZeroIfClose(cos(r));
	result.Data[0][1] = -Mathf::ToZeroIfClose(sin(r));
	result.Data[1][0] = Mathf::ToZeroIfClose(sin(r));
	result.Data[1][1] = Mathf::ToZeroIfClose(cos(r));
}

//template<typename TItem>
//void matrix_rotate_z(
//	int d,
//	Matrix<TItem, 4, 4>& result)
//{
//	matrix_rotate_z((d / 180.0 * PI), result)
//}

template<typename TItem>
void matrix_shearing(
	TItem xy,
	TItem xz,
	TItem yx,
	TItem yz,
	TItem zx,
	TItem zy,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][1] = xy;
	result.Data[0][2] = xz;

	result.Data[1][0] = yx;
	result.Data[1][2] = yz;

	result.Data[2][0] = zx;
	result.Data[2][1] = zy;
}