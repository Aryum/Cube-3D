#include "hlp.h"


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

static void	draw(t_vct center, t_vct size, int x, t_frame *texture)
{
	t_vct	i[2];
	t_vct	pivot;
	t_vct	adjst;
	t_frame	*f;

	adjst = set_limit(i, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	pivot.x = i[0].x;
	while (i[0].y > i[1].y)
	{
		i[0].x = pivot.x;
		pivot.y = (int)i[0].y * f->line_len;
		while (i[0].x > i[1].x)
		{
			set_pixel_pos(i[0].x, i[0].y, get_color(x, i, adjst, texture));
			i[0].x--;
		}
		i[0].y--;
	}
}

typedef	struct s_draw_info
{
	t_vct	center;
	t_vct	sq_size;
	float	dist;
	float	size_y;
}	t_draw_info;

t_draw_info	ini_draw_info(t_rayhit *hit, int i, float rad)
{
	t_render	*r;
	t_player	*p;
	t_draw_info	ret;

	r = render();
	p = player();
	ret.dist = dist_vct(p->pos, hit->pos) * cos(add_rad(rad, -p->rot_rad) );
	ret.size_y = render()->fov_v_adjust / ret.dist;
	ret.center = ini_vct_pos(r->ray_width / 2 + i * r->ray_width, WINDOW_Y / 2);
	ret.center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	ret.sq_size = ini_vct_pos(render()->ray_width, ret.size_y);
	return (ret);
}


void draw_door(t_rayhit *hit, int i, float rad)
{
	t_frame *f;

	float	dist;
	float	size_y;
	t_vct	center;
	t_vct	sq_size;

	t_vct vct;
	t_vct pos;

	if (hit->dir == dir_north)
		vct = ini_vct_pos(0, -1);
	if (hit->dir == dir_south)
		vct = ini_vct_pos(0, 1);
	if (hit->dir == dir_east)
		vct = ini_vct_pos(1, 0);
	if (hit->dir == dir_west)
		vct = ini_vct_pos(-1, 0);
	pos = add_vct(hit->pos, scale_vct(vct, GRIDSIZE / 2));
	dist = dist_vct(player()->pos, pos) * cos(add_rad(rad, -player()->rot_rad) );
	size_y = render()->fov_v_adjust / dist;
	center = ini_vct_pos(render()->ray_width / 2 + i * render()->ray_width, WINDOW_Y / 2);
	center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	sq_size = ini_vct_pos(render()->ray_width, size_y);
	set_pixel_pos(center.x, center.y , 0xFF0000);
	f = &render()->door_frame[door_get_state(hit->grid)];
	if (hit->axis == X)
		draw(center, sq_size, (int)hit->pos.y, f);
	else
		draw(center, sq_size, (int)hit->pos.x, f);
}
static void draw_wall(t_rayhit *hit, int i, float rad)
{
	t_frame *f;

	float	dist;
	float	size_y;
	t_vct	center;
	t_vct	sq_size;
	
	dist = dist_vct(player()->pos, hit->pos) * cos(add_rad(rad, -player()->rot_rad) );
	size_y = render()->fov_v_adjust / dist;
	center = ini_vct_pos(render()->ray_width / 2 + i * render()->ray_width, WINDOW_Y / 2);
	center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	sq_size = ini_vct_pos(render()->ray_width, size_y);

	f = &render()->wall_frame[hit->dir];
	if (hit->axis == X)
		draw(center, sq_size, (int)hit->pos.y, f);
	else
		draw(center, sq_size, (int)hit->pos.x, f);
}

void render_cub(void)
{
	t_rayhit	hit;
	float		rad;
	int			i;
	
	i = 0;
	rad = add_rad(player()->rot_rad, -FOV / 2.0);
	while (i < RAYCOUNT)
	{
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_wall, NULL));
		if (hit.sucess)
			draw_wall(&hit, i, rad);
		rad = add_rad(rad, render()->ray_delta_angle);
		i++;
	}

	/*
	i = 0;
	rad = add_rad(player()->rot_rad, -FOV / 2.0);
	while (i < RAYCOUNT)
	{
		hit = raycast(ini_ray(player()->pos, ini_vct_rad(rad), hit_door, hit_wall));
		if (hit.sucess)
			draw_door(&hit, i, rad);
		rad = add_rad(rad, render()->ray_delta_angle);
		i++;
	}
	*/
}
