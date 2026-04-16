#include "ray.h"

t_ray	ini_ray(t_vct s, t_vct rot, bool (*hit)(t_vct), bool (*fail)(t_vct))
{
	t_ray	ret;
	t_quad	quad;

	ret.cur_grid = pos_to_grid(s);
	quad = ini_quad(ret.cur_grid);
	ret.axis_dir[X] = ini_vct_pos(sign(rot.x), 0);
	ret.axis_dir[Y] = ini_vct_pos(0, sign(rot.y));
	ret.tar.x = quad.pos[(rot.x > 0) * 3].x;
	ret.tar.y = quad.pos[(rot.y > 0) * 3].y;
	ret.pos = s;
	ret.rot = rot;
	ret.hit = hit;
	ret.fail = fail;
	ret.m = 0;
	ret.b = 0;
	if (rot.x != 0)
	{
		ret.m = rot.y / rot.x;
		ret.b = s.y - s.x * ret.m;
	}
	return (ret);
}

static t_rayhit	ret_hit(t_ray *r, t_vct pos, t_axis axis, t_dir dir)
{
	t_rayhit	ret;

	ret.sucess = true;
	ret.axis = axis;
	ret.dir = dir;
	ret.pos = pos;
	ret.ray = r->rot;
	ret.grid = pos_to_grid(pos);
	if (dir == dir_west)
		ret.grid = add_vct(ret.grid, ini_vct_pos(-1, 0));
	else if (dir == dir_north)
		ret.grid = add_vct(ret.grid, ini_vct_pos(0, -1));
	ret.c = get_map_char(ret.grid);
	return (ret);
}

t_rayhit	ini_hit(t_ray *r, t_axis axis)
{
	t_vct		pos;
	t_dir		dir;

	if (axis == X)
	{
		pos = ini_vct_pos(r->tar.x, ceil(r->tar.x * r->m + r->b));
		if (sign(r->axis_dir[X].x) < 0)
			dir = dir_west;
		else
			dir = dir_east;
	}
	else
	{
		if (r->rot.x == 0)
			pos = ini_vct_pos(r->pos.x, r->tar.y);
		else
			pos = ini_vct_pos(ceil((r->tar.y - r->b) / r->m), r->tar.y);
		if (sign(r->axis_dir[Y].y) < 0)
			dir = dir_north;
		else
			dir = dir_south;
	}
	return (ret_hit(r, pos, axis, dir));
}

t_rayhit	ini_miss()
{
	t_rayhit	ret;

	lib_memset(&ret, 0, sizeof(ret));
	return (ret);
}
