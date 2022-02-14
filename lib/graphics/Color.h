#pragma once

#include <cassert>
#include <iostream>

template <typename TChannel, typename TChannels>
struct Channels
{
	union
	{
		TChannel Data[sizeof(TChannels)];
		TChannels Raw;
	};

	inline TChannel operator[](unsigned int index) const
	{
		return Data[index];
	}

	virtual Channels<TChannel, TChannels> operator*(const Channels<TChannel, TChannels>& other) const
	{
		Channels<TChannel, TChannels> result;

		for (unsigned i = 0; i < sizeof(TChannels); i++)
		{
			result.Data[i] = (Data[i] + other.Data[i]) / 2;
		}

		return result;
	}

	bool operator==(const Channels<TChannel, TChannels>& other) const
	{
		return Raw == other.Raw;
	}

	operator TChannels() const
	{
		return Raw;
	}

	friend std::ostream& operator<<(std::ostream& out, const Channels<TChannel, TChannels>& channels)
	{
		out << "Color";
		out << "(";

		for (unsigned i = 0; i < sizeof(TChannels); i++;)
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

//class Bpp16
//{
//public:
//	virtual operator unsigned short() const = 0;
//};
//
//class Bpp24
//{
//public:
//	virtual operator unsigned int() const = 0;
//};
//
//class Bpp32
//{
//public:
//	virtual operator unsigned int() const = 0;
//};

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

union Rgb565
{
	struct 
	{
		unsigned char R : 5;
		unsigned char G : 6;
		unsigned char B : 5;
	};
	unsigned short Raw;
};


struct Rgb888
{
	struct
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
	};
	unsigned int Raw;
};

struct Rgba8888
{
	struct
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	};
	unsigned int Raw;
};

class Rgb24 :
	public Channels<unsigned char, unsigned int>
{
public:

	Rgb24(unsigned char r, unsigned char g, unsigned char b)
	{
		Data[0] = r;
		Data[1] = g;
		Data[2] = b;
		Data[3] = 0;;
	}

	Rgb24(unsigned int value)
	{
		Raw = value;
	}

	operator unsigned short() const
	{
		return ((Data[0] >> 3) << 11 | (Data[1] >> 2) << 5 | Data[2] >> 3);
	}

	//operator unsigned int() const
	//{
	//	return Raw;
	//}
	
	const Rgb24 operator*(const Rgb24& other) const
	{
		auto color = ((Channels<unsigned char, unsigned int>)*this) * (Channels<unsigned char, unsigned int>)other;

		return Rgb24(color.Raw);
	}

	const static Rgb24 Red;

	const static Rgb24 Green;

	const static Rgb24 Blue;

	const static Rgb24 Black;
};

class Rgba32 :
	public Channels<unsigned char, unsigned int>
{
public:

	const Rgb24 ToRgb888() const
	{
		return Rgb24(Raw);
	}
};

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