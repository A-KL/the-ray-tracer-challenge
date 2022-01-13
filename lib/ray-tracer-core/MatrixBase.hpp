#pragma once

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
void matrix_identity(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	assert(TSizeX == TSizeY);

	matrix_zero(matrix);
	
	unsigned x, y;

	for (x = 0, y = 0; x < TSizeX; x++, y++)
	{
		matrix.Data[x][y] = true;
	}
}

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
inline Matrix<TItem, TSizeX, TSizeY> matrix_identity()
{
	Matrix<TItem, TSizeX, TSizeY> result;

	matrix_identity(result)

	return result;
}

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
void matrix_zero(
	Matrix<TItem, TSizeX, TSizeY>& matrix)
{
	memset(matrix.Data, 0, (TSizeX * TSizeY * sizeof(TItem)));
}

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
inline Matrix<TItem, TSizeX, TSizeY> matrix_zero()
{
	Matrix<TItem, TSizeX, TSizeY> result;

	matrix_zero(result);

	return result;
}