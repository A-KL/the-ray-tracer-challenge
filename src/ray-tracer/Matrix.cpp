#pragma once

#include "Matrix.h"

//template<class TItem, int TSizeX, int TSizeY>
//Matrix<TItem, TSizeX, TSizeY>::Matrix()
//{ 
//	matrix_identity(this);
//}


template<class TItem, int TSizeX, int TSizeY>
const TItem& Matrix<TItem, TSizeX, TSizeY>::operator [](int index) const
{
	return Data[index];
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

//template<class TItem, int TSizeX, int TSizeY>
//const TItem Matrix<TItem, TSizeX, TSizeY>::Determinant()
//{
//	TItem determinant = 0;
//
//	for (int col = 0; col < (TSizeY - 1); col++)
//	{
//		determinant += Data[0][col] * Cofactor(0, col);
//	}
//
//	return determinant;
//}