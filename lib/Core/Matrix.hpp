#pragma once

#include <cassert>

template<typename TItem, unsigned TSizeX, unsigned TSizeY>
struct Matrix
{
	TItem Data[TSizeX][TSizeY];

	const TItem& operator()(const unsigned row, const unsigned column)
	{
		assert((row < TSizeX) && (column < TSizeY));
		return Data[column][row];
	}

	const TItem& operator()(const unsigned row, const unsigned column) const
	{
		assert((row < TSizeX) && (column < TSizeY));
		return Data[column][row];
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

	bool operator==(const Matrix<TItem, TSizeX, TSizeY>& other) const
	{
		for (auto x = 0; x < TSizeX; x++)
		{
			for (auto y = 0; y < TSizeY; y++)
			{
				if (!Mathf<TItem>::Approximately(Data[x][y], other.Data[x][y]))
				{
					return false;
				}
			}
		}

		return true;
		//return memcmp(Data, other.Data, (TSizeX * TSizeY)) == 0;
	}

	bool operator!=(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		return !(*this == other);
	}

	Matrix<TItem, TSizeX, TSizeY> operator*(const Matrix<TItem, TSizeX, TSizeY>& other) const
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_mul(*this, other, result);

		return result;
	}

	Point3D operator*(const Point3D& other) const
	{
		TItem converted[4]{ 0, 0, 0, 0 };
		TItem result[4]{ 0, 0, 0, 0 };

		// TODO: optimize
		other.ToArray(converted);

		matrix_mul(*this, converted, result);

		return Point3D(result[0], result[1], result[2]);
	}

	Vector3D operator*(const Vector3D& other) const
	{
		TItem converted[4]{ 0, 0, 0, 0 };
		TItem result[4]{ 0, 0, 0, 0 };

		// TODO: optimize
		other.ToArray(converted);

		matrix_mul(*this, converted, result);

		return Vector3D(result[0], result[1], result[2]);
	}

	Primitive3D<TItem> operator*(const Primitive3D<TItem>& other) const
	{
		TItem converted[4]{ 0, 0, 0, 0 };
		TItem result[4]{ 0, 0, 0, 0 };

		// TODO: optimize
		other.ToArray(converted);

		matrix_mul(*this, converted, result);

		return Primitive3D<TItem>(result);
	}

	Matrix<TItem, TSizeX - 1, TSizeY - 1> Remove(int row, int col) const
	{
		Matrix<TItem, TSizeX - 1, TSizeY - 1> result;

		matrix_remove(*this, row, col, result);

		return result;
	}

	inline TItem Determinant() const
	{
		return matrix_determinant(*this);
	}

	inline TItem Minor(int row, int col)
	{
		return matrix_minor(*this, row, col);
	}

	inline TItem Cofactor(int row, int col) const
	{
		return matrix_cofactor(*this, row, col);
	}

	Matrix<TItem, TSizeX, TSizeY> Inverse() const
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_zero(result);
		assert(matrix_inverse(*this, result));

		return result;
	}

	Matrix<TItem, TSizeX, TSizeY> Transpose() const
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_zero(result);
		matrix_transpose(*this, result);

		return result;
	}

	static Matrix<TItem, TSizeX, TSizeY> Zero()
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_zero(result);

		return result;
	}

	static Matrix<TItem, TSizeX, TSizeX> Identity()
	{
		Matrix<TItem, TSizeX, TSizeX> result;

		matrix_zero(result);
		matrix_identity(result);

		return result;
	}

	static Matrix<TItem, 4, 4> Scale(TItem x, TItem y, TItem z)
	{
		Matrix<TItem, 4, 4> result;

		matrix_scale(x, y, z, result);

		return result;
	}

	static Matrix<TItem, 4, 4> Scale(TItem a)
	{
		Matrix<TItem, 4, 4> result;

		matrix_scale(a, a, a, result);

		return result;
	}

	static Matrix<TItem, 4, 4> Translate(const TItem x, const TItem y, const TItem z)
	{
		Matrix<TItem, 4, 4> result;

		matrix_translate(x, y, z, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateX(const double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_x(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateY(const double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_y(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateZ(const double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_z(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> Shearing(TItem xy,
		TItem xz,
		TItem yx,
		TItem yz,
		TItem zx,
		TItem zy)
	{
		Matrix<TItem, 4, 4> result;

		matrix_shearing(xy, xz, yx, yz, zx, zy, result);

		return result;
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

const Matrix2 matrix_identity_2
{
	1, 0,
	0, 1
};

const Matrix3 matrix_identity_3
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

const Matrix3d matrix_identity_3d
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

const Matrix4 matrix_identity_4
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

const Matrix4d matrix_identity_4d
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

const Matrix4d matrix_zero_4d
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};