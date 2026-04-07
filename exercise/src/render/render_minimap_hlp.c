#include "hlp.h"

static int get_color(t_vct grid_pos)
{
	char	c;
	int		x;
	int		y;

	x = (int)floor(grid_pos.x);
	y = (int)floor(grid_pos.y);
	if (grid_pos.x < 0 || grid_pos.x >= map()->len_x)
		return 0x6C0D4C;
	if (grid_pos.y < 0 || grid_pos.y >= map()->len_y)
		return 0x6C0D4C;
	c = map()->layout[y][x];
	if (c == '1')
		return 0x0D4D6C;
	if (c == '0')
		return 0x4C6C0D;
	else
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

	cur = add_vct(player()->grid, ini_vct_pos(x,y));
	draw_pos = ini_vct_pos(m.grid_size.x * x, m.grid_size.y * y);
	adjust = grid_distance(player()->pos);
	adjust.x = m.grid_size.x * adjust.x / GRIDSIZE - m.grid_size.x / 2;
	adjust.y = m.grid_size.y * adjust.y / GRIDSIZE - m.grid_size.y / 2;
	draw_pos = add_vct(draw_pos, adjust);
	m.center = add_vct(m.center, draw_pos);
	resize_border(&m, X);
	resize_border(&m, Y);
	draw_square(m.center, m.grid_size , get_color(cur));
}
