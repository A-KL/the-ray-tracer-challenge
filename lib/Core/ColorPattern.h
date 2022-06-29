#pragma once

#include <math.h>

#include "Color3D.h"
#include "Point3D.h"
#include "MatrixOps.hpp"

class Shape3D;

class ColorPattern
{
public:
	ColorPattern();

	ColorPattern(const Matrix4d& transformation);

	const Matrix4d Transformation;

	const virtual Color3D at(const Point3D& location) const = 0;

	const virtual Color3D at_shape(const Point3D& location, const Shape3D& shape) const;

	const bool operator==(const ColorPattern& other) const;
};

class SolidColor3D
	: public ColorPattern
{
public:
	SolidColor3D(double r = 1, double g = 1, double b = 1);

	SolidColor3D(const Color3D& color);

	SolidColor3D(const Color3D& color, const Matrix4d& transformation);

	const Color3D Color;

	const Color3D at(const Point3D& location) const;

	const static SolidColor3D Default;
};


class StripeColor3D
	: public ColorPattern
{
public:
	StripeColor3D(const Color3D& colorA, const Color3D& colorB);

	StripeColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation);

	const Color3D ColorA;
	const Color3D ColorB;

	const Color3D at(const Point3D& location) const;
};

class GradientColor3D
	: public StripeColor3D
{
public:
	GradientColor3D(const Color3D& colorA, const Color3D& colorB);

	GradientColor3D(const Color3D& colorA, const Color3D& colorB, const Matrix4d& transformation);

	const Color3D at(const Point3D& location) const;
};