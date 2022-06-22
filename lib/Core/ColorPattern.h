#pragma once

#include <math.h>

#include "Color3D.h"
#include "Point3D.h"

class ColorPattern
{
public:
	ColorPattern();

	const virtual Color3D at(const Point3D& location) const = 0;

	//const virtual bool operator==(const ColorPattern& other) const = 0;
};

class SolidColor3D
	: public ColorPattern
{
public:
	SolidColor3D(double r = 1, double g = 1, double b = 1);

	SolidColor3D(const Color3D& color);

	const Color3D Color;

	const Color3D at(const Point3D& location) const;

	const static SolidColor3D Default;
};


class StripeColor
	: public ColorPattern
{
public:
	StripeColor(const Color3D& colorA, const Color3D& colorB);

	const Color3D ColorA;
	const Color3D ColorB;

	const Color3D at(const Point3D& location) const;
};

class GradientColor
	: public StripeColor
{
public:
	GradientColor(const Color3D& colorA, const Color3D& colorB);

	const Color3D at(const Point3D& location) const;
};