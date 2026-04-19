#include "hlp.h"

typedef	struct s_draw_info
{
	t_frame	*f;
	t_vct	center;
	t_vct	sq_size;
	float	dist;
	float	size_y;
	int		x;
}	t_draw_info;

static t_vct set_limit(t_vct i[2], t_vct center, t_vct size)
{
	t_vct	ret;

	i[1] = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	i[0] = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	ret.x = i[1].y - i[0].y;
	if(i[1].y < 0)
		ret.y = -i[1].y;
	else
		ret.y = 0;
	i[0].x = clamp(i[0].x, 0, WINDOW_X - 1);
	i[0].y = clamp(i[0].y, 0, WINDOW_Y - 1);
	i[1].x = clamp(i[1].x, 0, WINDOW_X - 1);
	i[1].y = clamp(i[1].y, 0, WINDOW_Y - 1);
	return ret;
}

static int	get_color(int x, t_vct i[2], t_vct adjust, t_frame *f)
{
	char	*dst;
	float	y;

	y = (i[1].y - i[0].y - adjust.y) /adjust.x;
	dst = f->addr + (int)(y * (float)GRIDSIZE) * f->line_len + (x % GRIDSIZE) * f->byte_pixel;
	return (*(unsigned int *)dst);
}

static void	draw(t_draw_info *d)
{
	t_vct	i[2];
	t_vct	pivot;
	t_vct	adjst;
	t_frame	*f;

	adjst = set_limit(i, d->center, d->sq_size);
	f = &render()->frame_buff[render()->frame_cur];
	pivot.x = i[0].x;
	while (i[0].y > i[1].y)
	{
		i[0].x = pivot.x;
		pivot.y = (int)i[0].y * f->line_len;
		while (i[0].x > i[1].x)
		{
			set_pixel_add(f, i[0].x, pivot.y, get_color(d->x, i, adjst, d->f));
			i[0].x--;
		}
		i[0].y--;
	}
}



t_draw_info	ini_draw_info(t_rayhit *hit, int i, float cos_adj, t_frame *f)
{
	t_draw_info	ret;
	t_render	*r;
	t_player	*p;

	r = render();
	p = player();
	ret.f = f;
	ret.dist = dist_vct(p->pos, hit->pos) * cos_adj;
	ret.size_y = (r->fov_adj.y * (float)GRIDSIZE) / ret.dist;
	ret.center = ini_vct_pos(r->ray_width / 2 + i * r->ray_width, WINDOW_Y / 2);
	ret.center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	ret.sq_size = ini_vct_pos(r->ray_width, ret.size_y);
	if (hit->axis == X)
		ret.x = (int)hit->pos.y;
	else
		ret.x = (int)hit->pos.x;
	return (ret);
}


void draw_door(t_rayhit *hit, int i, float cos_adj, bool force)
{
	t_draw_info	info;
	bool		open;
	if (!force)
	{
		open = door_get_state(hit->grid);
		if (get_map_char(add_vct(hit->grid, ini_vct_dir(hit->dir))) == '1')
			return ;
	}
	else
		open = true;
	info = ini_draw_info(hit, i, cos_adj, &render()->door_frame[open]);
	draw(&info);
}
static void draw_wall(t_rayhit *hit, int i, float cos_adj)
{
	t_draw_info info;

	info = ini_draw_info(hit, i, cos_adj, &render()->wall_frame[hit->dir]);
	draw(&info);
}

void render_cub(void)
{
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
		cos_adjust = cos(add_rad(rad, -player()->rot_rad));
		rad = player()->rot_rad + atan(cast_pos * render()->fov_adj.x);
		rad_vct = ini_vct_rad(rad);
		hit = raycast(ini_ray(player()->pos, rad_vct, hit_wall, NULL));
		if (hit.sucess)
			draw_wall(&hit, i, cos_adjust);
		hit = raycast(ini_ray(player()->pos, rad_vct, hit_door_back, hit_any));
		if (hit.sucess)
			draw_door(&hit, i, cos_adjust, true);
		hit = raycast(ini_ray(player()->pos, rad_vct, hit_door, hit_wall));
		if (hit.sucess)
			draw_door(&hit, i, cos_adjust, false);
		i++;
	}
	
}
