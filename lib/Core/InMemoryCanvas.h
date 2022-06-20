#pragma once

#include <math.h>

#include "Mathf.h"
#include "Color3D.h"
#include "Canvas.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"

#include "InMemoryCanvas.h"

template<unsigned TWidth, unsigned THeight>
class InMemoryCanvas : public Canvas
{
public:
	void DrawPoint(int x, int y, const Color3D& color)
	{
		_data[x + TWidth * y] = color;
	};

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color)
	{

	};

	inline int Height() const
	{
		return THeight;
	}

	inline int Witdth() const
	{
		return TWidth;
	}

	unsigned int Bpp() const
	{
		return 24;
	}

	void Clear(const Color3D& color)
	{ }

	void Clear()
	{ }

	void Update()
	{ }

	inline Color3D Get(int x, int y)
	{
		return _data[x + TWidth * y];
	}

private:
	Color3D _data[(THeight * TWidth)];
};