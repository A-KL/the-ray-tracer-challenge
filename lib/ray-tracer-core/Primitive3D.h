#pragma once

#include <iostream>
using namespace std;

template<typename TItem>
class Primitive3D
{
public:
	Primitive3D(TItem x, TItem y, TItem z, TItem w)
		: _x(x), _y(y), _z(z), _w(w)
	{ }

	inline TItem X() const { return _x; };

	inline TItem Y() const { return _y; };

	inline TItem Z() const { return _z; };

	//inline const TItem& operator[](const unsigned index) const
	//{
	//	switch (index)
	//	{
	//		0: return _x;
	//		1: return _y;
	//		2: return _z;
	//		3: return _w;

	//		default:
	//			break;
	//	}
	//}

	void ToArray(TItem result[]) const
	{
		result[0] = _x;
		result[1] = _y;
		result[2] = _z;
		result[3] = _w;
	}

	inline Primitive3D operator-()
	{
		return Primitive3D(-_x, -_y, -_z, -_w);
	}

	friend ostream& operator<<(ostream& out, const Primitive3D<TItem>& p)
	{
		out << "(";
		out << p._x << ",";
		out << p._y << ",";
		out << p._z;
		out << ")";

		return out;
	}

protected:
	TItem _x, _y, _z, _w;
};

