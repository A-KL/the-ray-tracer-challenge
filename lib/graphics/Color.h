#pragma once

#include <cassert>

template <class T>
union Color
{
	T Channels;
	unsigned int Raw;
};

struct Rgba
{
	const unsigned char R, G, B, A;

	unsigned char operator[](int index)
	{
		assert(index < 4);

		switch (index)
		{
			case 0: return R;

			case 1: return G;

			case 2: return B;

			case 3: return A;
		}
	}

	Rgba operator*(const Rgba& other) const
	{
		Rgba result 
		{ 
			(R + other.R) / 2, 
			(G + other.G) / 2,
			(B + other.B) / 2,
			(A + other.A) / 2
		};
		return result;
	}

	inline unsigned short ToRgb565()
	{
		double prop_r = R / 255.0;
		double prop_g = G / 255.0;
		double prop_b = B / 255.0;

		char r = (char)(prop_r * 31);
		char g = (char)(prop_g * 62);
		char b = (char)(prop_b * 31);

		return (r << 11) | (g << 5) | (b << 0);
	}

	static Color<Rgba> Red, Green, Blue, Black;

};

//struct Rgb
//{
//	const unsigned char R, G, B;
//
//	static Color<Rgb> Red, Green, Blue;
//};

//struct ColorMono
//{
//	const unsigned char G;
//
//	static Color<ColorMono> On, Off;
//};






//class Color
//{
//public:
//	static const int Bpp24 = 24;
//
//	static const int Bpp32 = 32;
//
//	static const int Bpp8 = 8;
//
//	static const int Bpp1 = 1;
//
//	virtual int Bpp();
//
//protected:
//	virtual const char& GetBuffer() = 0;
//};