#include "hlp.h"

static void draw(t_rayhit hit, float rad,int i)
{
	//int		color[4];
	float	dist;
	float	size_y;
	t_vct	center;
	t_vct	sq_size;

	dist = dist_vct(player()->pos, hit.pos) * cos(player()->rot_rad - rad);
	size_y = (float)(WINDOW_Y * GRIDSIZE) / dist;
	center = ini_vct_pos(i * render()->resolution, WINDOW_Y / 2);
	center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	sq_size = ini_vct_pos(render()->resolution, size_y);
	//color[dir_east] = 0x00ff0000;
	//color[dir_west] = 0x000000ff;
	//color[dir_north] = 0x00ff00ff;
	//color[dir_south] = 0x0000ff00;
	if (hit.axis == X)
		draw_wall(center, sq_size, (int)hit.pos.y, &render()->test_img);
	else
		draw_wall(center, sq_size, (int)hit.pos.x, &render()->test_img);
}

void render_cub(void)
{
	t_rayhit	hit;
	float		cur;
	float		tar;
	float		rad;
	int			i;

	cur = -render()->fov_tar;
	tar = render()->fov_tar;
	i = 0;
	while (cur <= tar)
	{
		rad = add_rad(player()->rot_rad, cur);
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_wall));
		if (hit.sucess)
			draw(hit, rad, i);
		cur += render()->fov_delta;
		i++;
	}
}