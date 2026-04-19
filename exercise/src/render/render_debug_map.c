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

void	render_debug_map(t_player *p)
{
	t_vct	v;
	t_vct	h;

	draw_dbg_map();
	draw_circle(p->pos, 5, 0xff0000);


	t_rayhit	hit;
	float		rad;
	int			i;
	float		cast_pos;
	
	i = 0;
	while (i < RAYCOUNT)
	{
		cast_pos = 2.0 * i / RAYCOUNT - 1.0;
		rad = player()->rot_rad + atan(cast_pos * render()->fov_adj.x);
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_wall, NULL));
		if (hit.sucess)
			draw_line(p->pos, hit.pos, 0xff0000);
		i++;
	}

	i = 0;
	while (i < RAYCOUNT)
	{
		cast_pos = 2.0 * i / RAYCOUNT - 1.0;
		rad = player()->rot_rad + atan(cast_pos * render()->fov_adj.x);
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_door, hit_wall));
		if (hit.sucess)
		{
			t_vct vct;

			if (hit.dir == dir_north)
				vct = ini_vct_pos(0, -1);
			if (hit.dir == dir_south)
				vct = ini_vct_pos(0, 1);
			if (hit.dir == dir_east)
				vct = ini_vct_pos(1, 0);
			if (hit.dir == dir_west)
				vct = ini_vct_pos(-1, 0);
			vct = scale_vct(vct, GRIDSIZE / 2);
			t_vct	pos = add_vct(hit.pos, vct);
			float angle = angle_vct(ini_vct_vct(player()->pos, pos));
			t_rayhit a = raycast(ini_ray(player()->pos, ini_vct_rad(angle), hit_door, hit_wall));
			a.pos = pos;
			if (a.sucess)
				draw_line(p->pos, a.pos, 0x0000ff);
			else
				draw_line(p->pos,  pos, 0x00ff00);

		}
		i++;
	}

	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, MOV_SPEED) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
	v = ini_vct_pos(0, p->mov_vct.y * MOV_SPEED);
	h = ini_vct_pos(p->mov_vct.x * MOV_SPEED,0);
	draw_line(p->pos, add_vct(p->pos, v), 0x000000ff);
	draw_line(p->pos, add_vct(p->pos, h ), 0x0000ffff);
}
