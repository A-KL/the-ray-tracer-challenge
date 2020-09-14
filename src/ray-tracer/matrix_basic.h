//#pragma once
//
//#include "Matrix.h"
//
//template<class TItem, int TSizeX, int TSizeY>
//void matrix_remove(
//	const Matrix<TItem, TSizeX, TSizeY>& matrix,
//	int row, int col,
//	Matrix<TItem, TSizeX - 1, TSizeX - 1>& result)
//{
//	int x, y, x1, y1;
//
//	for (x = 0, x1 = 0; x < TSizeX; x++)
//	{
//		if (x == row)
//			continue;
//
//		for (y = 0, y1 = 0; y < TSizeY; y++)
//		{
//			if (y == col)
//				continue;
//
//			result.Data[x1][y1] = matrix.Data[x][y];
//			y1++;
//		}
//		x1++;
//	}
//}
//
//template<class TItem, int TSizeX, int TSizeY>
//void matrix_identity(
//	Matrix<TItem, TSizeX, TSizeY>& matrix)
//{
//	int x, y;
//
//	for (x = 0; x < TSizeX; x++)
//	{
//		for (y = 0; y < TSizeY; y++)
//		{
//			matrix.Data[x][y] = (x == y);
//		}
//	}
//}
//
//template<class TItem, int TSizeX, int TSizeY>
//void matrix_inverse(
//	Matrix<TItem, TSizeX, TSizeY>& matrix)
//{
//	//???
//}
//
//template<class TItem, int TSizeX, int TSizeY>
//void matrix_mul(
//	const Matrix<TItem, TSizeX, TSizeY>& matrix1,
//	const Matrix<TItem, TSizeX, TSizeY>& matrix2,
//	Matrix<TItem, TSizeX, TSizeY>& result)
//{
//	int x, y, j;
//
//	for (x = 0; x < TSizeX; x++)
//	{
//		for (y = 0; y < TSizeY; y++)
//		{
//			result.Data[x][y] = 0;
//
//			for (j = 0; j < TSizeY; j++)
//			{
//				result.Data[x][y] += matrix1.Data[x][j] * matrix2.Data[j][y];
//			}
//		}
//	}
//}
//
//template<class TItem>
//void matrix_mul(
//	const Matrix<TItem, 3, 3>& matrix,
//	const Vector3D& other,
//	Vector3D& result)
//{
//	result.X = matrix.Data[0][0] * other.X + matrix.Data[1][0] * other.Y + matrix.Data[2][0] * other.Z;
//	result.Y = matrix.Data[0][1] * other.X + matrix.Data[1][1] * other.Y + matrix.Data[2][1] * other.Z;
//	result.Z = matrix.Data[0][2] * other.X + matrix.Data[1][2] * other.Y + matrix.Data[2][2] * other.Z;
//}
//
//template<class TItem, int TSize>
//void matrix_mul(
//	const Matrix<TItem, TSize, TSize>& matrix,
//	const TItem other[],
//	TItem result[])
//{
//	int x, y, index;
//
//	for (index = 0; index < TSize; index++)
//	{
//		result[index] = 0;
//
//		for (x = 0; x < TSize; x++)
//		{
//			result[index] += (other[x] * matrix.Data[x][index]);
//		}
//	}
//}
//
//template<class TItem, int TSizeX, int TSizeY>
//void matrix_transpose(
//	const Matrix<TItem, TSizeX, TSizeY>& matrix,
//	Matrix<TItem, TSizeX, TSizeY>& result)
//{
//	int x, y;
//
//	for (x = 0; x < TSizeX; x++)
//	{
//		for (y = 0; y < TSizeY; y++)
//		{
//			result.Data[y][x] = matrix.Data[y][x];
//		}
//	}
//}
//
//template<class TItem>
//void matrix_translate(
//	TItem x,
//	TItem y,
//	TItem z,
//	Matrix<TItem, 4, 4>& result)
//{
//	result.Data[3][0] = x;
//	result.Data[3][1] = y;
//	result.Data[3][2] = z;
//}
//
//template<class TItem>
//void matrix_scaling(
//	TItem x,
//	TItem y,
//	TItem z,
//	Matrix<TItem, 4, 4>& result)
//{
//	result.Data[3][0] = x;
//	result.Data[3][1] = y;
//	result.Data[3][2] = z;
//}