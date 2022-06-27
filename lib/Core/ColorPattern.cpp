#include "ColorPattern.h"
#include "Shape3D.h"

const SolidColor3D SolidColor3D::Default(1, 1, 1);

ColorPattern::ColorPattern()
	: Transformation(Matrix4d::Identity())
{ }

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
	: Color(color)
{ }

const Color3D SolidColor3D::at(const Point3D& location) const
{
	return Color;
}


StripeColor3D::StripeColor3D(const Color3D& colorA, const Color3D& colorB)
	: ColorA(colorA), ColorB(colorB)
{ }

const Color3D StripeColor3D::at(const Point3D& location) const
{
	return (((int)floor(location.X()) % 2) == 0) ? ColorA : ColorB;
}


GradientColor3D::GradientColor3D(const Color3D& colorA, const Color3D& colorB)
	: StripeColor3D(colorA, colorB)
{ }

const Color3D GradientColor3D::at(const Point3D& location) const
{
	return ColorA + (ColorB - ColorA) * (location.X() - floor(location.X()));
}