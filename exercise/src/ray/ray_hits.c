#include "ray.h"

#include "ray.h"

char get_map_char(t_vct grid_pos)
{
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

bool hit_wall(t_vct grid_pos)
{
	return (get_map_char(grid_pos) == '1');
}

bool hit_any(t_vct grid_pos)
{
	char	c;
	c = get_map_char(grid_pos);
	return (c == '1' || c == 'D');
}

bool hit_door(t_vct grid_pos)
{
	return (get_map_char(grid_pos) == 'D');
}

bool hit_move(t_vct grid_pos)
{
	t_tile	*tile;

	tile = tile_get(grid_pos);
	if (tile == NULL)
		return (false);
	if (tile->val == '1' || tile->val == 'E')
		return (true);
	if (tile->val == 'D')
		return (((t_door *)tile->content)->open);
	return (false);
}