#include <M5GFX.h>
#include "Color3D.h"
#include "M5StackCanvas.h"

void M5StackCanvas::Init(const Color3D& color)
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

void M5StackCanvas::DrawPoint(int x, int y, const Color3D& color)
{
	_display->drawPixel(x, y, (unsigned short)color);
}

void M5StackCanvas::DrawLine(int x0, int y0, int x1, int y1, const Color3D& color)
{
	_display->drawLine(x0, y0, x1, y1, (unsigned short)color);
}

void M5StackCanvas::Clear(const Color3D& color)
{
	_display->fillScreen((unsigned short)color);
}

void M5StackCanvas::Clear()
{
  Clear(_background);
}

void M5StackCanvas::Update()
{
	_display->display();
}

M5StackCanvas::~M5StackCanvas()
{ }
