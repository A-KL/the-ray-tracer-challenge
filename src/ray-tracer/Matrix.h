#pragma once

template<int Tx, int Ty, class T>
union Matrix
{
public:
    T Data[Tx][Ty];

    const static Matrix<Tx, Ty, T>& Identity;

    bool operator==(const Matrix<Tx, Ty, T>& other)
    {
        int x, y;

        for (x = 0; x < Tx; x++)
        {
            for (y = 0; y < Ty; y++)
            {
                if (Data[x][y] != other.Data[x][y])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool  operator!=(const Matrix<Tx, Ty, T>& other)
    {
        return !(other == this);
    }

    T* operator*(const T other[Ty])
    {
        T result[Tx];

        int x, y, j;

        for (x = 0; x < Tx; x++)
        {
            result[x] = 0;

            for (y = 0; y < Ty; y++)
            {
                result[x] += Data[x][y] * other[y];
            }
        }

        return result;
    }

    const  Matrix<Tx, Ty, T>& operator*(const Matrix<Tx, Ty, T>& other)
    {
        Matrix<Tx, Ty, T> result;
        int x, y, j;

        for (x = 0; x < Tx; x++)
        {
            for (y = 0; y < Ty; y++)
            {
                result.Data[x][y] = 0;

                for (j = 0; j < Ty; j++)
                {
                    result.Data[x][y] += Data[x][j] * other.Data[j][y];
                }
            }
        }

        return result;
    }

    const  Matrix<Ty, Tx, T>& Transpose(const Matrix<Tx, Ty, T>& other)
    {
        Matrix<Ty, Tx, T> result;

        for (x = 0; x < Tx; x++)
        {
            for (y = 0; y < Ty; y++)
            {
                T tmp = Data[x][y];

                Data[x][y] = Data[y][x];

                Data[y][x] = tmp;
            }
        }

        return result;
    }

    const  Matrix<Ty-1, Tx-1, T>& Matrix<Tx, Ty, T>::Sub(int row, int col)
    {
        Matrix<Ty-1, Tx-1, T> result;
        int x, y, x1, y1;

        for (x = 0, x1 = 0; x < Tx; x++)
        {
            if (x == col)
                continue;
            
            for (y = 0, y1 = 0; y < Ty; y++)
            {
                if (y == row)
                    continue;

                result.Data[x1][y1] = Data[x][y];

                y1++;
            }
            

            x1++;
        }

        return result;
    }

    const int Determinant()
    {
        return Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
    }

    const int Minor(int row, int col)
    {        
        Matrix<Ty - 1, Tx - 1, T> result = Sub(row, col);

        return result.Determinant();
    }


private:
    const static Matrix<Tx, Ty, T>& GetIdentity()
    {
        Matrix<Tx, Ty, T> result;
        int x, y;

        for (x = 0; x < Tx; x++)
        {
            for (y = 0; y < Ty; y++)
            {
                result.Data[x][y] = (x == y);
            }
        }

        return result;
    }
};

template<int Tx, int Ty, class T>
const Matrix<Tx, Ty, T>& Matrix<Tx, Ty, T>::Identity = Matrix<Tx, Ty, T>::GetIdentity();

