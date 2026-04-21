#include "ray.h"

t_ray	ini_ray(t_vct s, t_vct rot, t_vct *skip_grid)
{
	t_ray	ret;
	t_quad	quad;

	ret.cur_grid = pos_to_grid(s);
	if (skip_grid != NULL)
		ret.skip_grid = ini_vct_pos(skip_grid->x, skip_grid->y);
	else
		ret.skip_grid = ini_vct_pos(-1, -1);
	quad = ini_quad(ret.cur_grid);
	ret.axis_dir[X] = ini_vct_pos(sign(rot.x), 0);
	ret.axis_dir[Y] = ini_vct_pos(0, sign(rot.y));
	ret.tar.x = quad.pos[(rot.x > 0) * 3].x;
	ret.tar.y = quad.pos[(rot.y > 0) * 3].y;
	ret.start = s;
	ret.rot = rot;
	ret.hit = NULL;
	ret.fail = NULL;
	ret.m = 0;
	ret.b = 0;
	if (rot.x == 0)
		return (ret);
	ret.m = rot.y / rot.x;
	ret.b = s.y - s.x * ret.m;
	return (ret);
}



t_rayhit	ini_hit(t_ray *r)
{
	t_vct		pos;
	t_dir		dir;
	
	if (r->cur_axis == X)
	{
		pos = ini_vct_pos(r->tar.x, ceil(r->tar.x * r->m + r->b));
		dir = 2 + (sign(r->axis_dir[X].x) < 0);
	}
	else
	{
		if (r->rot.x == 0)
			pos = ini_vct_pos(r->start.x, r->tar.y);
		else
			pos = ini_vct_pos(ceil((r->tar.y - r->b) / r->m), r->tar.y);
		dir = sign(r->axis_dir[Y].y) > 0;
	}
	return (ret_hit(r, pos, dir));
}
t_rayhit	ini_hit_start(t_ray *r)
{
	t_vct	pos;
	t_dir	dir;

	if (r->cur_axis == X)
	{
		pos = ini_vct_pos(r->tar.x, ceil(r->tar.x * r->m + r->b));
		dir = 2 + (sign(r->axis_dir[X].x) < 0);
	}
	else
	{
		if (r->rot.x == 0)
			pos = ini_vct_pos(r->start.x, r->tar.y);
		else
		{
			pos = ini_vct_pos(ceil((r->tar.y - r->b) / r->m), r->tar.y);
			dir = sign(r->axis_dir[Y].y) > 0;
		}
	}
	return (ret_hit_start(r, pos, dir));
}

t_rayhit	ini_miss()
{
	t_rayhit	ret;

	lib_memset(&ret, 0, sizeof(ret));
	return (ret);
}
