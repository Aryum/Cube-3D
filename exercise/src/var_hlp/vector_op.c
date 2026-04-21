#include "var_hlp.h"

t_vct	vct_add(t_vct a, t_vct b)
{
	t_vct ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vct	vct_scale(t_vct a, float factor)
{
	t_vct ret;

	ret.x = a.x * factor;
	ret.y = a.y * factor;
	return (ret);
}

t_vct	vct_abs(t_vct vct)
{
	return ini_vct_pos(f_abs(vct.x), f_abs(vct.y));
}

float	vct_dist(t_vct a, t_vct b)
{
	return (sqrt(pow_2(a.x - b.x) + pow_2(a.y - b.y)));
}

bool	vct_cmp(t_vct a, t_vct b)
{
	return (a.x == b.x && a.y == b.y);
}

float	vct_angle(t_vct vct)
{
	return (atan(vct.y / vct.x));
}