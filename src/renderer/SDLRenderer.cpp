#include <SDL.h>

#include "Color.h"

#include "SDLRenderer.h"


SDLRenderer::SDLRenderer(SDL_Window* window, int bpp)
{
	SDL_GetWindowSize(window, &_w, &_h);

	_bpp = bpp;

	_sdl = SDL_CreateRenderer(window, -1, 0);
}

SDLRenderer::SDLRenderer(SDL_Window* window) 
	: SDLRenderer(window, Color::Bpp32)
{ }

void SDLRenderer::DrawPoint(int x, int y, int color)
{
	SDL_SetRenderDrawColor(_sdl, 0, 255, 0, 255);

	SDL_RenderDrawPointF(_sdl, x, y);
}

void SDLRenderer::DrawLine(int x0, int y0, int x1, int y1, int color)
{
	SDL_SetRenderDrawColor(_sdl, 256, 0, 0, 255);

	SDL_RenderDrawLine(_sdl, x0, y0, x1, y1);
}


int SDLRenderer::Height()
{
	return _h;
}

int SDLRenderer::Witdth()
{
	return _w;
}

int SDLRenderer::Bpp()
{
	return _bpp;
}

void SDLRenderer::Clear()
{
	SDL_SetRenderDrawColor(_sdl, 0, 0, 0, 255);

	SDL_RenderClear(_sdl);
}

void SDLRenderer::Update()
{
	SDL_RenderPresent(_sdl);
}

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(_sdl);
}
