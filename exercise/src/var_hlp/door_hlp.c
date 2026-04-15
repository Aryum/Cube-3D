#include "var_hlp.h"

t_door	*door_get(t_vct grid)
{
	t_door	**arr;
	int		i;

	i = 0;
	arr = map()->door_arr;
	while (arr[i] != NULL)
	{
		if (equal_vct(grid, arr[i]->pos))
			return (arr[i]);
		i++;
	}
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


