#pragma once

#include "Canvas.h"

class M5StackCanvas :
	public Canvas
{
public:
	M5StackCanvas(M5GFX&, int);

	void Init(const Color3D& color);

	void DrawPoint(int x, int y, int color);

	void DrawLine(int x0, int y0, int x1, int y1, int color);

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

	void Clear(const Color3D& color);

	void Clear();

	void Update();

	virtual ~M5StackCanvas();

private:
	int _w, _h, _bpp;

	M5GFX* _display;

	const Color3D _background = Color3D::Black;
};

