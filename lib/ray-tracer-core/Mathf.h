#pragma once

class Mathf
{
public:
	static const double Epsilon;

	static bool Approximately(float, float);

	static bool Approximately(double, double);

	static double ToZeroIfClose(double);

private:
	Mathf()
	{ }
};

