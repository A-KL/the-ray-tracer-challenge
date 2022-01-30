#include "Color.h"
#include <SDL.h>
#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(SDL_Window* window, int bpp)
{
	SDL_GetWindowSize(window, &_w, &_h);

	_bpp = bpp;

	_sdl = SDL_CreateRenderer(window, -1, 0);
}

SDLRenderer::SDLRenderer(SDL_Window* window)
	: SDLRenderer(window, 32)
{ }

void SDLRenderer::DrawPoint(int x, int y, int color)
{
	Color<Rgba> rgba = Rgba::Black;

	rgba.Raw = color;

	SDL_SetRenderDrawColor(_sdl, rgba.Color.R, rgba.Color.G, rgba.Color.B, rgba.Color.A);

	SDL_RenderDrawPointF(_sdl, x, y);
}

void SDLRenderer::DrawLine(int x0, int y0, int x1, int y1, int color)
{
	Color<Rgba> rgba = Rgba::Black;

	rgba.Raw = color;

	SDL_SetRenderDrawColor(_sdl, rgba.Color.R, rgba.Color.G, rgba.Color.B, rgba.Color.A);

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
	SDL_SetRenderDrawColor(_sdl, _background.Color.R, _background.Color.G, _background.Color.B, _background.Color.A);

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
