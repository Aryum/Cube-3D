#include "hlp.h"


static int set_limit(t_vct i[2], t_vct center, t_vct size)
{
	float	ret;

	i[1] = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	i[0] = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	ret = i[1].y - i[0].y;
	i[0].x = clamp(i[0].x, 0, WINDOW_X - 1);
	i[0].y = clamp(i[0].y, 0, WINDOW_Y - 1);
	i[1].x = clamp(i[1].x, 0, WINDOW_X - 1);
	i[1].y = clamp(i[1].y, 0, WINDOW_Y - 1);
	return ret;
}

static int	get_color(int x, float y, t_frame *f)
{
	char	*dst;

	dst = f->addr + (int)(y * (float)GRIDSIZE) * f->line_len + (x % GRIDSIZE) * f->byte_pixel;
	return (*(unsigned int *)dst);
}

static void	draw(t_vct center, t_vct size, int x, t_frame *texture)
{
	t_vct	i[2];
	t_vct	pivot;
	float	total;
	t_frame	*f;

	total = set_limit(i, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	pivot.x = i[0].x;
	while (i[0].y > i[1].y)
	{
		i[0].x = pivot.x;
		pivot.y = (int)i[0].y * f->line_len;
		while (i[0].x > i[1].x)
		{
			set_pixel_pos(i[0].x, i[0].y, get_color(x - 1, (i[1].y - i[0].y) / (total), texture));
			i[0].x--;
		}
		i[0].y--;
	}
}

static void draw_wall(t_rayhit hit, int i)
{
	float	dist;
	float	size_y;
	t_vct	center;
	t_vct	sq_size;

	if (hit.axis == X)
		dist = f_abs((hit.pos.x - player()->pos.x) / hit.ray.x) ;
	else
		dist = f_abs((hit.pos.y - player()->pos.y) / hit.ray.y) ;
	size_y = (render()->fov_v_adjust * GRIDSIZE) / dist;
	center = ini_vct_pos(render()->ray_width / 2 + i * render()->ray_width, WINDOW_Y / 2);
	center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	sq_size = ini_vct_pos(render()->ray_width, size_y);

	//int		color[4];
	//color[dir_east] = 0x00ff0000;
	//color[dir_west] = 0x000000ff;
	//color[dir_north] = 0x00ff00ff;
	//color[dir_south] = 0x0000ff00;
	//draw_square(center, sq_size, color[hit.dir]);
	//return;

	if (hit.axis == X)
		draw(center, sq_size, (int)hit.pos.y, &render()->test_img);
	else
		draw(center, sq_size, (int)hit.pos.x, &render()->test_img);
}

void render_cub(void)
{
	t_rayhit	hit;
	float		rad;
	int			i;

	i = 0;
	rad = add_rad(player()->rot_rad, -FOV / 2.0);
	while (i < RAYCOUNT)
	{
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_wall));
		if (hit.sucess)
			draw_wall(hit, i);
		rad = add_rad(rad, render()->ray_delta_angle);
		i++;
	}
}