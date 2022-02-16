#pragma once

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