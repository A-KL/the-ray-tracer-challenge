#pragma once

#include "Matrix.h"
#include "MatrixBase.hpp"

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