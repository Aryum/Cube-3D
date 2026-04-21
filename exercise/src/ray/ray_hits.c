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
	t_vct	pos;

	if (vct_cmp(player()->grid, r->cur_grid))
		return (false);
	if (get_map_char(r->cur_grid) != '0')
		return (0);
	pos = add_vct(r->cur_grid, scale_vct(r->axis_dir[r->cur_axis] , -1));
	return (get_map_char(pos) == 'D');
}

bool miss_rnd_backdoor(t_ray *r)
{
	t_vct	pos;
	char	c;

	pos = add_vct(r->cur_grid, scale_vct(r->axis_dir[r->cur_axis] , -1));
	if (vct_cmp(pos, player()->grid))
		return (true);
	c = get_map_char(r->cur_grid);
	if (c == 'D' && !door_get_state(r->cur_grid))
		return (true);
	return (c == '1');
}