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


t_recuse	ini_recuse(t_vct pos, t_vct rad, int i, float cos_adjust)
{
	t_recuse	ret;

	ret.pos = pos;
	ret.rad = rad;
	ret.i = i;
	ret.cos_adjust = cos_adjust;
	ret.last_grid = ini_vct_pos(-1, -1);
	ret.first = true;
	return (ret);
}
void	fuck(t_recuse info, bool (*check)(t_ray *))
{
	t_rayhit	hit;
	t_ray		ray;

	if (!info.first)
		ray = ini_ray(info.pos, info.rad, &info.last_grid);
	else
		ray = ini_ray(info.pos, info.rad, NULL);
	hit = raycast(ray, check, hit_wall);
	if (hit.sucess && !vct_cmp(hit.grid, info.last_grid))
	{
		info.last_grid = hit.grid;
		info.first = false;
		info.pos = hit.pos;
		fuck(info, check);
		set_pixel_pos(hit.pos.x, hit.pos.y, 0x0000ff);
	}
}

void	render_debug_map(t_player *p)
{

	draw_dbg_map();
	draw_circle(p->pos, 5, 0xff0000);

	t_rayhit	hit;
	t_vct		rad_vct;
	float		rad;
	int			i;
	float		cast_pos;
	float		cos_adjust;


	i = 0;

	while (i < RAYCOUNT)
	{
		cast_pos = 2.0 * i / RAYCOUNT - 1.0;
		rad = player()->rot_rad + atan(cast_pos * render()->fov_adj.x);
		cos_adjust = cos(add_rad(rad, -player()->rot_rad));
		rad_vct = ini_vct_rad(rad);
		hit = raycast(ini_ray(player()->pos, rad_vct, NULL), hit_wall, NULL);
		if (hit.sucess && (i == 0 || i+ 1 == RAYCOUNT ))
			draw_line(player()->pos, hit.pos, 0xff0000);
		t_recuse t = ini_recuse(player()->pos, rad_vct, i, cos_adjust);
		fuck(t, hit_door_back);
		fuck(t, hit_door);

		i++;
	}
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, MOV_SPEED) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
}
