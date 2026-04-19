#include "ray.h"

static bool	check_grid(t_ray *ray, t_axis axis, t_rayhit *hit)
{
	ray->cur_axis = axis;
	ray->cur_grid = add_vct(ray->cur_grid, ray->axis_dir[axis]);
	if (!vct_cmp(ray->cur_grid, ray->skip_grid))
	{
		if (ray->hit(ray))
			return (*hit = ini_hit(ray), true);
		if (ray->fail != NULL && ray->fail(ray))
			return (true);
	}
	else
		printf("Skiping grid\n");
	ray->tar = add_vct(ray->tar, scale_vct(ray->axis_dir[axis], GRIDSIZE));
	return (false);
}

static t_rayhit	check_default(t_ray *r)
{
	t_rayhit ret;

	ret = ini_miss();
	while (1)
	{
		if (check_next_x(*r))
		{
			if (check_grid(r, X, &ret))
				break ;
			if (reached_clamp(&r->tar.x, 0, map()->scale.x))
				break ;
		}
		else
		{
			if (check_grid(r, Y, &ret))
				break;
			if (reached_clamp(&r->tar.y, 0, map()->scale.y))
				break ;
		}
	}
	return (ret);
}

static t_rayhit	check_v(t_ray *r)
{
	t_rayhit ret;

	ret = ini_miss();
	while (1)
	{
		if (check_grid(r, Y, &ret))
			return (ini_hit(r));
		if (reached_clamp(&r->tar.y, 0, map()->scale.y))
			break ;
	}
	return (ret);
}

t_rayhit	raycast(t_ray ray, bool (*hit)(t_ray *), bool (*fail)(t_ray *))
{
	ray.cur_axis = get_hit_axis(&ray);
	ray.fail = fail;
	ray.hit = hit;
	if (!vct_cmp(ray.cur_grid, ray.skip_grid))
	{
		if (hit == NULL)
			return (ini_miss());
		if (ray.hit(&ray))
			return (ini_hit_start(&ray));
		if (ray.fail != NULL && ray.fail(&ray))
			return (ini_miss());
	}
	if (ray.rot.x != 0)
		return (check_default(&ray));
	else
		return (check_v(&ray));
}
