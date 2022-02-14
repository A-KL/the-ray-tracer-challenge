#pragma once

#include <cassert>
#include <iostream>

template <typename TItem, unsigned TSize>
struct ColorChannels
{
	TItem Data[TSize];

	const unsigned char Bpp = 8 * TSize;

	//inline TItem operator[](unsigned int index) const
	//{
	//	return Data[index];
	//}

	ColorChannels<TItem, TSize> operator*(const ColorChannels<TItem, TSize>& other) const
	{
		ColorChannels<TItem, TSize> result;

		for (unsigned i = 0; i < TSize; i++)
		{
			result.Data[i] = (Data[i] + other.Data[i]) / 2;
		}

		return result;
	}

	bool operator==(const ColorChannels<TItem, TSize>& other) const
	{
		return memcmp(Data, other.Data, TSize) == 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const ColorChannels<TItem, TSize>& channels)
	{
		out << "Color";
		out << "(";

		for (unsigned i = 0; i < TSize; i++;)
		{
			out << Data[i];
			if (i < TSize - 1)
			{
				out << ",";
			}
		}
		out << ")";

		return out;
	}

	
};

class Rgb16 :
	public ColorChannels<unsigned char, 3>
{
public:

	inline unsigned char R() const
	{
		return Data[0];
	}

	inline unsigned char G() const
	{
		return Data[1];
	}

	inline unsigned char B() const
	{
		return Data[2];
	}

	operator unsigned short()
	{
		return (R() >> 3) << 11 | (G() >> 2) << 5 | B() >> 3;
	}
};

class Rgb24 :
	public Rgb16
{
public:

	const Rgb16 ToRgb565() const
	{
		Rgb16 result { *this };

		return result;
	}
	
	operator unsigned int()
	{
		return R() << 16 | G() << 8 | B();
	}
};

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