#include "ColorPattern.h"

const SolidColor3D SolidColor3D::Default(1, 1, 1);

ColorPattern::ColorPattern()
{ }

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


StripeColor::StripeColor(const Color3D& colorA, const Color3D& colorB)
	: ColorA(colorA), ColorB(colorB)
{ }

const Color3D StripeColor::at(const Point3D& location) const
{
	return (((int)floor(location.X()) % 2) == 0) ? ColorA : ColorB;
}


GradientColor::GradientColor(const Color3D& colorA, const Color3D& colorB)
	: StripeColor(colorA, colorB)
{ }

const Color3D GradientColor::at(const Point3D& location) const
{
	return ColorA * (ColorB - ColorA) * (location.X() - floor(location.X()));
}