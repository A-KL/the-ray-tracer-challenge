#include "Mathf.h"

#include "Color3D.h"

const Color3D Color3D::Black(0, 0, 0);

const Color3D Color3D::White(1, 1, 1);

const Color3D Color3D::operator*(const Color3D& other) const
{
	return Color3D{ R * other.R, G * other.G, B * other.B };
}

const Color3D Color3D::operator+(const Color3D& other) const
{
	return Color3D{ R + other.R, G + other.G, B + other.B };
}

const Color3D Color3D::operator*(double other) const
{
	return Color3D{ R * other, G * other, B * other };
}

bool Color3D::operator==(const Color3D& other) const
{
	return
		Mathf::Approximately(R, other.R) &&
		Mathf::Approximately(G, other.G) &&
		Mathf::Approximately(B, other.B);
}

Color3D::operator unsigned int() const
{
	unsigned char r = (R > 1 ? 1 : R < 0 ? 0 : R) * 255;
	unsigned char g = (G > 1 ? 1 : G < 0 ? 0 : G) * 255;
	unsigned char b = (B > 1 ? 1 : B < 0 ? 0 : B) * 255;

	return (r << 16) | (g << 8) | b;
}

Color3D::operator unsigned short() const
{
	unsigned char r = (R > 1 ? 1 : R < 0 ? 0 : R) * 255;
	unsigned char g = (G > 1 ? 1 : G < 0 ? 0 : G) * 255;
	unsigned char b = (B > 1 ? 1 : B < 0 ? 0 : B) * 255;

	return ((r >> 3) << 11 | (g >> 2) << 5 | b >> 3);
}