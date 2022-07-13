#include "Color3D.h"

#include "Mathf.h"

const Color3D Color3D::Black(0, 0, 0);

const Color3D Color3D::White(1, 1, 1);

const Color3D Color3D::Red(1, 0, 0);

const Color3D Color3D::Green(0, 1, 0);

const Color3D Color3D::DarkGreen(0, 0.6, 0);

const Color3D Color3D::LightGreen(0, 0.8, 0);

const Color3D Color3D::Blue(0, 0, 1);

const Color3D Color3D::Yellow(1, 1, 0);

const Color3D Color3D::Gray(0.4, 0.4, 0.4);

const Color3D Color3D::DarkGray(0.1, 0.1, 0.1);

const Color3D Color3D::operator*(const Color3D& other) const
{
	return Color3D { (R * other.R), (G * other.G), (B * other.B)};
}

const Color3D Color3D::operator+(const Color3D& other) const
{
	return Color3D { R + other.R, G + other.G, B + other.B };
}

const Color3D Color3D::operator-(const Color3D& other) const
{
	return Color3D{ R - other.R, G - other.G, B - other.B };
}

const Color3D Color3D::operator*(double other) const
{
	return Color3D { R * other, G * other, B * other };
}

const Color3D Color3D::operator/(double other) const
{
	return Color3D{ R / other, G / other, B / other };
}

bool Color3D::operator==(const Color3D& other) const
{
	return
		Mathf<double>::Approximately(R, other.R) &&
		Mathf<double>::Approximately(G, other.G) &&
		Mathf<double>::Approximately(B, other.B);
}

void Color3D::operator+=(const Color3D& other)
{
	this->R = this->R + other.R;
	this->G = this->G + other.G;
	this->B = this->B + other.B;
}

Color3D::operator unsigned int() const
{
	return (RToByte() << 16) | (GToByte() << 8) | BToByte();
}

Color3D::operator unsigned short() const
{
	return ((RToByte() >> 3) << 11 | (GToByte() >> 2) << 5 | BToByte() >> 3);
}