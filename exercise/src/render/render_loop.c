#include "render.h"

static void	loop_map(t_map	mp, void (*f)(char **, int, int))
{
	int		x;
	int		y;

	y = 0;
	while (y < mp.size_y)
	{
		x = 0;
		while (x < mp.size_x)
		{
			f(mp.layout, x, y);
			x++;
		}
		y++;
	}
}

void draw(char **map, int x, int y)
{
	t_vector_i limit;
	t_vector_i cur;
	int border = 1;
	if (map[y][x] != '1')
		return ;
	cur.x = x * GRIDSIZE + border;
	cur.y = y * GRIDSIZE + border;
	limit.x = cur.x + GRIDSIZE - border * 2;
	limit.y = cur.y + GRIDSIZE - border * 2;
	while (cur.y < limit.y)
	{
		cur.x = x * GRIDSIZE + border;
		while (cur.x < limit.x)
		{
			mlx_pixel_put(render()->mlx, render()->window, cur.x, cur.y, 0xffffff);
			cur.x++;
		}
		cur.y++;
	}
}

int render_loop(void)
{
	t_map mp;
	mp = *map();

	loop_map(mp, draw);
	return 0;
}