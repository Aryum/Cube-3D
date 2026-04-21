#include "hlp.h"

bool hit_enemy(t_ray *r)
{
	t_tile	*tile;

	tile = tile_get(r->cur_grid);
	if (tile == NULL)
		return (false);
	return (tile->playable == tile_enemy);
}

bool hit_player(t_ray *r)
{
	t_tile	*tile;

	tile = tile_get(r->cur_grid);
	if (tile == NULL)
		return (false);
	return (tile->playable == tile_player);
}

bool	miss_player(t_ray *r)
{
	(void)r;
	return (false);
}

bool	miss_enemy(t_ray *r)
{
	(void)r;
	return (false);
}