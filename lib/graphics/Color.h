#pragma once

#include <cassert>

template <class T>
union Color;

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


template <class T>
union Color
{
	T Channels;
	unsigned int Raw;
};



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