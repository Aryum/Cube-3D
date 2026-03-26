#include "var_hlp.h"

t_ray	ini_ray(t_vct start, t_vct rot, bool (*hit_cond)(t_vct))
{
	t_ray	ret;
	t_quad	quad;

	ret.cur_grid = pos_to_grid(start);
	quad = ini_quad(ret.cur_grid);
	ret.tar.x = quad.pos[(rot.x > 0) * 3].x;
	ret.tar.y = quad.pos[(rot.y > 0) * 3].y;
	ret.pos = start;
	ret.rot = rot;
	ret.hit_cond = hit_cond;
	return (ret);
}

t_rayhit	ini_hit(t_vct pos, t_dir dir)
{
	t_rayhit	ret;

	ret.pos = pos;
	ret.dir = dir;
	return (ret);
}