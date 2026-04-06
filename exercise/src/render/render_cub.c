#include "hlp.h"

static void draw(t_rayhit hit)
{
	float dist = dist_vct(p->pos, hit.pos) * cos(add_rad(p->rot_rad, -rad));
	float size = render()->window_y * GRIDSIZE / dist;
	t_vct center = ini_vct_pos(a * rnd->window_x /div , rnd->window_y / 2);
	center.y += sin(p->tilt) * (float)(rnd->window_y / 2);
	t_vct sq_size = ini_vct_pos(rnd->window_x / div , size);
	int color[4];
	color[dir_east] = 0x00ff0000;
	color[dir_west] = 0x000000ff;
	color[dir_north] = 0x00ff00ff;
	color[dir_south] = 0x0000ff00;
	draw_square(center, sq_size, color[hit.dir]);
}

static void cast(t_player *p, int i, float rad)
{
	float rad = add_rad(p->rot_rad, i * fov / 2);
	t_ray ray =  ini_ray(p->pos, ini_vct_rad(rad), hit_wall);
	t_rayhit hit = raycast(ray);
	if (hit.sucess)
	{
		draw()
		//float angle = add_rad(p->rot_rad, i);
		float dist = dist_vct(p->pos, hit.pos) * cos(add_rad(p->rot_rad, -rad));
		float size = render()->window_y * GRIDSIZE / dist;
		t_vct center = ini_vct_pos(a * rnd->window_x /div , rnd->window_y / 2);
		center.y += sin(p->tilt) * (float)(rnd->window_y / 2);
		t_vct sq_size = ini_vct_pos(rnd->window_x / div , size);
		int color[4];
		color[dir_east] = 0x00ff0000;
		color[dir_west] = 0x000000ff;
		color[dir_north] = 0x00ff00ff;
		color[dir_south] = 0x0000ff00;
		draw_square(center, sq_size, color[hit.dir]);
	}

}
void render_cub()
{
	float	i;
	float	tar;
	float	rad;
	tar = FOV / 2;
	i = -tar;
	while (i < tar)
	{
		rad = add_rad(player()->rot_rad, i * tar);
		i+=  render()->fov_delta;
	}
	/*
	//quad based raycast
		int a = 0;
		for (float i = -fov / 2 ; i < fov / 2; i+=delta)
		{
			float rad = add_rad(p->rot_rad, i * fov / 2);
			t_ray ray =  ini_ray(p->pos, ini_vct_rad(rad), hit_wall);
			t_rayhit hit = raycast(ray);
			if (hit.sucess)
			{
				//float angle = add_rad(p->rot_rad, i);
				float dist = dist_vct(p->pos, hit.pos) * cos(add_rad(p->rot_rad, -rad));
				float size = render()->window_y * GRIDSIZE / dist;
				t_vct center = ini_vct_pos(a * rnd->window_x /div , rnd->window_y / 2);
				center.y += sin(p->tilt) * (float)(rnd->window_y / 2);
				t_vct sq_size = ini_vct_pos(rnd->window_x / div , size);
				int color[4];
				color[dir_east] = 0x00ff0000;
				color[dir_west] = 0x000000ff;
				color[dir_north] = 0x00ff00ff;
				color[dir_south] = 0x0000ff00;
				draw_square(center, sq_size, color[hit.dir]);
			}
			a++;
		}
		*/
}
