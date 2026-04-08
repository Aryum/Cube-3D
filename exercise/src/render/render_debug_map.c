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

static void draw_raycast_quads(t_player *p, t_vct v, t_vct h)
{
	t_quad	p_quad;
	t_quad	v_quad;
	t_quad	h_quad;

	p_quad = ini_quad(pos_to_grid(p->pos));
	v_quad = ini_quad(pos_to_grid(add_vct(p->pos, v)));
	h_quad = ini_quad(pos_to_grid(add_vct(p->pos, h)));
	draw_quad(p_quad, 0x00ff00ff);
	if (v_quad.grid.y != p_quad.grid.y)
		draw_quad(v_quad, 0x000000ff);
	if ( h_quad.grid.x != p_quad.grid.x )
		draw_quad(h_quad, 0x0000ffff);
}

void	render_debug_map(t_player *p)
{
	t_vct	v;
	t_vct	h;

	draw_dbg_map();
	draw_circle(p->pos, 5, 0xff0000);

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
			draw_line(p->pos, hit.pos, 0xff0000);
		cur += render()->fov_delta;
		i++;
	}

	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, MOV_SPEED) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
	v = ini_vct_pos(0, p->mov_vct.y * MOV_SPEED);
	h = ini_vct_pos(p->mov_vct.x * MOV_SPEED,0);
	draw_line(p->pos, add_vct(p->pos, v), 0x000000ff);
	draw_line(p->pos, add_vct(p->pos, h ), 0x0000ffff);
	draw_raycast_quads(p, v, h);
}