#include "var_hlp.h"

t_vct	ini_vct_pos(float x, float y)
{
	t_vct	ret;
	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vct	ini_vct_rad(float rad)
{
	t_vct	ret;

	ret.y = sin(rad);
	ret.x = cos(rad);
	return (ret);
}
