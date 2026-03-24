#include "ray.h"

static bool	check_grid(t_vct *grid_pos, float *tar, t_vct mod, float rad)
{
	float	sign;

	if (rad > 0)
		sign = 1;
	else
		sign = -1;
	*grid_pos = add_vct(*grid_pos, scale_vct(mod, sign));
	if (map()->layout[(int)(*grid_pos).y][(int)(*grid_pos).x] == '1')
		return (true);
	*tar += sign * GRIDSIZE;
	return (false);
}

static t_vct	check_default(t_vct pos, t_vct rad, t_vct tar, t_vct grid)
{
	float	m;
	float	b;

	m = rad.y / rad.x;
	b = pos.y - pos.x * m;
	while (1)
	{
		if (f_abs((tar.x - pos.x) / rad.x) < f_abs((tar.y - pos.y) / rad.y))
		{
			if (check_grid(&grid, &tar.x, ini_vct_pos(1, 0), rad.x))
				return (ini_vct_pos(tar.x, tar.x * m + b));
			if (reached_clamp(&tar.x, 0, render()->window_x))
				break ;
		}
		else
		{
			if (check_grid(&grid, &tar.y, ini_vct_pos(0, 1), rad.y))
				return (ini_vct_pos((tar.y - b) / m, tar.y));
			if (reached_clamp(&tar.y, 0, render()->window_y))
				break ;
		}
	}
	return (ini_vct_pos(-1, -1));
}

static t_vct	check_v(t_vct pos, t_vct rad, t_vct tar, t_vct grid)
{
	while (1)
	{
		if (check_grid(&grid, &tar.y, ini_vct_pos(0, 1), rad.y))
			return (ini_vct_pos(pos.x, tar.y));
		if (reached_clamp(&tar.y, 0, render()->window_y))
			break ;
	}
	return (ini_vct_pos(-1,-1));
}

t_vct	raycast(t_vct pos, t_vct rad)
{
	t_vct	tar;
	t_vct	grid_pos;
	t_quad	quad;

	grid_pos = pos_to_grid(pos);
	quad = ini_quad(grid_pos);
	tar.x = quad.pos[(rad.x > 0) * 3].x;
	tar.y = quad.pos[(rad.y > 0) * 3].y;
	if (rad.x != 0)
		return (check_default(pos, rad, tar, grid_pos));
	else
		return (check_v(pos, rad, tar, grid_pos));
}
