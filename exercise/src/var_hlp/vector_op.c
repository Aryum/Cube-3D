#include "var_hlp.h"

t_vct	add_vct(t_vct a, t_vct b)
{
	t_vct ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vct	scale_vct(t_vct a, float factor)
{
	t_vct ret;

	ret.x = a.x * factor;
	ret.y = a.y * factor;
	return (ret);
}

t_vct	abs_vct(t_vct vct)
{
	return ini_vct_pos(f_abs(vct.x), f_abs(vct.y));
}

float	dist_vct(t_vct a, t_vct b)
{
	return (sqrt(pow_2(a.x - b.x) + pow_2(a.y - b.y)));
}

bool	equal_vct(t_vct a, t_vct b)
{
	return (a.x == b.x && a.y == b.y);
}

float	angle_vct(t_vct vct)
{
	return (atan(vct.y / vct.x));
}