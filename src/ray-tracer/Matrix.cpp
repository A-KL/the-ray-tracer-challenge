#pragma once

#include "Matrix.h"

template<class TItem, int TSizeX, int TSizeY>
const TItem& Matrix<TItem, TSizeX, TSizeY>::operator [](int Index) const
{
	return Data[Index];
}

template<class TItem, int TSizeX, int TSizeY>
Matrix<TItem, TSizeX, TSizeY>& Matrix<TItem, TSizeX, TSizeY>::operator+=(const Matrix<TItem, TSizeX, TSizeY>& other)
{
	for (int i = 0; i < TSizeX * TSizeY; i++)
	{
		this->Data[i] += other.Data[i];
	}
	return *this;
}

template<class TItem, int TSizeX, int TSizeY>
Matrix<TItem, TSizeX, TSizeY>& Matrix<TItem, TSizeX, TSizeY>::operator-=(const Matrix<TItem, TSizeX, TSizeY>& other)
{
	for (int i = 0; i < TSizeX * TSizeY; i++)
	{
		this->Data[i][0] -= other.Data[i][0];
	}
	return *this;
}

template<class TItem, int TSizeX, int TSizeY>
bool Matrix<TItem, TSizeX, TSizeY>::operator==(const Matrix<TItem, TSizeX, TSizeY>& other)
{
	int x;

	TItem* item0 = &Data[0][0];
	const TItem* item1 = &other.Data[0][0];

	for (x = 0; x < TSizeX * TSizeY; x++)
	{
		if (item1[x] != item1[x])
		{
			return false;
		}
	}

	return true;
}

template<class TItem, int TSizeX, int TSizeY>
bool Matrix<TItem, TSizeX, TSizeY>::operator!=(const Matrix<TItem, TSizeX, TSizeY>& other)
{
	return !(other == this);
}

template<class TItem, int TSizeX, int TSizeY>
const TItem Matrix<TItem, TSizeX, TSizeY>::Determinant()
{
	TItem determinant = 0;

	if (TSizeX == 2 && TSizeY == 2)
	{
		determinant = Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
	}
	else
	{
		for (int col = 0; col < (TSizeY - 1); ++col)
		{
			TItem d = Data[0][col];

			int minor = 10;// Minor(0, col);

			int cofactor = ((0 + col) % 2) ? -minor : minor; //Cofactor(0, col);

			determinant += d * cofactor;// *Cofactor(0, col);
		}
	}

	return determinant;
}

template<class TItem, int TSizeX, int TSizeY>
const TItem Matrix<TItem, TSizeX, TSizeY>::Minor(int row, int col)
{
	Matrix<TItem, TSizeX - 1, TSizeY - 1> result;

	matrix_remove(*this, row, col, result);

	return result.Determinant();
}

template<class TItem, int TSizeX, int TSizeY>
const TItem Matrix<TItem, TSizeX, TSizeY>::Cofactor(int row, int col)
{
	int minor = Minor(row, col);

	// if odd return -minor otherwise +minor
	return ((row + col) % 2) ? -minor : minor;
}