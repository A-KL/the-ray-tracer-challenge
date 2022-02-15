#pragma once

#include "../ray-tracer-core/Color3D.h"

class Canvas
{
public:
	virtual void DrawPoint(int x, int y, const Color3D& color) = 0;

	virtual void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color) = 0;

	virtual int Height() = 0;

	virtual int Witdth() = 0;

	virtual unsigned int Bpp() = 0;

	virtual void Clear(const Color3D& color) = 0;

	virtual void Clear() = 0;

	virtual void Update() = 0;
};