#pragma once

#ifndef DBL_EPSILON
	#define DBL_EPSILON 0.001//2.2204460492503131e-016
#endif

template<typename TItem>
struct Mathf
{
	static inline bool Approximately(TItem a, TItem b)
	{
		return fabs(a - b) < 0.00001f;
	}

	static inline double ToZeroIfClose(TItem a)
	{
		return Approximately(a, 0) ? 0 : a;
	}

private:
	Mathf()
	{ }
};