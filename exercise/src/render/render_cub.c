#include "hlp.h"

static void draw(t_rayhit hit, int i, float rad)
{
	float	dist;
	float	size_y;
	t_vct	center;
	t_vct	sq_size;

	dist = dist_vct(player()->pos, hit.pos) * cos(add_rad(rad, -player()->rot_rad));
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
		draw_wall(center, sq_size, (int)hit.pos.y, &render()->test_img);
	else
		draw_wall(center, sq_size, (int)hit.pos.x, &render()->test_img);
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
			draw(hit, i,rad);
		rad = add_rad(rad, render()->ray_delta_angle);
		i++;
	}
}