#define SDL_MAIN_HANDLED

#include <iostream>
#include <list>

#include <SDL.h>
#include "renderer/SDLRenderer.h"

#include "ray-tracer/Vector3D.h"
#include "ray-tracer/Point3D.h"
#include "ray-tracer/Projectile.h"

using namespace std;

struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
};

int main()
{
    Projectile proj(Point3D(0, 1, 0), Vector3D(1, 1, 0).Normalize());

    Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));



    Point3D p0(1, 1, 0);

    Vector3D v1(1,0,0);

    Point3D p1 = p0 + v1;

    cout << p1;
    cout << v1;

    // init SDL

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 line drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDLRenderer renderer(640, 480, 24, window);

    // variables

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    bool drawing = false;

    std::list<Line> lines;

    bool quit = false;
    SDL_Event event;

    // handle events

    while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                x1 = event.motion.x;
                y1 = event.motion.y;
                x2 = event.motion.x;
                y2 = event.motion.y;
                drawing = true;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                drawing = false;
                Line line = { x1, y1, x2, y2 };
                lines.push_back(line);
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            if (drawing)
            {
                x2 = event.motion.x;
                y2 = event.motion.y;
            }
            break;
        }

        // clear window
        renderer.Clear();

        // draw stored lines
        for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
        {
            Line line = *i;
            renderer.DrawLine(line.x1, line.y1, line.x2, line.y2, 0);
        }

        // render window
        renderer.Update();
    }

    // cleanup SDL

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}