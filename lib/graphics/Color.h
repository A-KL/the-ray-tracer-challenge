#pragma once

#include <cassert>
#include <iostream>

template <typename TItem, unsigned TSize>
struct Channels
{
	TItem Data[TSize];

	const unsigned char Bpp = 8 * TSize;

	//inline TItem operator[](unsigned int index) const
	//{
	//	return Data[index];
	//}

	Channels<TItem, TSize> operator*(const Channels<TItem, TSize>& other) const
	{
		Channels<TItem, TSize> result;

		for (unsigned i = 0; i < TSize; i++)
		{
			result.Data[i] = (Data[i] + other.Data[i]) / 2;
		}

		return result;
	}

	bool operator==(const Channels<TItem, TSize>& other) const
	{
		return memcmp(Data, other.Data, TSize) == 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const Channels<TItem, TSize>& channels)
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

class Bpp16
{
public:
	virtual operator unsigned short() const = 0;
};

class Bpp24
{
public:
	virtual operator unsigned int() const = 0;
};

class Bpp32
{
public:
	virtual operator unsigned int() const = 0;
};

//class Rgb
//{
//public:
//	virtual unsigned char R() const = 0;
//
//	virtual unsigned char G() const = 0;
//
//	virtual unsigned char B() const = 0;
//};
//
//class Rgba : public Rgb
//{
//public:
//	virtual unsigned char A() const = 0;
//};

class Rgb16 :
	public Channels<unsigned char, 3>, Bpp16
{
public:

	Rgb16(unsigned char r, unsigned char g, unsigned char b)
	{
		Data[0] = r;
		Data[1] = g;
		Data[2] = b;
	}

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

	operator unsigned short() const
	{
		return ((R() >> 3) << 11 | (G() >> 2) << 5 | B() >> 3);
	}
};

class Rgb24 :
	public Rgb16, Bpp24
{
public:

	Rgb24(unsigned char r, unsigned char g, unsigned char b)
		: Rgb16(r, g, b)
	{ }

	const Rgb16 ToRgb565() const
	{
		return *this;
	}
	
	operator unsigned int() const
	{
		return R() << 16 | G() << 8 | B();
	}

	Rgb24 operator*(const Rgb24& other) const
	{
		auto color = ((Channels<unsigned char, 3>)*this) * (Channels<unsigned char, 3>)other;

		return Rgb24(color.Data[0], color.Data[1], color.Data[2]);
	}

	const static Rgb24 Red;

	const static Rgb24 Green;

	const static Rgb24 Blue;

	const static Rgb24 Black;
};

//class Rgba32 :
//	public Rgb24
//{
//public:
//
//	inline unsigned char A() const
//	{
//		return Data[3];
//	}
//
//	const Rgb16 ToRgb565() const
//	{
//		Rgb16 result{ *this };
//
//		return result;
//	}
//
//	operator unsigned int()
//	{
//		return A() << 24 | R() << 16 | G() << 8 | B();
//	}
//};

typedef Rgb24 Color;

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