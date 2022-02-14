#pragma once

#include "Canvas.h"

class SDLCanvas :
	public Canvas
{
public:
	SDLCanvas(SDL_Window*, int);

	SDLCanvas(SDL_Window*);

	void DrawPoint(int x, int y, unsigned int color);

	void DrawLine(int x0, int y0, int x1, int y1, unsigned int color);

	inline int Height()
	{
		return _h;
	}

	inline int Witdth()
	{
		return _w;
	}

	inline unsigned int Bpp()
	{
		return _bpp;
	}

	void Clear(unsigned int color = 0);

	void Update();

	virtual ~SDLCanvas();

private:
	int _w, _h, _bpp;

	SDL_Renderer* _sdl;

	const Color _background = Color::Black;
};

