#include "hlp.h"

static void draw(t_tile **map, int x, int y)
{
	t_vct	limit;
	t_vct	cur;
	int		border;

	border = 1;
	if (map[y][x].val == '1')
	{
		cur.x = x * GRIDSIZE + border;
		cur.y = y * GRIDSIZE + border;
		limit.x = cur.x + GRIDSIZE - border;
		limit.y = cur.y + GRIDSIZE - border;
		while (cur.y < limit.y)
		{
			cur.x = x * GRIDSIZE + border;
			while (cur.x < limit.x)
			{
				set_pixel_pos(cur.x, cur.y, 0xffffff);
				cur.x++;
			}
			cur.y++;
		}
	}
}

static void	draw_dbg_map(void)
{
	t_map	*m;
	int		x;
	int		y;

	y = 0;
	m = map();
	while (y < m->len_y)
	{
		x = 0;
		while (x < m->len_x)
		{
			draw(m->layout, x, y);
			x++;
		}
		y++;
	}
}

void draw_raycast_quads(t_rayhit hit)
{
	int color;

	if (hit.dir == dir_north)
		color = 0x51A3A3; //blue 
	else if (hit.dir == dir_south)
		color = 0x75485E; //purple
	else if (hit.dir == dir_east)
		color = 0xCB904D; //orange
	else
		color = 0xC3E991; //greeen
	draw_quad(ini_quad(hit.grid), color);
}

void	recursive_dbg(t_render *r, t_draw_ray d, int loop)
{
	t_rayhit	hit;
	t_ray		ray;

	if (!d.first)
		ray = ini_ray(d.pos_vct, d.dir_vct, &d.last_grid);
	else
		ray = ini_ray(d.pos_vct, d.dir_vct, NULL);
	hit = raycast(ray, hit_door_open, hit_wall);
	if (hit.sucess && !vct_cmp(d.last_grid, hit.grid))
	{
		recursive_dbg(r, update_draw_info(d, hit), loop + 1);
		ray = ini_ray(hit.pos, vct_scale(ray.dir, -1), NULL);
		if (!raycast(ray, hit_wall, NULL).sucess)
			set_pixel_pos(hit.pos.x, hit.pos.y, 0x00ff00);
		else
			set_pixel_pos(hit.pos.x, hit.pos.y, 0x0000ff);
	}
}

void	render_debug_map(t_player *p)
{

	draw_dbg_map();
	//draw_circle(p->pos, 5, 0xff0000);

	t_draw_ray t;

	t_rayhit	hit;
	int i;


	i = 0;

	while (i < RAYCOUNT)
	{
		t = ini_draw_ray(i);
		recursive_dbg(render(), t, 0);
		hit = raycast(ini_ray(p->pos, t.dir_vct, NULL), hit_wall, NULL);
		if (hit.sucess )
		{
			if(i == 0)
				draw_line(p->pos, hit.pos, 0xff0000);
			else if(i == RAYCOUNT / 2)
				draw_line(p->pos, hit.pos, 0x00ff00);
			if(i+ 1 == RAYCOUNT)
				draw_line(p->pos, hit.pos, 0x0000ff);
		}
		i++;
	}
	draw_line(p->pos, vct_add(p->pos, vct_scale(p->rot_vct, MOV_SPEED) ), 0xfffb00);
	draw_line(p->pos, vct_add(p->pos, vct_scale(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
}
