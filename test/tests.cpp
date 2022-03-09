#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"

#include "tests.h"

void test_vector_dot()
{
	// Set up
	Vector3D vector1(1, 2, 3);
	Vector3D vector2(2, 3, 4);

	// Act
	auto result = vector1.Dot(vector2);

	// Assert
	assert(20 == result);
}

void test_vector_reflect()
{
	// Set up
	Vector3D v1(0, -1, 0);
	Vector3D normal(sqrt(2) / 2, sqrt(2) / 2, 0);

	// Act
	auto result = Vector3D::Reflect(v1, normal);

	// Assert
	assert(Vector3D(1, 0, 0) == result);
}

void run_tests()
{
	run_matrix_tests();

	run_ray_tests();

	run_color_tests();

	run_light_tests();

	run_scene_tests();

	run_normal_tests();

	run_camera_tests();

	run_shadow_tests();


	test_vector_dot();

	test_vector_reflect();
}