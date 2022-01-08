#pragma once

template<class TItem, int TSizeX, int TSizeY>
struct Matrix
{
	TItem Data[TSizeX][TSizeY];

	const TItem& operator[](int index) const
	{
		return Data[index];
	}

	Matrix<TItem, TSizeX, TSizeY>& operator+=(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		for (int i = 0; i < TSizeX * TSizeY; i++)
		{
			this->Data[i] += other.Data[i];
		}
		return *this;
	}

	Matrix<TItem, TSizeX, TSizeY>& operator-=(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		for (int i = 0; i < TSizeX * TSizeY; i++)
		{
			this->Data[i][0] -= other.Data[i][0];
		}
		return *this;
	}

	bool operator==(const Matrix<TItem, TSizeX, TSizeY>& other)
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

	bool operator!=(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		return !(other == this);
	}
};

typedef Matrix<int, 2, 2> Matrix2;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<double, 2, 2> Matrix2d;

typedef Matrix<int, 3, 3> Matrix3;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<double, 3, 3> Matrix3d;

typedef Matrix<int, 4, 4> Matrix4;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 4, 4> Matrix4d;