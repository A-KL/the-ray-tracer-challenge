#include <SDL.h>

#include "SDLCanvas.h"
#include "SDLWindowRenderer.h"

SDLWindowRenderer::SDLWindowRenderer(const char* title, int width, int height, int bpp)
	: SDLWindowRenderer(SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0),
		bpp)
{ }

SDLWindowRenderer::SDLWindowRenderer(SDL_Window* window, int bpp)
	: SDLCanvas(window, bpp), _window(window)
{ }

SDLWindowRenderer::~SDLWindowRenderer()
{
	SDL_DestroyWindow(_window);
}