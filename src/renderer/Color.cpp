#include "Color.h"

//const int Color::Bpp24 = 24;
//
//const int Color::Bpp32 = 32;
//
//const int Color::Bpp8 = 8;
//
//const int Color::Bpp1 = 1;

int Color::Bpp()
{
	return sizeof(this);
}
