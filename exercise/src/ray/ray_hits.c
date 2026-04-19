#include "ray.h"

char get_map_char(t_vct grid_pos)
{
	;
	int	x;
	int	y;

	x = (int)floor(grid_pos.x);
	y = (int)floor(grid_pos.y);
	if (grid_pos.x < 0 || grid_pos.x >= map()->len_x)
		return ('\0');
	if (grid_pos.y < 0 || grid_pos.y >= map()->len_y)
		return ('\0');
	return (map()->layout[y][x].val);
}

bool hit_wall(t_ray *r)
{
	return (get_map_char(r->cur_grid) == '1');
}

bool hit_any(t_ray *r)
{
	char	c;
	c = get_map_char(r->cur_grid);
	return (c == '1' || c == 'D');
}

bool hit_door(t_ray *r)
{
	return (get_map_char(r->cur_grid) == 'D');
}

