#include "render.h"

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
	draw_circle(rnd->minimap.center, 7,  0xFA05EE);
}