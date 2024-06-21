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

	inline unsigned char RToByte() const
	{
		return Bound(R);
	}

	inline unsigned char GToByte() const
	{
		return Bound(G);
	}

	inline unsigned char BToByte() const
	{
		return Bound(B);
	}

	inline double operator[](unsigned int index) const
	{
		assert(index < 2);

		switch (index)
		{
			case 0: return R;
			case 1: return G;
			case 2: return B;
		}
		throw std::invalid_argument("Unable to address a channel via index.");
	}

	const Color3D operator*(const Color3D& other) const;

	const Color3D operator+(const Color3D& other) const;

	const Color3D operator-(const Color3D& other) const;

	const Color3D operator*(double other) const;

	const Color3D operator/(double other) const;

	void operator+=(const Color3D& other);

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

	const static Color3D Red;

	const static Color3D Green;

	const static Color3D DarkGreen;

	const static Color3D LightGreen;

	const static Color3D Blue;

	const static Color3D Yellow;

	const static Color3D Gray;

	const static Color3D DarkGray;

private:
	inline unsigned char Bound(double val) const
	{
		return (val > 1 ? 1 : val < 0 ? 0 : val) * 255;
	}
};