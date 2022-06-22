#include <cassert>

#include "../lib/Core/Point3D.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/ColorPattern.h"

#include "tests.h"

void test_stride_pattern_alternates()
{
	// Set up
	auto black = Color3D::Black;
	auto white = Color3D::White;

	StripeColor stripeWhiteAndBlack(white, black);

	// Act
	// Assert
	assert(white == stripeWhiteAndBlack.at(Point3D(0, 0, 0)));
	assert(white == stripeWhiteAndBlack.at(Point3D(0.8, 0, 0)));
	assert(black == stripeWhiteAndBlack.at(Point3D(1, 0, 0)));
	assert(black == stripeWhiteAndBlack.at(Point3D(-0.1, 0, 0)));
	assert(black == stripeWhiteAndBlack.at(Point3D(-1, 0, 0)));
	assert(white == stripeWhiteAndBlack.at(Point3D(-1.1, 0, 0)));
}

void run_patterns_tests()
{
	test_stride_pattern_alternates();
}