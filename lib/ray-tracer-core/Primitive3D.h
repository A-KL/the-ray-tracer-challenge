#pragma once

class Primitive3D
{
public:
	Primitive3D(float x, float y, float z, float w)
		: _x(x), _y(y), _z(z), _w(w)
	{ }

	inline float X() const { return _x; };

	inline float Y() const { return _y; };

	inline float Z() const { return _z; };

	Primitive3D operator-();

protected:
	float _x, _y, _z, _w;
};

