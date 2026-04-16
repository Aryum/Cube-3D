#include "var_hlp.h"

t_door	*door_get(t_vct grid)
{
	t_tile	*tile;

	tile = tile_get(grid);
	if (tile != NULL && tile->val == 'D')
		return (tile->content);
	return (NULL);
}

void	door_switch_state(t_vct grid)
{
	t_door	*door;

	door = door_get(grid);
	if (door != NULL)
		door->open = !door->open;
}

bool	door_get_state(t_vct grid)
{
	t_door	*door;

	door = door_get(grid);
	if (door == NULL)
		return (false);
	return (door->open);
}


