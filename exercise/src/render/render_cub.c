#include "hlp.h"

static void draw_door(t_render *r, t_rayhit *hit, t_draw_ray *d)
{
	t_draw_info	info;

	if (get_map_char(vct_add(hit->grid, ini_vct_dir(hit->dir))) == tile_wall)
		return ;
	info = ini_draw_info(hit, d, &r->door_frame[true]);
	draw_texture(&info);
}

static void draw_wall(t_render *r, t_rayhit *hit, t_draw_ray *dr)
{
	t_frame *f;
	t_draw_info info;

	
	if (hit->c == 'D')
		f = &r->door_frame[0];
	else
		f = &r->wall_frame[hit->dir];
	info = ini_draw_info(hit, dr, f);
	draw_texture(&info);
}

static void	draw_wall_loop(t_render *r, t_draw_ray d)
{
	t_rayhit	h_front;
	t_rayhit	h_back;
	t_ray		ray;

	if (!d.first)
		ray = ini_ray(d.pos_vct, d.dir_vct, &d.last_grid);
	else
		ray = ini_ray(d.pos_vct, d.dir_vct, NULL);
	h_front = raycast(ray, hit_door_open, hit_wall);
	if (h_front.sucess)
	{
		draw_wall_loop(r, update_draw_info(d, h_front));
		h_back = raycast(ray, hit_rnd_backdoor, hit_wall);
		if(h_back.sucess)
			draw_door(r, &h_back, &d);
		draw_door(r, &h_front, &d);
	}
	
	//else
	//{
	//	h_back = raycast(ray, hit_rnd_backdoor, miss_rnd_backdoor);
	//	if(h_back.sucess)
	//		draw_door(r, &h_back, &d);
	//}
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
		draw_wall_loop(r, t);
		i++;
	}
	
}
