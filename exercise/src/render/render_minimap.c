#include "hlp.h"

void	render_minimap(t_render *rnd)
{
	int	x;
	int	y;

	y = -5;
	while (y <= 5) 
	{
		x = -5;
		while (x <= 5)
		{
			draw_map_tile(rnd->minimap, x, y);
			x++;
		}
		y++;
	}
	t_vct ctr;
	t_vct	left;
	t_vct	right;

	ctr =rnd->minimap.center;
	right =  add_vct(ctr, scale_vct(ini_vct_rad(add_rad(player()->rot_rad, + rnd->fov_tar)), 50));
	left =  add_vct(ctr, scale_vct(ini_vct_rad(add_rad(player()->rot_rad, - rnd->fov_tar)), 50));
	if(1)
	{
		draw_line(ctr, left, 0xFFFFFF);
		draw_line(ctr, right,  0xFFFFFF);
	}
	draw_circle(rnd->minimap.center, 7,  0xFA05EE);
}
