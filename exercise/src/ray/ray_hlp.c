#include "hlp.h"

t_vct	grid_distance(t_vct pos)
{
	t_vct ret;

	ret.x = GRIDSIZE - (int)floor(pos.x) % GRIDSIZE;
	ret.y = GRIDSIZE - (int)floor(pos.y) % GRIDSIZE;
	return (ret);
}

t_vct	pos_to_grid(t_vct pos)
{
	t_vct	ret;

	ret.x = clamp(((int)floor(pos.x)) / GRIDSIZE, 0, map()->len_x);
	ret.y = clamp(((int)floor(pos.y)) / GRIDSIZE, 0, map()->len_y);
	return (ret);
}

t_vct	grid_to_pos(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x * GRIDSIZE + GRIDSIZE / 2;
	ret.y = pos.y * GRIDSIZE + GRIDSIZE / 2;
	return (ret);
}

bool	check_next_x(t_ray r)
{
	float	x_dist;
	float	y_dist;
	
	x_dist = f_abs((r.tar.x - r.start_pos.x) / r.dir.x);
	y_dist = f_abs((r.tar.y - r.start_pos.y) / r.dir.y);
	return (x_dist < y_dist);
}