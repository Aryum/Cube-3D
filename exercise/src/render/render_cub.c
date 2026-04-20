#include "hlp.h"

static void draw_door(t_render *r, t_rayhit *hit, t_draw_ray *d)
{
	t_draw_info	info;

	if (get_map_char(add_vct(hit->grid, ini_vct_dir(hit->dir))) != '0')
		return;
	info = ini_draw_info(hit, d, &r->door_frame[true]);
	draw_texture(&info);
}

static void draw_wall(t_render *r, t_rayhit *hit, t_draw_ray *d)
{
	t_frame *f;
	t_draw_info info;

	
	if (hit->c == 'D')
		f = &r->door_frame[0];
	else
		f = &r->wall_frame[hit->dir];
	info = ini_draw_info(hit, d, f);
	draw_texture(&info);
}

static void	draw_wall_loop(t_render *r, t_draw_ray *d)
{
	t_rayhit	h_front;
	t_rayhit	h_back;

	t_ray		ray;

	if (!d->first)
		ray = ini_ray(d->pos_vct, d->dir_vct, &d->last_grid);
	else
		ray = ini_ray(d->pos_vct, d->dir_vct, NULL);
	h_front = raycast(ray, hit_door_open, hit_wall);
	if (h_front.sucess && !vct_cmp(h_front.grid, d->last_grid))
	{
		d->last_grid = h_front.grid;
		d->first = false;
		d->pos_vct = h_front.pos;
		draw_wall_loop(r, d);
		h_back = raycast(ray, hit_door_back, hit_wall);
		if(h_back.sucess)
			draw_door(r, &h_back, d);
		draw_door(r, &h_front, d);
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
			draw_wall(r, &hit, &t);
		draw_wall_loop(r, &t);
		i++;
	}
	
}
