#include <M5GFX.h>
#include "Color3D.h"
#include "M5StackCanvas.h"

M5StackCanvas::M5StackCanvas(M5GFX& display, int bpp)
{
	_bpp = bpp;
	_display = &display;

	_w = display.width();
	_h = display.height();
}

void M5StackCanvas::Init(const Color3D& color)
{
  _display->init();
  _display->startWrite();
  _display->fillScreen(color);

  if (_display->isEPD())
  {
    _display->setEpdMode(epd_mode_t::epd_fastest);
  }
  if (_display->width() < _display->height())
  {
    _display->setRotation(_display->getRotation() ^ 1);
  }
}

void M5StackCanvas::DrawPoint(int x, int y, int color)
{
	_display->drawPixel(x, y, color);
}

void M5StackCanvas::DrawLine(int x0, int y0, int x1, int y1, int color)
{
	_display->drawLine(x0, y0, x1, y1, color);
}

void M5StackCanvas::Clear(const Color3D& color)
{
	_display->fillScreen(color);
}

void M5StackCanvas::Clear(const Color3D& color)
{
  Clear(_background);
}

void M5StackCanvas::Update()
{
	_display->display();
}

M5StackCanvas::~M5StackCanvas()
{ }
