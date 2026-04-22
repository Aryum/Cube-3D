#include "hlp.h"

static void draw_door(t_render *r, t_rayhit hit, t_draw_ray *d)
{
	t_draw_info	info;

	if (get_map_char(vct_add(hit.grid, ini_vct_dir(hit.dir))) == tile_wall)
		return ;
	info = ini_draw_info(hit, d, &r->door_frame[true]);
	draw_texture(&info);
}

static void draw_wall(t_render *r, t_rayhit hit, t_draw_ray *dr)
{
	t_frame *f;
	t_draw_info info;

	
	if (hit.c == 'D')
		f = &r->door_frame[0];
	else
		f = &r->wall_frame[hit.dir];
	info = ini_draw_info(hit, dr, f);
	draw_texture(&info);
}


static void	draw_back(t_render *r, t_rayhit last_hit, t_ray ray, t_draw_ray d)
{
	t_rayhit	hit;
	t_vct		dir;
	t_vct		pos;

	dir = ini_vct_dir(last_hit.dir);
	if (get_map_char(vct_add(last_hit.grid, dir)) == tile_empty )
	{
		dir = vct_add(last_hit.pos, vct_scale(dir, GRIDSIZE));
		pos = calculate_ray_pos(ray, last_hit.axis, dir);
		hit = raycast(ini_ray(pos, vct_scale(ray.dir, -1), NULL), hit_player, hit_wall );
		if (hit.sucess)
		{
			hit.pos = pos;
			hit.axis = last_hit.axis;
			draw_door(r, hit, &d);
		}
	}
}

void	draw_wall_loop(t_render *r, t_draw_ray d)
{
	t_rayhit	hit;
	t_ray		ray;

	if (!d.first)
		ray = ini_ray(d.pos_vct, d.dir_vct, &d.last_grid);
	else
		ray = ini_ray(d.pos_vct, d.dir_vct, NULL);
	hit = raycast(ray, hit_door_open, hit_wall);
	if (hit.sucess && !vct_cmp(d.pos_vct, hit.pos))
	{
		draw_wall_loop(r, update_draw_info(d, hit));
		if (!vct_cmp(hit.grid, player()->grid))
			draw_back(r, hit, ray, d);
		draw_door(r, hit, &d);
	}
}


void render_cub(t_player *p, t_render *r)
{
	t_draw_ray	t;
	t_rayhit	hit;
	int			i;

	i = 0;
	while (i < RAYCOUNT)
	{
		t = ini_draw_ray(i);
		hit = raycast(ini_ray(p->pos, t.dir_vct, NULL), hit_wall, NULL);
		if (hit.sucess)
			draw_wall(r, hit, &t);
		draw_wall_loop(r, t);
		i++;
	}
	
}
