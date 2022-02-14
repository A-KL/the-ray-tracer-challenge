#include "Color.h"

const Rgb24 Rgb24::White(255, 255, 255);

const Rgb24 Rgb24::Red(255, 0, 0);

const Rgb24 Rgb24::Green(0, 255, 0 );

const Rgb24 Rgb24::Blue(0, 0, 255);

const Rgb24 Rgb24::Black(0, 0, 0);

const Rgb24 Rgb24::operator*(const Rgb24& other) const
{
	auto color = ((Channels<unsigned char, unsigned int>) * this) * (Channels<unsigned char, unsigned int>)other;

	return Rgb24(color.Raw);
}

const Rgb24 Rgb24::operator*(double other) const
{
	auto color = ((Channels<unsigned char, unsigned int>) * this) * other;

	return Rgb24(color.Raw);
}