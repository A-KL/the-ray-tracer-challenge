#pragma once

template<class TItem, int TSizeX, int TSizeY>
struct Matrix
{
public:
    TItem Data[TSizeX][TSizeY];

    const static Matrix<TItem, TSizeX, TSizeY>& Identity;

    inline const TItem& operator[](int Index) const
    {
        return Data[Index];
    }

    inline Matrix<TItem, TSizeX, TSizeY>& operator+=(const Matrix<TItem, TSizeX, TSizeY>& other)
    {
        for (int i = 0; i < TSizeX * TSizeY; i++)
        {
            this->Data[i] += other.Data[i];
        }
        return *this;
    }

    inline Matrix<TItem, TSizeX, TSizeY>& operator-=(const Matrix<TItem, TSizeX, TSizeY>& other)
    {
        for (int i = 0; i < TSizeX * TSizeY; i++)
        {
            this->Data[i][0] -= other.Data[i][0];
        }
        return *this;
    }

    inline bool operator==(const Matrix<TItem, TSizeX, TSizeY>& other)
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

    inline bool  operator!=(const Matrix<TItem, TSizeX, TSizeY>& other)
    {
        return !(other == this);
    }

    //const int Determinant()
    //{
    //    return Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
    //}

    //const int Minor(int row, int col)
    //{        
    //    Matrix<Ty - 1, Tx - 1, T> result = Sub(row, col);

    //    return result.Determinant();
    //}


private:
    const static Matrix<TItem, TSizeX, TSizeY>& GetIdentity()
    {
        Matrix<TItem, TSizeX, TSizeY> result;
        int x, y;

        for (x = 0; x < TSizeX; x++)
        {
            for (y = 0; y < TSizeY; y++)
            {
                result.Data[x][y] = (x == y);
            }
        }

        return result;
    }
};

template<class TItem, int TSizeX, int TSizeY>
const Matrix<TItem, TSizeX, TSizeY>& Matrix<TItem, TSizeX, TSizeY>::Identity = Matrix<TItem, TSizeX, TSizeY>::GetIdentity();

template<class TItem, int TSizeX, int TSizeY>
void matrix_mul(
    const Matrix<TItem, TSizeX, TSizeY>& matrix1,
    const Matrix<TItem, TSizeX, TSizeY>& matrix2,
          Matrix<TItem, TSizeX, TSizeY>& result)
{
    int x, y, j;

    for (x = 0; x < TSizeX; x++)
    {
        for (y = 0; y < TSizeY; y++)
        {
            result.Data[x][y] = 0;

            for (j = 0; j < TSizeY; j++)
            {
                result.Data[x][y] += matrix1.Data[x][j] * matrix2.Data[j][y];
            }
        }
    }
}

template<class TItem>
void matrix_mul(
    const Matrix<TItem, 3, 3>& matrix,
    const Vector3D& other,
          Vector3D& result)
{
    result.X = matrix.Data[0][0] * other.X + matrix.Data[1][0] * other.Y + matrix.Data[2][0] * other.Z;
    result.Y = matrix.Data[0][1] * other.X + matrix.Data[1][1] * other.Y + matrix.Data[2][1] * other.Z;
    result.Z = matrix.Data[0][2] * other.X + matrix.Data[1][2] * other.Y + matrix.Data[2][2] * other.Z;
}

template<class TItem, int TSize>
void matrix_mul(
    const Matrix<TItem, TSize, TSize>& matrix,
    const TItem other[],
          TItem result[])
{
    int x, y, index;

    for (index = 0; index < TSize; index++)
    {
        result[index] = 0;

        for (x = 0; x < TSize; x++)
        {
            result[index] += other[x] * matrix.Data[x][index];
        }
    }
}

template<class TItem, int TSizeX, int TSizeY>
void matrix_transpose(
    const Matrix<TItem, TSizeX, TSizeY>& matrix,
          Matrix<TItem, TSizeX, TSizeY>& result)
{
    int x, y;

    for (x = 0; x < TSizeX; x++)
    {
        for (y = 0; y < TSizeY; y++)
        {
            result.Data[y][x] = matrix.Data[y][x];
        }
    }
}

template<class TItem, int TSizeX, int TSizeY, int TSubSizeX, int TSubSizeY>
void matrix_sub(
    const Matrix<TItem, TSizeX, TSizeY>& matrix,
          Matrix<TItem, TSubSizeX, TSubSizeY>& result)
{
    int x, y, x1, y1;

    for (x = 0, x1 = 0; x < TSizeX; x++)
    {
        if (x == TSubSizeY)
            continue;

        for (y = 0, y1 = 0; y < TSizeY; y++)
        {
            if (y == TSubSizeX)
                continue;

            result.Data[x1][y1] = matrix.Data[x][y];
            y1++;
        }
        x1++;
    }
}
