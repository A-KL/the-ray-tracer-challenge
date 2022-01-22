#pragma once

#include <math.h> 

#define PI 3.14159265

template<typename TItem>
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
	result.Data[1][1] = cos(r);
	result.Data[2][1] = -sin(r);
	result.Data[1][2] = sin(r);
	result.Data[2][2] = cos(r);
}

template<typename TItem>
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

template<typename TItem>
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

template<typename TItem>
void matrix_rotate_z(
	int d,
	Matrix<TItem, 4, 4>& result)
{
	matrix_rotate_z((d / 180.0 * PI), result)
}

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

	result.Data[1][0] = xy;
	result.Data[2][0] = xz;

	result.Data[0][1] = yx;
	result.Data[2][1] = yz;

	result.Data[0][2] = zx;
	result.Data[1][2] = zy;
}