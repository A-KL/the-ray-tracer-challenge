#include "Canvas.h"

//#include "tests.h"
#include "examples.h"

#ifdef ARDUINO
#include "ArduinoApp.h"
#else
#include "SDL_App.h"
#endif

void Run(Canvas& canvas)
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
	run_scene_patterns_demo(canvas);
}