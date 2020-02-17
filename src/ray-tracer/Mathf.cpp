#include <math.h>

#include "Mathf.h"

const float Mathf::Epsilon = 0.00001f;

bool Mathf::Approximately(float a, float b)
{
	return fabs((double)a - b) < Epsilon;
}
