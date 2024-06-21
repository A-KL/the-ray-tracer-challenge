#include <Arduino.h>
#include <M5GFX.h>

#include "M5StackCanvas.h"

M5GFX display;
M5StackCanvas canvas(display);

//#include <M5UnitOLED.h>
//M5UnitOLED display; // default setting
//M5UnitOLED display ( 21, 22, 400000 ); // SDA, SCL, FREQ

//#include <M5UnitLCD.h>
//M5UnitLCD display;  // default setting
//M5UnitLCD display  ( 21, 22, 400000 ); // SDA, SCL, FREQ

void Run(Canvas& canvas);

void setup(void)
{
    canvas.Init();
	display.waitDisplay();
    
    Run(canvas);
}

void loop(void)
{
    delay(10);
}