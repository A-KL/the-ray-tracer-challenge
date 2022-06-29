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


StripeColor3D::StripeColor3D(const Color3D& colorA, const Color3D& colorB)
	: StripeColor3D(colorA, colorB, Matrix4d::Identity())
{ }

StripeColor3D::StripeColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: ColorA(colorA), ColorB(colorB), ColorPattern(transformation)
{ }

const Color3D StripeColor3D::at(const Point3D& location) const
{
	return (((int)floor(location.X()) % 2) == 0) ? ColorA : ColorB;
}


GradientColor3D::GradientColor3D(const Color3D& colorA, const Color3D& colorB)
	: StripeColor3D(colorA, colorB, Matrix4d::Identity())
{ }

GradientColor3D::GradientColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation)
	: StripeColor3D(colorA, colorB, transformation)
{ }

const Color3D GradientColor3D::at(const Point3D& location) const
{
	return ColorA + (ColorB - ColorA) * (location.X() - floor(location.X()));
}