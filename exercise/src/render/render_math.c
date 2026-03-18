#include "render.h"

int clamp(int val, int min, int max)
{
	if (val >= max)
		return max;
	if (val <= min)
		return min;
	return val;
}

float	f_abs(float a)
{
	if (a < 0)
		a *= -1;
	return (a);
}