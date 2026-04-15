#include "hlp.h"

static void draw(char **map, int x, int y)
{
	t_vct	limit;
	t_vct	cur;
	int		border;

	border = 1;
	if (map[y][x] == '1')
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

static void draw_raycast_quads(t_rayhit hit)
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

void	render_debug_map(t_player *p)
{
	t_vct	v;
	t_vct	h;

	draw_dbg_map();
	draw_circle(p->pos, 5, 0xff0000);
	t_rayhit	hit;
	float		rad;
	int			i;

	i = 0;
	rad = add_rad(player()->rot_rad, -FOV / 2.0);
	while (i < RAYCOUNT)
	{
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_any));
		if (hit.sucess)
		{
			if (i == 0 || i + 1 == RAYCOUNT)
				draw_line(p->pos, hit.pos, 0xff0000);
			draw_raycast_quads(hit);
		}
		rad = add_rad(rad, render()->ray_delta_angle);
		i++;
	}

	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, MOV_SPEED) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
	v = ini_vct_pos(0, p->mov_vct.y * MOV_SPEED);
	h = ini_vct_pos(p->mov_vct.x * MOV_SPEED,0);
	draw_line(p->pos, add_vct(p->pos, v), 0x000000ff);
	draw_line(p->pos, add_vct(p->pos, h ), 0x0000ffff);
}
