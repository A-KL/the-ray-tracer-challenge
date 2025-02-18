#include "ColorPattern.h"
#include "Shape3D.h"

const SolidColor3D SolidColor3D::Default(1, 1, 1);

ColorPattern::ColorPattern()
	: Transformation(Matrix4d::Identity())
{ }

ColorPattern::ColorPattern(const Matrix4d& transformation)
	: Transformation(transformation)
{ }

const bool ColorPattern::operator==(const ColorPattern& other) const
{
	return Transformation == other.Transformation;
}

const Color3D ColorPattern::at_shape(const Point3D& location, const Shape3D& shape) const
{
	auto object_point = shape.Transformation.Inverse() * location;
	auto pattern_point = Transformation.Inverse() * object_point;

	return at(pattern_point);
}

// Test Pattern

TestPattern::TestPattern()
	: ColorPattern()
{ }

TestPattern::TestPattern(const Matrix4d& transformation)
	: ColorPattern(transformation)
{ }

const Color3D TestPattern::at(const Point3D& location) const
{
	return Color3D(location.X(), location.Y(), location.Z());
}

// SolidColor3D

SolidColor3D::SolidColor3D(double r, double g, double b)
	: SolidColor3D(Color3D(r, g, b))
{ }

SolidColor3D::SolidColor3D(const Color3D& color)
	: SolidColor3D(color, Matrix4d::Identity())
{ }

SolidColor3D::SolidColor3D(const Color3D& color, const Matrix4d& transformation)
	: Color(color), ColorPattern(transformation)
{ }

const Color3D SolidColor3D::at(const Point3D& location) const
{
	return Color;
}

// StripeColor3D

StripeColor3D::StripeColor3D(const Color3D& colorA, const Color3D& colorB)
	: StripeColor3D(colorA, colorB, Matrix4d::Identity())
{ }

StripeColor3D::StripeColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: ColorA(colorA), ColorB(colorB), ColorPattern(transformation)
{ }

const Color3D StripeColor3D::at(const Point3D& location) const
{
	return Mathf<double>::IsZero(std::fmod(floor(location.X()), 2)) ? ColorA : ColorB;
}

// GradientColor3D

GradientColor3D::GradientColor3D(const Color3D& colorA, const Color3D& colorB)
	: GradientColor3D(colorA, colorB, Matrix4d::Identity())
{ }

GradientColor3D::GradientColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: StripeColor3D(colorA, colorB, transformation)
{ }

const Color3D GradientColor3D::at(const Point3D& location) const
{
	return ColorA + (ColorB - ColorA) * (location.X() - floor(location.X()));
}

// RingColor3D

RingColor3D::RingColor3D(const Color3D& colorA, const Color3D& colorB)
	: RingColor3D(colorA, colorB, Matrix4d::Identity())
{ }

RingColor3D::RingColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: StripeColor3D(colorA, colorB, transformation)
{ }

const Color3D RingColor3D::at(const Point3D& location) const
{
	return (
		Mathf<double>::IsZero(
			std::fmod(
				floor(
					sqrt(
						location.X() * location.X() + location.Z() * location.Z()
					)
				),
				2
			)
		)
	) ? ColorA : ColorB;
}

// CheckersColor3D

CheckersColor3D::CheckersColor3D(const Color3D& colorA, const Color3D& colorB)
	: CheckersColor3D(colorA, colorB, Matrix4d::Identity())
{ }

CheckersColor3D::CheckersColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: StripeColor3D(colorA, colorB, transformation)
{ }

const Color3D CheckersColor3D::at(const Point3D& location) const
{
	return (
		Mathf<double>::IsZero(
			std::fmod(
				floor(location.X()) + floor(location.Y())+ floor(location.Z()),
				2
			)
		)
	) ? ColorA : ColorB;
}

// BlendedColor3D

BlendedColor3D::BlendedColor3D(const ColorPattern& patternA, const ColorPattern& patternB)
	: BlendedColor3D(&patternA, &patternB)
{ }

BlendedColor3D::BlendedColor3D(const ColorPattern* patternA, const ColorPattern* patternB)
	: PatternA(patternA), PatternB(patternB)
{ }

const Color3D BlendedColor3D::at(const Point3D& location) const
{
	auto colorA = PatternA->at(location);
	auto colorB = PatternB->at(location);

	return (colorA + colorB) / 2.0;
}