#pragma once

#include <math.h>

template<typename TItem>
struct Mathf
{
	inline static TItem Epsilon()
	{
		return 0.0001;
	}

	static inline bool Approximately(TItem a, TItem b)
	{
		return fabs(a - b) <= Epsilon();
	}

	static inline bool IsZero(TItem a)
	{
		return Approximately(a, 0);
	}

	static inline double ToZeroIfClose(TItem a)
	{
		return IsZero(a) ? 0 : a;
	}

	static inline TItem Min(TItem a, TItem b, TItem c)
	{
		return a > b ? b > c ? c : b : a > c ? c : a;
	}

	static inline TItem Max(TItem a, TItem b, TItem c)
	{
		return a < b ? b < c ? c : b : a < c ? c : a;
	}

private:
	Mathf()
	{ }
};