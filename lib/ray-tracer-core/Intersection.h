#pragma once

class Intersection
{
public:
	Intersection(double t, const Shape3D& object)
		: _t(t), _object(&object)
	{ }

	inline double T() const 
	{
		return _t;
	}

	static const Intersection Empty;

	bool operator==(const Intersection& other) const
	{
		return _t == other._t && _object == other._object;
	}

	bool operator!=(const Intersection& other)
	{
		return !(*this == other);
	}

	inline const Shape3D* Object() const
	{
		return _object;
	}

private:
	Intersection(double t, const Shape3D* object)
		: _t(t), _object(object)
	{ }


	double _t;
	const Shape3D* _object;
};
