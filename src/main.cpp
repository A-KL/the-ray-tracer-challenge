#define SDL_MAIN_HANDLED

#include <iostream>
#include <list>

#include <SDL.h>

#include "renderer/SDLRenderer.h"

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"

using namespace std;

template<int Tx, int Ty, class T>
union Matrix
{
    T Data[Tx][Ty];

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

    bool operator!=(const Matrix<Tx, Ty, T>& other)
    {
        return !(other == this);
    }

    const Matrix<Ty, Tx, T>& Transpose(const Matrix<Tx, Ty, T>& other)
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

    const Matrix<Tx, Ty, T>& operator*(const Matrix<Tx, Ty, T>& other)
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

    //T[Tx] operator*(const T other[Ty])
    //{
    //    T result[Tx];

    //    int x, y, j;

    //    for (x = 0; x < Tx; x++)
    //    {
    //        result[x] = 0;

    //        for (y = 0; y < Ty; y++)
    //        {
    //            result[x] += Data[x][y] * other[y];
    //        }
    //    }

    //    return &result;
    //}
};


int main()
{
    Point3D start(0, 1, 0);
    Vector3D velocity(1, 1.8, 0);

    Projectile proj(start, velocity.Normalize() * 11.25);
    Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

    Color<Rgba> c = Rgba::Blue;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);

    const int h = 550;
    const int w = 900;

    Matrix<3, 3, int> m0 = { 
        1,2,3, 
        4,5,6, 
        7,8,9
    };

    Matrix<3, 3, int> m1 = { 
        1,2,3,
        4,5,6, 
        7,8,9 
    };

    bool same = m0 == m1;

    Matrix<3, 3, int> mux = m0 * m1;

    int tuple[3] = { 2, 2, 2 };

   // int mul[3] = { 0,0,0 };

   // auto mul = m0 * tuple;


    SDL_Window* window = SDL_CreateWindow(
        "The Ray Tracer Challenge", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        w, h, 0);

    SDLRenderer renderer(window);
    SDL_Event event;

    renderer.Clear();

    do 
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        Point3D p = proj.Position();

        renderer.DrawPoint(p.X(), h - p.Y(), c.Raw);

        // render window
        renderer.Update();

        proj = proj.Tick(env);

    } while (event.type != SDL_QUIT);

    // cleanup SDL

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}