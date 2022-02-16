#pragma once

#include "Canvas.h"

class M5StackCanvas :
	public Canvas
{
public:
	M5StackCanvas(M5GFX& display) :
		_display(&display)
	{}

	void Init(const Color3D& color = Color3D::Black);

	void DrawPoint(int x, int y, const Color3D& color);

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color);

	inline int Height()
	{
		return _display->height();
	}

	inline int Witdth()
	{
		return _display->width();
	}

	void Clear(const Color3D& color);

	void Clear();

	void Update();

	virtual ~M5StackCanvas();

private:
	M5GFX* _display;

	const Color3D _background = Color3D::Black;
};

