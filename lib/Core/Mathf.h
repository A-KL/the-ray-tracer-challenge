#pragma once

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

inline bool Mathf<int>::Approximately(int a, int b)
{
	return a == b;
}