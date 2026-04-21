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

bool hit_wall(t_ray *r)
{
	char	c;

	c = get_map_char(r->cur_grid);
	if (c == 'D' && !door_get_state(r->cur_grid))
		return (true);
	return (c == '1');
}

bool hit_door(t_ray *r)
{
	return (get_map_char(r->cur_grid) == 'D' );
}
bool hit_door_open(t_ray *r)
{
	return (get_map_char(r->cur_grid) == 'D' && door_get_state(r->cur_grid));
}

bool hit_rnd_backdoor(t_ray *r)
{
	t_vct	grid;

	if (vct_cmp(r->cur_grid, player()->grid))
		return (false);
	if (get_map_char(r->cur_grid) != '0')
		return (false);
	grid = vct_add(r->cur_grid, vct_scale(r->axis_dir[r->cur_axis] , -1));
	return (get_map_char(grid) == 'D' && !vct_cmp(grid, player()->grid));
}

bool miss_rnd_backdoor(t_ray *r)
{
	char	c;

	c = get_map_char(r->cur_grid);
	if (c == 'D' && !door_get_state(r->cur_grid))
		return (true);
	return (c == '1');
}