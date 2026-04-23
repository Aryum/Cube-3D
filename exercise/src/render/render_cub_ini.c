#include "hlp.h"

t_draw_ray	ini_draw_ray(int i)
{
	t_draw_ray	ret;
	float		angle;
	float		cast_pos;

	ret.pos_vct = player()->pos;
	cast_pos = 2.0 * (float)i / (float)RAYCOUNT - 1.0;
	ret.i = i;
	angle = player()->rot_rad + atan(cast_pos * render()->fov_adj.x);
	ret.cos_adjust = cos(add_rad(angle, -player()->rot_rad));
	ret.dir_vct = ini_vct_rad(angle);
	ret.last_grid = ini_vct_pos(-1, -1);
	ret.first = true;
	return (ret);
}

t_draw_info	ini_draw_info(t_rayhit hit, t_draw_ray d, t_frame *f)
{
	t_draw_info	ret;
	t_render	*r;
	t_player	*p;

	r = render();
	p = player();
	ret.f = f;
	ret.dist = vct_dist(p->pos, hit.pos) * d.cos_adjust;
	ret.size_y = (r->fov_adj.y) / ret.dist;
	ret.center = ini_vct_pos(floor(r->ray_width / 2 + d.i * r->ray_width), WINDOW_Y / 2);
	ret.center.y += sin(player()->tilt) * (float)(WINDOW_Y / 2);
	ret.sq_size = ini_vct_pos(r->ray_width, ret.size_y);
	if (hit.axis == X)
		ret.x = (int)hit.pos.y;
	else
		ret.x = (int)hit.pos.x;
	return (ret);
}

t_draw_ray	update_draw_info(t_draw_ray d, t_rayhit hit)
{
	d.last_grid = hit.grid;
	d.first = false;
	d.pos_vct = hit.pos;
	return (d);
}