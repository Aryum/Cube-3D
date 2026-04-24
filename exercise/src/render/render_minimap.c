#include "hlp.h"

void draw_ray(t_minimap	m)
{
	t_vct	dir;
	t_vct	pos;
	t_ray	ray;
	int 	i;

	i = 0;
	while (i < 2)
	{
		dir = player()->ray_dir[i];
		ray = ini_ray(m.center, dir, NULL);
		if (f_abs(dir.x)  >  f_abs(dir.y) )
			pos = calculate_ray_pos(ray, X, m.limit[dir.x > 0]);
		else
			pos = calculate_ray_pos(ray, Y, m.limit[dir.y > 0]);
		draw_line(m.center, pos, 0xff0000);
		i++;
	}
}
void	render_minimap(t_render *r)
{
	t_minimap	m;
	int		x;
	int		y;

	m = r->minimap;
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
	draw_circle(m.center, 5,  0xFA05EE);
	draw_ray(m);
}
