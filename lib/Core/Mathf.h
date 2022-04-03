#pragma once

#include <math.h>

template<typename TItem>
struct Mathf
{
	inline static TItem Epsilon()
	{
		return 0.00001;
	}

	static inline bool Approximately(TItem a, TItem b)
	{
		return fabs(a - b) < Epsilon();
	}

	static inline double ToZeroIfClose(TItem a)
	{
		return Approximately(a, 0) ? 0 : a;
	}

private:
	Mathf()
	{ }
};