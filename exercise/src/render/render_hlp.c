#include "render.h"

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

float	f_abs(float a)
{
	if (a < 0)
		a *= -1;
	return (a);
}

float	square(float a)
{
	return (a * a);
}

long get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit_clean(NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}