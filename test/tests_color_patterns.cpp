#include <cassert>

#include "../lib/Core/Point3D.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/ColorPattern.h"

#include "../lib/Core/Material3D.h"
#include "../lib/Core/Light3D.h"
#include "../lib/Core/Sphere3D.h"

#include "tests.h"

void test_gradient_pattern_interpolates()
{
	// Set up
	GradientColor3D gradientWhiteAndBlack(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == gradientWhiteAndBlack.at(Point3D(0, 0, 0)));
	assert(Color3D(0.75, 0.75, 0.75) == gradientWhiteAndBlack.at(Point3D(0.25, 0, 0)));
	assert(Color3D(0.5, 0.5, 0.5) == gradientWhiteAndBlack.at(Point3D(0.5, 0, 0)));
	assert(Color3D(0.25, 0.25, 0.25) == gradientWhiteAndBlack.at(Point3D(0.75, 0, 0)));
}

void test_ring_pattern_interpolates()
{
	// Set up
	RingColor3D whiteAndBlackRing(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == whiteAndBlackRing.at(Point3D(0, 0, 0)));
	assert(Color3D::Black == whiteAndBlackRing.at(Point3D(1, 0, 0)));
	assert(Color3D::Black == whiteAndBlackRing.at(Point3D(0, 0, 1)));
	assert(Color3D::Black == whiteAndBlackRing.at(Point3D(0.708, 0, 0.708)));
}

void test_stride_pattern_alternates()
{
	// Set up
	auto black = Color3D::Black;
	auto white = Color3D::White;

	StripeColor3D stripeWhiteAndBlack(white, black);

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
	Sphere3D sphere;
	Material3D material(StripeColor3D(Color3D(1, 1, 1), Color3D(0, 0, 0)), 1, 0, 0);
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, -10), Color3D(1, 1, 1));

	// Act
	auto result1 = light.Compute(material, sphere, Point3D(0.9, 0, 0), camera, normal, false);
	auto result2 = light.Compute(material, sphere, Point3D(1.1, 0, 0), camera, normal, false);

	// Assert
	assert(Color3D(1, 1, 1) == result1);
	assert(Color3D(0, 0, 0) == result2);
}

void test_transformed_object_with_pattern()
{
	// Set up
	Sphere3D sphere(Matrix4d::Scale(2, 2, 2));
	Point3D location(1.5, 0, 0);
	StripeColor3D stripeWhiteAndBlack(Color3D::White, Color3D::Black);

	// Act
	auto result = stripeWhiteAndBlack.at_shape(location, sphere);

	// Assert
	assert(Color3D::White == result);
}

void test_object_with_scaled_pattern()
{
	// Set up
	Sphere3D sphere;
	Point3D location(1.5, 0, 0);
	StripeColor3D stripeWhiteAndBlack(Color3D::White, Color3D::Black, Matrix4d::Scale(2, 2, 2));

	// Act
	auto result = stripeWhiteAndBlack.at_shape(location, sphere);

	// Assert
	assert(Color3D::White == result);
}

void test_transformed_object_with_translated_pattern()
{
	// Set up
	Sphere3D sphere(Matrix4d::Scale(2, 2, 2));
	Point3D location(2.5, 0, 0);
	StripeColor3D stripeWhiteAndBlack(Color3D::White, Color3D::Black, Matrix4d::Translate(0.5, 0, 0));

	// Act
	auto result = stripeWhiteAndBlack.at_shape(location, sphere);

	// Assert
	assert(Color3D::White == result);
}

void run_patterns_tests()
{
	test_stride_pattern_alternates();

	test_gradient_pattern_interpolates();

	test_light_with_pattern();

	test_transformed_object_with_pattern();

	test_object_with_scaled_pattern();

	test_transformed_object_with_translated_pattern();

	test_ring_pattern_interpolates();
}