#include "ray.h"

static bool	check_grid(t_ray *ray, t_axis axis)
{
	t_vct	mod;
	float	sign;
	float	rot;
	float	*tar;

	if (axis == axis_x)
	{
		rot = ray->rot.x;
		tar = &ray->tar.x;
		mod = ini_vct_pos(1, 0);
	}
	else
	{
		rot = ray->rot.y; 
		tar = &ray->tar.y;
		mod = ini_vct_pos(0, 1);
	}
	if (rot > 0)
		sign = 1;
	else
		sign = -1;
	ray->cur_grid = add_vct(ray->cur_grid, scale_vct(mod, sign));
	if (ray->hit_cond(ray->cur_grid))
		return (true);
	return (*tar += sign * GRIDSIZE, false);
}

static t_vct	check_default(t_ray *r)
{
	float	m;
	float	b;

	m = r->rot.y / r->rot.x;
	b = r->pos.y - r->pos.x * m;
	while (1)
	{
		if (check_next_x(*r))
		{
			if (check_grid(r, axis_x))
				return (ini_vct_pos(r->tar.x, r->tar.x * m + b));
			if (reached_clamp(&r->tar.x, 0, render()->window_x))
				break ;
		}
		else
		{
			if (check_grid(r, axis_y))
				return (ini_vct_pos((r->tar.y - b) / m, r->tar.y));
			if (reached_clamp(&r->tar.y, 0, render()->window_y))
				break ;
		}
	}
	return (ini_vct_pos(-1, -1));
}

static t_vct	check_v(t_ray *r)
{
	while (1)
	{
		if (check_grid(r, axis_y))
			return (ini_vct_pos(r->pos.x, r->tar.y));
		if (reached_clamp(&r->tar.y, 0, render()->window_y))
			break ;
	}
	return (ini_vct_pos(-1,-1));
}

t_vct	raycast(t_ray ray)
{
	if (ray.rot.x != 0)
		return (check_default(&ray));
	else
		return (check_v(&ray));
}
