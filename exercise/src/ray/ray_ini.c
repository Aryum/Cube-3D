#include "ray.h"

t_ray	ini_ray(t_vct start, t_vct rot, bool (*hit_cond)(t_vct))
{
	t_ray	ret;
	t_quad	quad;

	ret.cur_grid = pos_to_grid(start);
	quad = ini_quad(ret.cur_grid);
	ret.axis_dir[X] = ini_vct_pos(sign(rot.x), 0);
	ret.axis_dir[Y] = ini_vct_pos(0, sign(rot.y));
	ret.tar.x = quad.pos[(rot.x > 0) * 3].x;
	ret.tar.y = quad.pos[(rot.y > 0) * 3].y;
	ret.pos = start;
	ret.rot = rot;
	ret.hit_cond = hit_cond;
	return (ret);
}

t_rayhit	ini_hit(t_ray *r, t_axis axis, float m, float b)
{
	t_rayhit	ret;

	ret.sucess = true;
	ret.ray = r->rot;
	ret.axis = axis;
	if (axis == X)
	{
		ret.pos = ini_vct_pos(r->tar.x, ceil(r->tar.x * m + b));
		if (sign(r->axis_dir[X].x) > 0)
			ret.dir = dir_west;
		else
			ret.dir = dir_east;
	}
	else
	{
		if (r->rot.x == 0)
			ini_vct_pos(r->pos.x, r->tar.y);
		else
			ret.pos = ini_vct_pos(ceil((r->tar.y - b) / m), r->tar.y);
		if (sign(r->axis_dir[Y].y) > 0)
			ret.dir = dir_north;
		else
			ret.dir = dir_south;
	}
	return (ret);
}

t_rayhit	ini_miss()
{
	t_rayhit	ret;

	lib_memset(&ret, 0, sizeof(ret));
	return (ret);
}
