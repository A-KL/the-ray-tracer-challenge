#pragma once

class Color
{
public:
	static const int Bpp24 = 24;

	static const int Bpp32 = 32;

	static const int Bpp8 = 8;

	static const int Bpp1 = 1;

	virtual int Bpp();

protected:
	virtual const char& GetBuffer() = 0;
};