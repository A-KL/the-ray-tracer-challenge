#include <cassert>

#include "../lib/Core/Point3D.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/ColorPattern.h"

#include "../lib/Core/Material3D.h"
#include "../lib/Core/Light3D.h"

#include "tests.h"

void test_gradient_pattern_interpolates()
{
	// Set up
	GradientColor gradientWhiteAndBlack(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == gradientWhiteAndBlack.at(Point3D(0, 0, 0)));
	assert(Color3D(0.75, 0.75, 0.75) == gradientWhiteAndBlack.at(Point3D(0.25, 0, 0)));
	assert(Color3D(0.5, 0.5, 0.5) == gradientWhiteAndBlack.at(Point3D(0.5, 0, 0)));
	assert(Color3D(0.25, 0.25, 0.25) == gradientWhiteAndBlack.at(Point3D(0.75, 0, 0)));
}

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

void test_light_with_pattern()
{
	// Set up
	Material3D material(StripeColor(Color3D(1, 1, 1), Color3D(0, 0, 0)), 1, 0, 0);
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, -10), Color3D(1, 1, 1));

	// Act
	auto result1 = light.Compute(material, Point3D(0.9, 0, 0), camera, normal, false);
	auto result2 = light.Compute(material, Point3D(1.1, 0, 0), camera, normal, false);

	// Assert
	assert(Color3D(1, 1, 1) == result1);
	assert(Color3D(0, 0, 0) == result2);
}

void run_patterns_tests()
{
	test_stride_pattern_alternates();

	test_gradient_pattern_interpolates();

	test_light_with_pattern();
}