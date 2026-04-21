#include "hlp.h"


t_ray	ini_ray(t_vct s, t_vct d, t_vct *skip_grid)
{
	t_ray	ret;
	t_quad	quad;

	ret.check_done = false;
	ret.cur_grid = pos_to_grid(s);
	if (skip_grid != NULL)
		ret.skip_grid = ini_vct_pos(skip_grid->x, skip_grid->y);
	else
		ret.skip_grid = ini_vct_pos(-1, -1);
	quad = ini_quad(ret.cur_grid);
	ret.axis_dir[X] = ini_vct_pos(sign(d.x), 0);
	ret.axis_dir[Y] = ini_vct_pos(0, sign(d.y));
	ret.tar.x = quad.pos[(d.x > 0) * 3].x;
	ret.tar.y = quad.pos[(d.y > 0) * 3].y;
	ret.start_pos = s;
	ret.dir = d;
	ret.hit = NULL;
	ret.fail = NULL;
	ret.m = 0;
	ret.b = 0;
	if (d.x == 0)
		return (ret);
	ret.m = d.y / d.x;
	ret.b = s.y - s.x * ret.m;
	return (ret);
}

void	update_ray_pos(t_ray *r)
{
	if (r->cur_axis == X)
		r->cur_pos = ini_vct_pos(r->tar.x, ceil(r->tar.x * r->m + r->b));
	else
	{
		if (r->dir.x == 0)
			r->cur_pos = ini_vct_pos(r->start_pos.x, r->tar.y);
		else
			r->cur_pos = ini_vct_pos(ceil((r->tar.y - r->b) / r->m), r->tar.y);
	}
}



t_rayhit	ini_hit(t_ray *r)
{
	t_dir		dir;
	
	if (r->cur_axis == X)
		dir = 2 + (sign(r->axis_dir[X].x) < 0);
	else
		dir = sign(r->axis_dir[Y].y) > 0;
	return (ret_hit(r, dir));
}
t_rayhit	ini_hit_start(t_ray *r)
{
	t_dir	dir;

	update_ray_pos(r);
	if (r->cur_axis == X)
		dir = 2 + (sign(r->axis_dir[X].x) < 0);
	else
		dir = sign(r->axis_dir[Y].y) > 0;
	return (ret_hit_start(r, dir));
}

t_rayhit	ini_miss()
{
	t_rayhit	ret;

	lib_memset(&ret, 0, sizeof(ret));
	ret.pos = ini_vct_pos(-1, -1);
	return (ret);
}
