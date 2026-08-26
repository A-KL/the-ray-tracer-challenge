#include "tests.h"

#include "unity.h"

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(run_matrix_tests);

  RUN_TEST(run_ray_tests);

  RUN_TEST(run_color_tests);

  RUN_TEST(run_light_tests);

  RUN_TEST(run_scene_tests);

  RUN_TEST(run_normal_tests);

  RUN_TEST(run_camera_tests);

  RUN_TEST(run_shadow_tests);

  RUN_TEST(run_patterns_tests);

  RUN_TEST(run_reflection_tests);

  RUN_TEST(run_cube_tests);

  RUN_TEST(run_cylinder_tests);

  RUN_TEST(run_cone_tests);

  RUN_TEST(run_group_tests);

  RUN_TEST(run_triangle_tests);

  return UNITY_END();
}

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int main(void) {
  return runUnityTests();
}