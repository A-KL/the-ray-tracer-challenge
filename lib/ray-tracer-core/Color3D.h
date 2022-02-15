#pragma once

#include <iostream>
#include <cassert>

#include "Mathf.h"

struct Color3D
{
	Color3D(double r = 1, double g = 1, double b = 1)
		: R(r), G(g), B(b)
	{ }

	double R;
	double G;
	double B;

	inline double operator[](unsigned int index) const
	{
		assert(index < 2);

		switch (index)
		{
		case 0: return R;
		case 1: return G;
		case 2: return B;
		}
	}

	const Color3D operator*(const Color3D& other) const
	{
		return Color3D { R * other.R, G * other.G, B * other.B };
	}

	const Color3D operator+(const Color3D& other) const
	{
		return Color3D { R + other.R, G + other.G, B + other.B };
	}

	const Color3D operator*(double other) const
	{
		return Color3D { R * other, G * other, B * other };
	}

	bool operator==(const Color3D& other) const
	{
		return
			Mathf::Approximately(R, other.R) &&
			Mathf::Approximately(G, other.G) &&
			Mathf::Approximately(B, other.B);
	}

	inline operator unsigned int() const
	{
		unsigned char r = (R > 1 ? 1 : R < 0 ? 0 : R) * 255;
		unsigned char g = (G > 1 ? 1 : G < 0 ? 0 : G) * 255;
		unsigned char b = (B > 1 ? 1 : B < 0 ? 0 : B) * 255;

		return (r << 16) | (g << 8) | b;
	}

	inline operator unsigned short() const
	{
		unsigned char r = (R > 1 ? 1 : R < 0 ? 0 : R) * 255;
		unsigned char g = (G > 1 ? 1 : G < 0 ? 0 : G) * 255;
		unsigned char b = (B > 1 ? 1 : B < 0 ? 0 : B) * 255;

		return ((r >> 3) << 11 | (g >> 2) << 5 | b >> 3);
	}

	friend std::ostream& operator<<(std::ostream& out, const Color3D& color)
	{
		out << "Color3D";
		out << "(";
		out << color.R << ",";
		out << color.G << ",";
		out << color.B;
		out << ")";

		return out;
	}

	const static Color3D Black;

	const static Color3D White;
};