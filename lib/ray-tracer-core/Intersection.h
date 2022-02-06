#pragma once

#include <cassert>
#include <stdarg.h>

class Intersection
{
public:
	Intersection(double t, const Object3D& object)
		: _t(t), _object(object)
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

private:

	double _t;
	Object3D _object;
};

struct IntersectionComparator
{
	bool operator ()(const Intersection& intersection1, const Intersection& intersection2)
	{
		if (intersection1.T() == intersection2.T())
			return intersection1.T() < intersection2.T();

		return intersection1.T() < intersection2.T();
	}
};

template<unsigned Size>
class Intersections
{
public:
	//Intersections(std::initializer_list<Intersection> list)
	//{
	//	assert(list.size() > 0);


	//	for (auto elem : list)
	//	{
	//		//std::cout << elem << std::endl;
	//	}
	//}

	//Intersections(int count, ...)
	//{
	//	va_list ap;
	//	va_start(ap, count);

	//	for (int i = 0; i < count; i++)
	//	{
	//		_intersections[i] = va_arg(ap, Intersection);
	//	}

	//	va_end(ap);
	//}


	Intersection _intersections[Size];

	
};
