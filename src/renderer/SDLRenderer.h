#pragma once
class SDLRenderer
{
public:
	SDLRenderer(int, int, int, SDL_Window*);

	//const char& BeginDrawing();

	void DrawPoint(int x, int y, int color);

	void DrawLine(int x0, int y0, int x1, int y1, int color);

	int Height();

	int Witdth();

	int Bpp();

	void Clear();

	void Update();

	virtual ~SDLRenderer();

private:
	int _w, _h, _bpp;

	SDL_Renderer* _sdl;
};

