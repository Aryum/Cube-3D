#include "hlp.h"

static t_minimap ini_minimap(void)
{
	t_minimap	ret;

	ret.corner = ini_vct_pos(WINDOW_X, WINDOW_Y);
	ret.size = ini_vct_pos(200, 200);
	ret.grid_size = scale_vct(ret.size, 1/8.0);
	ret.size = add_vct(ret.size, ret.grid_size);
	ret.center = add_vct(ret.corner, scale_vct(ret.size, -0.6));
	ret.limit[0] = add_vct(ret.center,scale_vct(ret.size, -0.5));
	ret.limit[1] = add_vct(ret.center,scale_vct(ret.size, 0.5));
	return ret;
}

void setup_settings(t_render *r)
{
	r->last_time = get_time();
	r->start_time = r->last_time;
	r->fov_adj.x = tan(FOV /2);
	r->fov_adj.y = (float)(WINDOW_X / 2) / tan(FOV / 2);
	r->ray_delta_angle = FOV / (float)(RAYCOUNT - 1);
	r->ray_width = (float)WINDOW_X / (float)RAYCOUNT;
	r->minimap = ini_minimap();
}
