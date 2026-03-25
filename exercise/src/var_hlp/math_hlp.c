#include "var_hlp.h"

float clamp(float val, float min, float max)
{
	if (val >= max)
		return max;
	if (val <= min)
		return min;
	return val;
}

bool reached_clamp(float *val, float min, float max)
{
	*val = clamp(*val, min, max);
	return (*val ==  min || *val == max);
}

void	update_rad(float *rad, float delta)
{
	*rad += delta;
	if (*rad > PI_360)
		*rad -= PI_360;
	else if (*rad < 0)
		*rad += PI_360;
}

float	f_abs(float a)
{
	if (a < 0)
		a *= -1;
	return (a);
}

float	pow_2(float a)
{
	return (a * a);
}