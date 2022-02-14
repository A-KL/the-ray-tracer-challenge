#pragma once

class Canvas
{
public:
	virtual void DrawPoint(int x, int y, unsigned int color) = 0;

	virtual void DrawLine(int x0, int y0, int x1, int y1, unsigned int color) = 0;

	virtual int Height() = 0;

	virtual int Witdth() = 0;

	virtual unsigned int Bpp() = 0;

	virtual void Clear(unsigned int color = 0) = 0;

	virtual void Update() = 0;
};