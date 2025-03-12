#pragma once

class SDLCanvas :
	public Canvas
{
public:
	SDLCanvas(SDL_Window* window, int bpp)
	{
		SDL_GetWindowSize(window, &_w, &_h);

		_bpp = bpp;

		_sdl = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	SDLCanvas(SDL_Window* window)
		: SDLCanvas(window, 32)
	{ }

	void DrawPoint(int x, int y, const Color3D& color)
	{
		SDL_SetRenderDrawColor(_sdl, color.RToByte(), color.GToByte(), color.BToByte(), 0);

		SDL_RenderDrawPoint(_sdl, x, y);
	}

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color)
	{
		SDL_SetRenderDrawColor(_sdl, color.RToByte(), color.GToByte(), color.BToByte(), 0);

		SDL_RenderDrawLine(_sdl, x0, y0, x1, y1);
	}

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

	void Clear(const Color3D& color)
	{
		SDL_SetRenderDrawColor(_sdl, color.RToByte(), color.GToByte(), color.BToByte(), 0);

		SDL_RenderClear(_sdl);
	}

	void Clear()
	{
		Clear(_background);
	}

	void Update(bool force = false)
	{
		#ifdef __APPLE__
		if (force)
			SDL_RenderPresent(_sdl);
		#else
			SDL_RenderPresent(_sdl);
		#endif
	}

	~SDLCanvas()
	{
		SDL_DestroyRenderer(_sdl);
	}

private:
	int _w, _h, _bpp;

	SDL_Renderer* _sdl;

	Color3D _background = Color3D::Black;
};

