#ifdef LGFX_AUTODETECT
	#include <LovyanGFX.h>
	#include <LGFX_AUTODETECT.hpp>
#elif LGFX_ESP32
	#include "LGFX_ESP32_LCD.hpp"
	#include <LGFX_TFT_eSPI.h>
#else
	#include <TFT_eSPI.h>
	#include <TFT_eSPI_GFX.h>
	using LGFX = TFT_eSPI_GFX;
#endif

#include "Canvas.h"
#include "LovyanGFXCanvas.h"
#include "examples.h"
#include "../test/tests.h"

#if defined ( SDL_h_ )
static LGFX lcd ( 600, 400, 2 );
#else
static LGFX lcd;
#endif

LovyanGFXCanvas canvas(lcd);

void setup(void)
{
	canvas.Init(TFT_BLUE);
}

void loop(void)
{
#ifdef _DEBUG
	run_tests();
#endif
	// run_projectile_demo(canvas);
	// run_clock_demo(canvas);
	// run_shadow_demo(canvas);
	// run_light_demo(canvas);

	// run_scene_demo(canvas);
	// run_scene_plane_demo(canvas);
	// run_scene_patterns_demo(canvas);
	
	// run_fresnel_demo(canvas);
	// run_glass_sphere_demo(canvas);
	// run_cylinder_demo(canvas);
	// run_hexagon_demo(canvas);

	// run_reflection_demo(canvas);
	// run_cylinders_demo(canvas);
	// run_obj_demo(canvas);
	// run_cover_demo(canvas);
	run_csg_demo(canvas);
}