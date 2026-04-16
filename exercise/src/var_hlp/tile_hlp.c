#include "var_hlp.h"

t_tile	*tile_get(t_vct grid)
{
	int		x;
	int		y;

	x = grid.x;
	y = grid.y;
	if (x < 0 || x >= map()->len_x)
		return (NULL);
	if (y < 0 || y >= map()->len_y)
		return (NULL);
	return (&map()->layout[y][x]);
}

char	tile_get_char(t_vct grid)
{
	t_tile	*t;

	t = tile_get(grid);
	if (t == NULL)
		return ('\0');
	return (t->val);
}

