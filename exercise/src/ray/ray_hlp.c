#include "ray.h"

t_vct	grid_distance(t_vct pos, t_vct rot)
{
	t_vct ret;

	ret.x = (rot.x > 0) * GRIDSIZE - (int)floor(pos.x) % GRIDSIZE ;
	ret.y = (rot.y > 0) * GRIDSIZE - (int)floor(pos.y) % GRIDSIZE ;
	return (ret);
}

t_vct	pos_to_grid(t_vct pos)
{
	t_vct	ret;

	ret.x = clamp(((int)floor(pos.x)) / GRIDSIZE, 0, map()->size_x);
	ret.y = clamp(((int)floor(pos.y)) / GRIDSIZE, 0, map()->size_y);
	return (ret);
}

t_vct	grid_to_pos(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x * GRIDSIZE + GRIDSIZE / 2;
	ret.y = pos.y * GRIDSIZE + GRIDSIZE / 2;
	return (ret);
}