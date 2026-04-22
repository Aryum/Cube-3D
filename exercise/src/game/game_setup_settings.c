#include "hlp.h"

static t_minimap ini_minimap(void)
{
	t_minimap	ret;

	ret.corner = ini_vct_pos(WINDOW_X, WINDOW_Y);
	ret.size = ini_vct_pos(200, 200);
	ret.grid_size = vct_scale(ret.size, 1/8.0);
	ret.size = vct_add(ret.size, ret.grid_size);
	ret.center = vct_add(ret.corner, vct_scale(ret.size, -0.6));
	ret.limit[0] = vct_add(ret.center,vct_scale(ret.size, -0.5));
	ret.limit[1] = vct_add(ret.center,vct_scale(ret.size, 0.5));
	return ret;
}

void setup_settings(t_render *r)
{
	r->last_time = get_time();
	r->start_time = r->last_time;
	r->fov_adj.x = tan(FOV /2) ;
	r->fov_adj.y = (float)(WINDOW_X / 2) * (float)GRIDSIZE / tan(FOV / 2);
	r->ray_delta_angle = FOV / (float)(RAYCOUNT - 1);
	r->ray_width = (float)WINDOW_X / (float)RAYCOUNT;
	r->minimap = ini_minimap();
}
