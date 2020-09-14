#pragma once

template<class TItem, int TSizeX, int TSizeY>
struct Matrix
{
	TItem Data[TSizeX][TSizeY];

	inline const TItem& operator[](int Index) const;

	Matrix<TItem, TSizeX, TSizeY>& operator+=(const Matrix<TItem, TSizeX, TSizeY>& other);

	Matrix<TItem, TSizeX, TSizeY>& operator-=(const Matrix<TItem, TSizeX, TSizeY>& other);

	bool operator==(const Matrix<TItem, TSizeX, TSizeY>& other);

	bool operator!=(const Matrix<TItem, TSizeX, TSizeY>& other);

	inline const TItem Determinant();

	inline const TItem Minor(int row, int col);

	inline const TItem Cofactor(int row, int col);
};

template<class TItem>
struct Matrix2 :  Matrix<TItem, 2, 2>
{ };

template<class TItem>
struct Matrix3 : Matrix<TItem, 3, 3>
{ };

template<class TItem>
struct Matrix4 : Matrix<TItem, 4, 4>
{ };