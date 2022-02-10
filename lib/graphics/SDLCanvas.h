#pragma once

class Canvas
{
public:
	virtual void DrawPoint(int x, int y, unsigned int color) = 0;

	virtual void DrawLine(int x0, int y0, int x1, int y1, unsigned int color) = 0;

	virtual int Height() = 0;

	virtual int Witdth() = 0;

	virtual unsigned int Bpp() = 0;

	virtual void Clear() = 0;

	virtual void Clear(unsigned int color) = 0;

	virtual void Update() = 0;
};

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

	void Clear();

	void Clear(unsigned int color);

	void Update();

	virtual ~SDLCanvas();

private:
	int _w, _h, _bpp;

	SDL_Renderer* _sdl;

	const Color<Rgba> _background = Rgba::Black;
};

