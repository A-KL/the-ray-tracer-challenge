#pragma once

#include <M5GFX.h>

#include "../lib/Core/Color3D.h"
#include "../lib/Core/Canvas.h"

class M5StackCanvas :
	public Canvas
{
public:
	M5StackCanvas(M5GFX& display) :
		_display(&display)
	{ }

	void Init(const Color3D& color = Color3D::Black)
	{
		_display->init();
		_display->startWrite();
		_display->fillScreen((unsigned short)color);

		if (_display->isEPD())
		{
			_display->setEpdMode(epd_mode_t::epd_fastest);
		}
		if (_display->width() < _display->height())
		{
			_display->setRotation(_display->getRotation() ^ 1);
		}
	}

	void DrawPoint(int x, int y, const Color3D& color)
	{
		_display->drawPixel(x, y, (unsigned short)color);
	}

	void DrawLine(int x0, int y0, int x1, int y1, const Color3D& color)
	{
		_display->drawLine(x0, y0, x1, y1, (unsigned short)color);
	}

	inline int Height() const
	{
		return _display->height();
	}

	inline int Width() const
	{
		return _display->width();
	}

	inline unsigned int Bpp() const
	{
		return 24;
	}

	inline void Clear(const Color3D& color)
	{
		_display->fillScreen((unsigned short)color);
	}

	inline void Clear()
	{
		Clear(_background);
	}

	inline void Update(bool force = false)
	{
		_display->display();
	}

private:
	M5GFX* _display;

	const Color3D _background = Color3D::Black;
};

