// #include "Canvas.h"

// #include "../test/tests.h"

// #include "examples.h"

// #ifdef ARDUINO
// #include "ArduinoApp.h"
// #else
// #include "SDL_App.h"
// #endif

// void Run(Canvas& canvas)
// { 
// #ifdef _DEBUG
// 	run_tests();
// #endif

// 	//run_projectile_demo(canvas);
// 	//run_clock_demo(canvas);
// 	//run_shadow_demo(canvas);
// 	//run_light_demo(canvas);

// 	//run_scene_demo(canvas);
// 	//run_scene_plane_demo(canvas);
// 	//run_scene_patterns_demo(canvas);
// 	//run_fresnel_demo(canvas);
// 	run_glass_sphere_demo(canvas);
// }

#include <lgfx/v1/platforms/sdl/Panel_sdl.hpp>
#if defined ( SDL_h_ )

void setup(void);
void loop(void);

__attribute__((weak))
int user_func(bool* running)
{
  setup();
  do
  {
    loop();
  } while (*running);
  return 0;
}

int main(int, char**)
{
  return lgfx::Panel_sdl::main(user_func);
}

#endif