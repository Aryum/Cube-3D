#include "ray.h"

bool hit_wall(t_vct grid_pos)
{
	int x;
	int y;

	x = (int)floor(grid_pos.x);
	y = (int)floor(grid_pos.y);
	if (grid_pos.x < 0 || grid_pos.x >= map()->len_x)
		return false;
	if (grid_pos.y < 0 || grid_pos.y >= map()->len_y)
		return false;
	return (map()->layout[y][x] == '1');
}
