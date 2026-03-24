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