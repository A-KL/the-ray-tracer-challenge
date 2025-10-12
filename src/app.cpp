#ifdef LGFX_AUTODETECT
#include <LovyanGFX.h>
#include <LGFX_AUTODETECT.hpp>
#else
#include <TFT_eSPI.h>
#include <TFT_eSPI_T_HMI_Display.h>
using LGFX = TFT_eSPI_T_HMI_Display;
#endif

#include "Canvas.h"
#include "LovyanGFXCanvas.h"
#include "examples.h"
#include "../test/tests.h"

#if defined ( SDL_h_ )
static LGFX lcd ( 320, 240, 2 );
#else
static LGFX lcd;
#endif

LovyanGFXCanvas canvas(lcd);

void setup(void)
{
  lcd.init();
  lcd.fillScreen(TFT_BLUE);
}

void loop(void)
{
#ifdef _DEBUG
	run_tests();
#endif
	//run_projectile_demo(canvas);
	//run_clock_demo(canvas);
	//run_shadow_demo(canvas);
	//run_light_demo(canvas);

	//run_scene_demo(canvas);
	//run_scene_plane_demo(canvas);
	//run_scene_patterns_demo(canvas);
	run_fresnel_demo(canvas);

	//run_glass_sphere_demo(canvas);
    //lcd.fillCircle(rand()%lcd.width(), rand()%lcd.height(), 16, rand());
}

#if defined ( ESP_PLATFORM ) && !defined ( ARDUINO )
extern "C" {

int app_main(int, char**)
{
    setup();
    for (;;) {
      loop();
    }
    return 0;
}

}
#endif