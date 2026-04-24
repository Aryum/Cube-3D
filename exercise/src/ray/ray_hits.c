#include "hlp.h"

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
bool hit_empty(t_ray *r)
{
	return (get_map_char(r->cur_grid) == tile_empty );
}

bool hit_wall(t_ray *r)
{
	return (get_map_char(r->cur_grid) == tile_wall);
}
bool hit_wall_door(t_ray *r)
{
	char	c;

	c = get_map_char(r->cur_grid);
	if (c == tile_door && !door_get_state(r->cur_grid))
		return (true);
	return (c == tile_wall);
}

bool hit_door(t_ray *r)
{
	t_vct	pos;
	t_vct	grid;
	t_axis	axis;

	axis = r->cur_axis;

	if(get_map_char(r->cur_grid) != tile_door)
		return (false);
	pos = vct_add(r->cur_pos, vct_scale(r->axis_dir[axis], GRIDSIZE / 2));
	pos = calculate_ray_pos(*r, axis, pos);
	grid = pos_to_grid(pos);
	if (get_map_char(grid) != tile_door)
		return (false);
	r->cur_pos = pos;
	return (true);
}

bool hit_rnd_backdoor(t_ray *r)
{
	t_vct	grid;

	if (vct_cmp(r->cur_grid, player()->grid))
		return (false);
	if (get_map_char(r->cur_grid) != tile_empty)
		return (false);
	r->check_done = true;
	grid = vct_add(r->cur_grid, vct_scale(r->axis_dir[r->cur_axis] , -1));
	return (get_map_char(grid) == tile_door && !vct_cmp(grid, player()->grid));
}
