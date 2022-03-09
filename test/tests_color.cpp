#include <cassert>

#include "../lib/Core/Color3D.h"

#include "tests.h"

void test_color3d_rgb888()
{
	// Set up
	Color3D white(1, 1, 1);
	Color3D white2(2, 1.9, 1.1);

	Color3D black(0, 0, 0);
	Color3D black2(-2, 0, -0.1);

	// Act
	auto white_888 = (unsigned int)white;
	auto white2_888 = (unsigned int)white2;

	auto black_888 = (unsigned int)black;
	auto black2_888 = (unsigned int)black2;

	// Assert
	assert(0x00FFFFFF == white_888);
	assert(0x00FFFFFF == white2_888);
	assert(0x00000000 == black_888);
	assert(0x00000000 == black2_888);
}

void test_color3d_rgb565()
{
	// Set up
	Color3D red(1, 0, 0);
	Color3D purple(0.5, 0, 0.5);
	Color3D gray(0.5, 0.5, 0.5);

	// Act
	auto red565 = (unsigned short)red;
	auto purple565 = (unsigned short)purple;
	auto gray565 = (unsigned short)gray;

	// Assert
	assert(0xF800 == red565);
	assert(0x780F == purple565);
	assert(0x7BEF == gray565);
}

void test_color_rgb565()
{
	// Set up
	Color3D red = Color3D::Red;
	Color3D purple{ 0.5, 0, 0.5 };
	Color3D gray{ 0.5, 0.5, 0.5 };

	// Act
	auto red565 = (unsigned short)red;
	auto purple565 = (unsigned short)purple;
	auto gray565 = (unsigned short)gray;

	// Assert
	assert(0xF800 == red565);
	assert(0x780F == purple565);
	assert(0x7BEF == gray565);
}

void test_color_rgb16()
{
	// Set up
	Color3D orange{ 1, 0.706, 0 };

	// Act
	auto orange565 = (unsigned short)orange;

	// Assert
	assert(0xFDA0 == orange565);
}

void test_color_rgb24()
{
	// Set up
	Color3D orange{ 1, 0.706, 0 };

	// Act
	auto result = (unsigned int)orange;

	// Assert
	// 0xBBGGRR
	assert(0xFFB400 == result);
}

void test_color_mul()
{
	// Set up
	Color3D color1{ 1, 0, 0 };
	Color3D color2{ 0, 1, 0 };
	Color3D expected{ 0.5, 0.5, 0 };

	// Act
	auto result = color1 * color2;

	// Assert
	//assert(expected == result);
}

void test_color_mul_scalar()
{
	// Set up
	Color3D color{ 0.2, 0.5, 0 };

	// Act
	auto result = color * 2.0;

	// Assert
	assert(Color3D(0.4, 1, 0) == result);
}

void run_color_tests()
{
	test_color_rgb565();

	test_color_rgb16();

	test_color_rgb24();

	test_color_mul();

	test_color_mul_scalar();

	test_color3d_rgb888();

	test_color3d_rgb565();
}