#pragma once

#include <iostream>
#include <cassert>

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

	const Color3D operator*(const Color3D& other) const;

	const Color3D operator+(const Color3D& other) const;

	const Color3D operator*(double other) const;

	bool operator==(const Color3D& other) const;

	operator unsigned int() const;

	operator unsigned short() const;

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