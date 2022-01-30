#include <math.h>

#include "Mathf.h"

const double Mathf::Epsilon = 0.00001f;

bool Mathf::Approximately(float a, float b)
{
	return fabs((double)a - b) < Epsilon;
}

bool Mathf::Approximately(double a, double b)
{
	return fabs((double)a - b) < Epsilon;
}

double Mathf::ToZeroIfClose(double a)
{
	return Approximately(a, 0) ? 0 : a;
}
