#include "ray.h"

t_rayhit	ret_hit(t_ray *r, t_vct pos, t_axis axis, t_dir dir)
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


t_rayhit	ret_hit_start(t_ray *r, t_vct pos, t_axis axis, t_dir dir)
{
	t_rayhit	ret;

	ret.sucess = true;
	ret.axis = axis;
	ret.dir = dir;
	ret.pos = pos;
	ret.ray = r->rot;
	ret.grid = pos_to_grid(r->pos);
	ret.c = get_map_char(ret.grid);
	return (ret);
}
t_axis	get_hit_axis(t_ray *r)
{
	float x;
	float y;

	x = f_abs((r->tar.x - r->pos.x) / r->rot.x);
	y = f_abs((r->tar.y - r->pos.y) / r->rot.y);
	return (x > y);
}