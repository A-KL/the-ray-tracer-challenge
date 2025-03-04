#pragma once

#include <iostream>
#include <cstring>
#include <math.h>

#include "Mathf.h"

template<typename TItem>
class Primitive3D
{
public:
	Primitive3D(const TItem data[])
	{ 
		memcpy(_data, data, sizeof(_data));
	}

	Primitive3D(TItem x, TItem y, TItem z, TItem w)
		: _data { x, y, z, w }
	{ }

	const inline TItem X() const { return _data[0]; };

	const inline TItem Y() const { return _data[1]; };

	const inline TItem Z() const { return _data[2]; };

	const inline TItem W() const { return _data[3]; };

	inline void SetW(TItem value) { _data[3] = value; };

	inline const TItem& operator[](const unsigned index) const
	{
		return _data[index];
	}

	void ToArray(TItem result[]) const
	{
		memcpy(result, _data, sizeof(_data));
	}

	inline Primitive3D<TItem> operator-()
	{
		return Primitive3D<TItem>(-X(), -Y(), -Z(), -W());
	}

	virtual bool operator==(const Primitive3D<TItem>& other)
	{
		return 
			Mathf<TItem>::Approximately(X(), other.X()) &&
			Mathf<TItem>::Approximately(Y(), other.Y()) &&
			Mathf<TItem>::Approximately(Z(), other.Z()) &&
			W() == other.W();
	}

	friend std::ostream& operator<<(std::ostream& out, const Primitive3D<TItem>& p)
	{
		out << "(";
		out << p.X() << ",";
		out << p.Y() << ",";
		out << p.Z();
		out << ")";

		return out;
	}

private:
	TItem _data[4];
};

