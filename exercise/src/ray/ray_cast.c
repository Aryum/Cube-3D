#include "ray.h"

static bool	check_grid(t_ray *ray, t_axis axis)
{
	ray->cur_grid = add_vct(ray->cur_grid, ray->axis_dir[axis]);
	if (ray->hit_cond(ray->cur_grid))
		return (true);
	ray->tar = add_vct(ray->tar, scale_vct(ray->axis_dir[axis], GRIDSIZE));
	return (false);
}

static t_rayhit	check_default(t_ray *r)
{
	float	m;
	float	b;

	m = r->rot.y / r->rot.x;
	b = r->pos.y - r->pos.x * m;
	while (1)
	{
		if (check_next_x(*r))
		{
			if (check_grid(r, X))
				return (ini_hit(r, X, m, b));
			if (reached_clamp(&r->tar.x, 0, map()->scale.x))
				break ;
		}
		else
		{
			if (check_grid(r, Y))
				return (ini_hit(r, Y, m, b));
			if (reached_clamp(&r->tar.y, 0, map()->scale.y))
				break ;
		}
	}
	return (ini_miss());
}

static t_rayhit	check_v(t_ray *r)
{
	while (1)
	{
		if (check_grid(r, Y))
			return (ini_hit(r, Y, 0, 0));
		if (reached_clamp(&r->tar.y, 0, map()->scale.y))
			break ;
	}
	return (ini_miss());
}

t_rayhit	raycast(t_ray ray)
{
	if (ray.rot.x != 0)
		return (check_default(&ray));
	else
		return (check_v(&ray));
}
