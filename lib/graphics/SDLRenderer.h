#pragma once

class Renderer
{
public:
	virtual void DrawPoint(int x, int y, int color) = 0;

	virtual void DrawLine(int x0, int y0, int x1, int y1, int color) = 0;

	virtual unsigned int Height() = 0;

	virtual unsigned int Witdth() = 0;

	virtual unsigned int Bpp() = 0;

	virtual void Clear() = 0;

	virtual void Update() = 0;
};

class SDLRenderer :
	public Renderer
{
public:
	SDLRenderer(SDL_Window*, int);

	SDLRenderer(SDL_Window*);

	//const char& BeginDrawing();

	void DrawPoint(int x, int y, int color);

	void DrawLine(int x0, int y0, int x1, int y1, int color);

	unsigned int Height();

	unsigned int Witdth();

	unsigned int Bpp();

	void Clear();

	void Update();

	virtual ~SDLRenderer();

private:
	unsigned int _w, _h, _bpp;

	SDL_Renderer* _sdl;

	const Color<Rgba> _background = Rgba::Black;
};

