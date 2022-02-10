#include <SDL.h>
#include "Color.h"
#include "SDLCanvas.h"

SDLCanvas::SDLCanvas(SDL_Window* window, int bpp)
{
	SDL_GetWindowSize(window, &_w, &_h);

	_bpp = bpp;

	_sdl = SDL_CreateRenderer(window, -1, 0);
}

SDLCanvas::SDLCanvas(SDL_Window* window)
	: SDLCanvas(window, 32)
{ }

void SDLCanvas::DrawPoint(int x, int y, unsigned int color)
{
	SDL_SetRenderDrawColor(_sdl, (uint8_t)color, (uint8_t)(color >> 8), (uint8_t)(color >> 16), (uint8_t)(color >> 24));

	SDL_RenderDrawPointF(_sdl, x, y);
}

void SDLCanvas::DrawLine(int x0, int y0, int x1, int y1, unsigned int color)
{
	SDL_SetRenderDrawColor(_sdl, (uint8_t)color, (uint8_t)(color >> 8), (uint8_t)(color >> 16), (uint8_t)(color >> 24));

	SDL_RenderDrawLine(_sdl, x0, y0, x1, y1);
}

void SDLCanvas::Clear(unsigned int color)
{
	SDL_SetRenderDrawColor(_sdl, (uint8_t)color, (uint8_t)(color>>8), (uint8_t)(color >> 16), (uint8_t)(color >> 24));

	SDL_RenderClear(_sdl);
}

void SDLCanvas::Clear()
{
	Clear(_background.Raw);
}

void SDLCanvas::Update()
{
	SDL_RenderPresent(_sdl);
}

SDLCanvas::~SDLCanvas()
{
	SDL_DestroyRenderer(_sdl);
}
