#pragma once

template <class T>
union Color;

struct Rgba
{
	const unsigned char R, G, B, A;

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
	T Color;
	int Raw;
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