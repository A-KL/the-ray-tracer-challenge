#pragma once
class Color
{
public:
	Color(int); 

	int R();

	int G();

	int B();

	int A();

	static Color Green();

	static const int Bpp24 = 24;

	static const int Bpp32 = 32;

	static const int Bpp8 = 8;

private:
	char* _data;
};

