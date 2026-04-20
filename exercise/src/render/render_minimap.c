#include "hlp.h"

void	render_minimap(t_render *r)
{
	int	x;
	int	y;

	y = -5;
	while (y <= 5) 
	{
		x = -5;
		while (x <= 5)
		{
			draw_map_tile(r->minimap, x, y);
			x++;
		}
		y++;
	}
	draw_circle(r->minimap.center, 5,  0xFA05EE);
}
