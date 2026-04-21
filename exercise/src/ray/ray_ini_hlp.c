#include "hlp.h"

t_rayhit	ret_hit(t_ray *r, t_dir dir)
{
	t_rayhit	ret;

	ret.sucess = true;
	ret.axis = r->cur_axis;
	ret.dir = dir;
	ret.pos = r->cur_pos;
	ret.ray = r->dir;
	ret.grid = r->cur_grid;
	ret.c = get_map_char(r->cur_grid);
	return (ret);
}


t_rayhit	ret_hit_start(t_ray *r, t_dir dir)
{
	t_rayhit	ret;

	ret.sucess = true;
	ret.axis = r->cur_axis;
	ret.dir = dir;
	ret.pos = r->cur_pos;
	ret.ray = r->dir;
	ret.grid = r->cur_grid;
	ret.c = get_map_char(ret.grid);
	return (ret);
}

t_axis	get_hit_axis(t_ray *r)
{
	float x;
	float y;

	x = f_abs((r->tar.x - r->start_pos.x) / r->dir.x);
	y = f_abs((r->tar.y - r->start_pos.y) / r->dir.y);
	return (x > y);
}

