#include <cassert>

#include "../lib/Core/Point3D.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/ColorPattern.h"

#include "../lib/Core/Material3D.h"
#include "../lib/Core/Light3D.h"
#include "../lib/Core/Sphere3D.h"

#include "tests.h"

/* Stripe pattern */

// A stripe pattern is constant in y
void test_stripe_pattern_constant_in_y()
{
	// Set up
	auto black = Color3D::Black;
	auto white = Color3D::White;

	StripeColor3D pattern(white, black);

	// Act
	// Assert
	assert(white == pattern.at(Point3D(0, 0, 0)));
	assert(white == pattern.at(Point3D(0, 1, 0)));
	assert(white == pattern.at(Point3D(0, 2, 0)));
}

// A stripe pattern is constant in z
void test_stripe_pattern_constant_in_z()
{
	// Set up
	auto black = Color3D::Black;
	auto white = Color3D::White;

	StripeColor3D pattern(white, black);

	// Act
	// Assert
	assert(white == pattern.at(Point3D(0, 0, 0)));
	assert(white == pattern.at(Point3D(0, 0, 1)));
	assert(white == pattern.at(Point3D(0, 0, 2)));
}

// A stripe pattern is constant in x
void test_stripe_pattern_alternates_in_x()
{
	// Set up
	auto black = Color3D::Black;
	auto white = Color3D::White;

	StripeColor3D pattern(white, black);

	// Act
	// Assert
	assert(white == pattern.at(Point3D(0, 0, 0)));
	assert(white == pattern.at(Point3D(0.9, 0, 0)));

	assert(black == pattern.at(Point3D(1, 0, 0)));
	assert(black == pattern.at(Point3D(-1, 0, 0)));

	assert(black == pattern.at(Point3D(-1, 0, 0)));
	assert(white == pattern.at(Point3D(-1.1, 0, 0)));
}

// Lighting with a pattern applied
void test_stripe_light_applied()
{
	// Set up
	Material3D material(StripeColor3D(Color3D::White, Color3D::Black), 1, 0, 0);
	Sphere3D sphere(material);
	
	Vector3D camera(0, 0, -1);
	Vector3D normal(0, 0, -1);

	Light3D light(Point3D(0, 0, -10), Color3D::White);

	// Act
	auto result1 = light.Compute(sphere, Point3D(0.9, 0, 0), camera, normal, false);
	auto result2 = light.Compute(sphere, Point3D(1.1, 0, 0), camera, normal, false);

	// Assert
	assert(Color3D::White == result1);
	assert(Color3D::Black == result2);
}

// Stripes with an object transformation
void test_stripe_transformed_object()
{
	// Set up
	Sphere3D sphere(Matrix4d::Scale(2, 2, 2));
	Point3D location(1.5, 0, 0);
	StripeColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	auto result = pattern.at_shape(location, sphere);

	// Assert
	assert(Color3D::White == result);
}

// Stripes with a pattern transformation
void test_stripe_object_with_scaled_pattern()
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

// Stripes with both an object and a pattern transformation
void test_stripes_transformed_object_with_translated_pattern()
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

/* Gradient pattern */

// A gradient linearly interpolates between colors
void test_gradient_pattern_interpolates()
{
	// Set up
	GradientColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White 						== pattern.at(Point3D(0, 0, 0)));
	assert(Color3D(0.75, 0.75, 0.75) 	== pattern.at(Point3D(0.25, 0, 0)));
	assert(Color3D(0.5, 0.5, 0.5) 		== pattern.at(Point3D(0.5, 0, 0)));
	assert(Color3D(0.25, 0.25, 0.25) 	== pattern.at(Point3D(0.75, 0, 0)));
}

/* Ring pattern */

// A ring should extend in both x and z
void test_ring_pattern_interpolates()
{
	// Set up
	RingColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == pattern.at(Point3D(0, 0, 0)));
	assert(Color3D::Black == pattern.at(Point3D(1, 0, 0)));
	assert(Color3D::Black == pattern.at(Point3D(0, 0, 1)));
	assert(Color3D::Black == pattern.at(Point3D(0.708, 0, 0.708)));
}

/* Checkers pattern */

// Checkers should repeat in x
void test_checker_pattern_interpolates_x()
{
	// Set up
	CheckersColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == pattern.at(Point3D(0.00, 0, 0)));
	assert(Color3D::White == pattern.at(Point3D(0.99, 0, 0)));
	assert(Color3D::Black == pattern.at(Point3D(1.01, 0, 0)));
}

// Checkers should repeat in x
void test_checker_pattern_repeats_y()
{
	// Set up
	CheckersColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == pattern.at(Point3D(0, 0.00, 0)));
	assert(Color3D::White == pattern.at(Point3D(0, 0.99, 0)));
	assert(Color3D::Black == pattern.at(Point3D(0, 1.01, 0)));
}

// Checkers should repeat in z
void test_checker_pattern_repeats_z()
{
	// Set up
	CheckersColor3D pattern(Color3D::White, Color3D::Black);

	// Act
	// Assert
	assert(Color3D::White == pattern.at(Point3D(0, 0, 0.00)));
	assert(Color3D::White == pattern.at(Point3D(0, 0, 0.99)));
	assert(Color3D::Black == pattern.at(Point3D(0, 0, 1.01)));
}

void run_patterns_tests()
{
	/* Stripe pattern */

	test_stripe_pattern_constant_in_y();

	test_stripe_pattern_constant_in_z();

	test_stripe_pattern_alternates_in_x();

	test_stripe_light_applied();

	test_stripe_transformed_object();

	test_stripe_object_with_scaled_pattern();

	test_stripes_transformed_object_with_translated_pattern();

	/* Gradient pattern */

	test_gradient_pattern_interpolates();

	/* Ring pattern */
	
	test_ring_pattern_interpolates();

	/* Checkers pattern */

	test_checker_pattern_interpolates_x();

	test_checker_pattern_repeats_y();

	test_checker_pattern_repeats_z();
}