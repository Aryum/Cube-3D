#include "ray.h"

bool hit_wall(t_vct grid_pos)
{
	int x;
	int y;

	x = (int)floor(grid_pos.x);
	y = (int)floor(grid_pos.y);
	return (map()->layout[y][x] == '1');
}
