#define SDL_MAIN_HANDLED

#include <iostream>
#include <list>

#include <SDL.h>

#include "renderer/SDLRenderer.h"
#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"

#include "ray-tracer/Matrix.h"

using namespace std;


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

    Matrix<3, 3, int> mux2 = mux * Matrix<3, 3, int>::Identity;

    int tuple[3] = { 2, 2, 2 };

    int* mul = m0 * tuple;

    int i0 = mul[0];
    int i1 = mul[1];
    int i2 = mul[2];

    Matrix<2, 2, int> sub = m0.Sub(2, 2);

    int d0 = sub.Determinant();

    int d = sub.Minor(2,2);

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