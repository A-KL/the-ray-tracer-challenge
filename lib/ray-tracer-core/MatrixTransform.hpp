#pragma once

#include <math.h> 

#include "Matrix.h"
#include "MatrixBase.hpp"

#define PI 3.14159265

template<class TItem>
void matrix_translate(
	TItem x,
	TItem y,
	TItem z,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[3][0] = x;
	result.Data[3][1] = y;
	result.Data[3][2] = z;
}

template<class TItem>
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

template<class TItem>
void matrix_rotate_x(
	double r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);
	//r * PI / 180
	result.Data[1][1] = cos(r);
	result.Data[2][1] = -sin(r);
	result.Data[1][2] = sin(r);
	result.Data[2][2] = cos(r);
}

template<class TItem>
void matrix_rotate_y(
	float r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][0] = cos(r);
	result.Data[2][0] = sin(r);
	result.Data[0][2] =-sin(r);
	result.Data[2][2] = cos(r);
}

template<class TItem>
void matrix_rotate_z(
	float r,
	Matrix<TItem, 4, 4>& result)
{
	matrix_identity(result);

	result.Data[0][0] = cos(r);
	result.Data[1][0] =-sin(r);
	result.Data[0][2] = sin(r);
	result.Data[1][1] = cos(r);
}