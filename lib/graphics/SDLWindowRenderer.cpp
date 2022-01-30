#include "Color.h"
#include <SDL.h>
#include "SDLRenderer.h"
#include "SDLWindowRenderer.h"

SDLWindowRenderer::SDLWindowRenderer(unsigned int width, unsigned int height, int bpp)
	: SDLWindowRenderer(SDL_CreateWindow(
		"The Ray Tracer Challenge",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0),
		bpp)
{ }

SDLWindowRenderer::SDLWindowRenderer(SDL_Window* window, int bpp)
	: SDLRenderer(window, bpp), _window(window)
{ }

SDLWindowRenderer::~SDLWindowRenderer()
{
	SDL_DestroyWindow(_window);
}