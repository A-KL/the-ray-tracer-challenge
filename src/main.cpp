#define SDL_MAIN_HANDLED

#include <iostream>
#include <list>

#include <SDL.h>

#include "renderer/ColorRgba.h"
#include "renderer/SDLRenderer.h"

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"

using namespace std;

int main()
{
    Point3D start(0, 1, 0);
    Vector3D velocity(1, 1.8, 0);

    Projectile proj(start, velocity.Normalize() * 11.25);
    Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));


    // init SDL
    SDL_Init(SDL_INIT_VIDEO);

    const int h = 550;
    const int w = 900;

    ColorRgba<int> background(255, 255, 255, 255);

   // int bpp = background.Bpp();


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

        renderer.DrawPoint(p.X(), h - p.Y(), 0);

        // render window
        renderer.Update();

        proj = proj.Tick(env);

    } while (event.type != SDL_QUIT);

    // cleanup SDL

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}