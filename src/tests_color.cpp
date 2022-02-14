#include <cassert>

#include "../lib/graphics/Color.h"

#include "tests.h"

void test_color_rgb565()
{
	// Set up
	Color red = Color::Red;
	Color purple { 127, 0, 127 };
	Color gray { 127, 127, 127 };

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
	Color orange { 255, 180, 0 };

	// Act
	auto orange565 = (unsigned short)orange;

	// Assert
	assert(0xFDA0 == orange565);
}

void test_color_rgb24()
{
	// Set up
	Color orange { 255, 180, 0 };

	// Act
	auto result = (unsigned int)orange;

	// Assert
	// 0xBBGGRR
	assert(0x00B4FF == result);
}

void test_color_mul()
{
	// Set up
	Color color1 { 255, 0, 0 };
	Color color2 { 0, 255, 0 };
	Color expected { 127, 127, 0 };

	// Act
	auto result = color1 * color2;

	// Assert
	assert(expected == result);
}

void test_color_mul_scalar()
{
	// Set up
	Color color{ 100, 127, 0 };

	// Act
	auto result = color * 2.0;

	// Assert
	assert(Color(200, 254, 0) == result);
}

void run_color_tests()
{
	test_color_rgb565();

	test_color_rgb16();

	test_color_rgb24();

	test_color_mul();

	test_color_mul_scalar();
}