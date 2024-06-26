#pragma once

#include "../lib/Core/Canvas.h"

class SDLCanvas :
	public Canvas
{
public:
	SDLCanvas(SDL_Window*, int);

	SDLCanvas(SDL_Window*);

	void DrawPoint(int x, int y, const Color3D& color);

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color);

	inline int Height() const
	{
		return _h;
	}

	inline int Width() const
	{
		return _w;
	}

	inline unsigned int Bpp() const
	{
		return _bpp;
	}

	void Clear(const Color3D& color);

	void Clear();

	void Update();

	virtual ~SDLCanvas();

private:
	int _w, _h, _bpp;

	SDL_Renderer* _sdl;

	Color3D _background = Color3D::Black;
};

