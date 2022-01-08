#pragma once

#include "Matrix.h"

template<typename  TItem, int TSizeX, int TSizeY>
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