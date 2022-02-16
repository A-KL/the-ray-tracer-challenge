#pragma once

#include "Canvas.h"

class M5StackCanvas :
	public Canvas
{
public:
	M5StackCanvas(M5GFX&);

	void Init(const Color3D& color);

	void DrawPoint(int x, int y, const Color3D& color);

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color);

	inline int Height()
	{
		return _h;
	}

	inline int Witdth()
	{
		return _w;
	}

	void Clear(const Color3D& color);

	void Clear();

	void Update();

	virtual ~M5StackCanvas();

private:
	int _w, _h;

	M5GFX* _display;

	const Color3D _background = Color3D::Black;
};

