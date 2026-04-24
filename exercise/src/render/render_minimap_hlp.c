#include "hlp.h"

static int get_color(t_tile *tile)
{

	if (tile == NULL)
		return 0x6C0D4C;
	if (tile->val == '\0')
		return 0x6C0D4C;
	if (tile->val == '1')
		return 0x0D4D6C;
	if (tile->val == '0')
		return 0x4C6C0D;
	if (tile->val == 'D')
		return (0xffffff);
	return 0x4C6C0D;
}

static float *val(t_vct *vct, t_axis axis)
{
	if (axis == X)
		return (&vct->x);
	else
		return (&vct->y);
}

static void resize_border(t_minimap *m, t_axis axis)
{
	float	*grid;
	float	*center; 
	float	max;
	float	min;

	grid = val(&m->grid_size, axis);
	center = val(&m->center, axis);
	min = *val(&m->limit[0], axis);
	max = *val(&m->limit[1], axis);
	if (min > *center - *grid / 2)
	{
		*grid = *center + *grid / 2 - min;
		*center = min + *grid / 2;
	}
	if (max < *center + *grid / 2)
	{
		*grid = max - (*center - *grid / 2);
		*center = max - *grid / 2;
	}
}

void	draw_map_tile(t_minimap m, int x, int y)
{
	t_vct	cur;
	t_vct	draw_pos;
	t_vct	adjust;
	t_tile	*tile;

	cur = vct_add(player()->grid, ini_vct_pos(x,y));
	draw_pos = ini_vct_pos(m.grid_size.x * x, m.grid_size.y * y);
	adjust = grid_distance(player()->pos);
	adjust.x = m.grid_size.x * adjust.x / GRIDSIZE - m.grid_size.x / 2;
	adjust.y = m.grid_size.y * adjust.y / GRIDSIZE - m.grid_size.y / 2;
	draw_pos = vct_add(draw_pos, adjust);
	m.center = vct_add(m.center, draw_pos);
	resize_border(&m, X);
	resize_border(&m, Y);
	tile = tile_get(cur);
	
	draw_square(m.center, m.grid_size , get_color(tile));
	if (tile != NULL && tile->playable == tile_enemy)
		draw_circle(m.center, 5, 0xFF);
}
