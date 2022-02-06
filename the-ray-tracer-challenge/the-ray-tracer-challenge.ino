
#include <M5GFX.h>
#include <list>
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Environment.h"
#include "Projectile.h"

// #include "Matrix.hpp"
// #include "MatrixOps.hpp"
// #include "MatrixTransform.hpp"

M5GFX display;

//#include <M5UnitOLED.h>
//M5UnitOLED display; // default setting
//M5UnitOLED display ( 21, 22, 400000 ); // SDA, SCL, FREQ

//#include <M5UnitLCD.h>
//M5UnitLCD display;  // default setting
//M5UnitLCD display  ( 21, 22, 400000 ); // SDA, SCL, FREQ

Point3D start(0, 1, 0);
Vector3D velocity(1, 1.8, 0);

Projectile proj(start, velocity.Normalize() * 6.25);
Environment env(Vector3D(0, -0.1, 0), Vector3D(-0.01, 0, 0));

void setup(void)
{ 
std::list<int> l = { 7, 5, 16, 8 };

  display.init();
  display.startWrite();
  display.fillScreen(TFT_BLACK);

  if (display.isEPD())
  {
    display.setEpdMode(epd_mode_t::epd_fastest);
  }
  if (display.width() < display.height())
  {
    display.setRotation(display.getRotation() ^ 1);
  }
}

void loop(void)
{ 
	Point3D p = proj.Position();

  display.waitDisplay();
  display.drawPixel(p.X(), display.height() - p.Y(), TFT_RED);

	proj = proj.Tick(env);

  display.display();

  delay(1);
}
