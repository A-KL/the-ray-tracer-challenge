#include <cassert>

#include "../lib/graphics/Color.h"

#include "tests.h"

void test_color_rgb565()
{
	// Set up
	Color<Rgba> red = Rgba::Red;
	Color<Rgba> purple{ 128, 0, 128, 0 };
	Color<Rgba> gray{ 128, 128, 128, 0 };

	// Act
	auto red565 = red.Channels.ToRgb565();
	auto purple565 = purple.Channels.ToRgb565();
	auto gray565 = gray.Channels.ToRgb565();

	// Assert
	assert(0xF800 == red565);
	assert(0x780F == purple565);
	assert(0x7BEF == gray565);
}

void test_color_rgb16()
{
	// Set up
	Rgb24 orange { 255, 180, 0 };

	// Act
	Rgb16 orange565 = orange.ToRgb565();

	auto result = (unsigned short)orange565;

	// Assert
	assert(0xFDA0 == result);
}

void test_color_rgb24()
{
	// Set up
	Rgb24 orange{ 255, 180, 0 };

	// Act
	auto result = (unsigned int)orange;

	// Assert
	assert(0xFFB400 == result);
}

void test_color_mul()
{
	// Set up
	Rgb24 color1 { 255, 0, 0 };
	Rgb24 color2 { 0, 255, 0 };
	Rgb24 expected { 127, 127, 0 };

	// Act
	auto result = color1 * color2;

	// Assert
	assert(expected == result);
}

void run_color_tests()
{
	test_color_rgb565();

	test_color_rgb16();

	test_color_rgb24();

	test_color_mul();
}