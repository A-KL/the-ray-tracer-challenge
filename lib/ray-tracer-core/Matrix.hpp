#pragma once

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

	bool operator==(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		return memcmp(Data, other.Data, (TSizeX * TSizeY)) == 0;
	}

	bool operator!=(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		return !(*this == other);
	}

	Matrix<TItem, TSizeX, TSizeY> operator*(const Matrix<TItem, TSizeX, TSizeY>& other)
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_mul(*this, other, result);

		return result;
	}

	Primitive3D<TItem> operator*(const Primitive3D<TItem>& other)
	{
		TItem converted[4] { 0, 0, 0, 0 };
		TItem result[4] { 0, 0, 0, 0 };

		// TODO: optimize
		other.ToArray(converted);

		matrix_mul(*this, converted, result);

		return Primitive3D<TItem>(result);
	}

	Matrix<TItem, TSizeX - 1, TSizeY - 1> remove(int row, int col)
	{
		Matrix<TItem, TSizeX - 1, TSizeY - 1> result;

		matrix_remove(*this, row, col, result);

		return result;
	}

	inline TItem determinant()
	{
		return matrix_determinant(*this);
	}

	inline TItem minor(int row, int col)
	{
		return matrix_minor(*this, row, col);
	}

	inline TItem cofactor(int row, int col)
	{
		return matrix_cofactor(*this, row, col);
	}

	Matrix<TItem, TSizeX, TSizeY> inverse()
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_zero(result);
		matrix_inverse(*this, result);

		return result;
	}

	static Matrix<TItem, TSizeX, TSizeY> zero()
	{
		Matrix<TItem, TSizeX, TSizeY> result;

		matrix_zero(result);

		return result;
	}

	static Matrix<TItem, TSizeX, TSizeX> identity()
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

	static Matrix<TItem, 4, 4> Translate(TItem x, TItem y, TItem z)
	{
		Matrix<TItem, 4, 4> result;

		matrix_translate(x, y, z, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateX(double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_x(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateY(double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_y(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> RotateZ(double r)
	{
		Matrix<TItem, 4, 4> result;

		matrix_rotate_z(r, result);

		return result;
	}

	static Matrix<TItem, 4, 4> shearing(TItem xy,
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