#include "draw.h"

static void	draw_same_x(t_vct start, t_vct end, int color)
{
	t_vct	tar;

	if (start.y < end.y)
		tar = ini_vct_pos(start.y, end.y);
	else
		tar = ini_vct_pos(end.y, start.y);
	while (tar.x < tar.y)
	{
		put_pixel(start.x, tar.x, color);
		tar.x++;
	}
}

static void	draw_default(t_vct start, t_vct end, int color)
{
	t_vct	tar;
	t_vct	cur;
	float	m;
	float	b;

	m = (float)(end.y - start.y) / (float)(end.x - start.x);
	b = start.y - start.x * m;
	if (start.x < end.x)
		tar = ini_vct_pos(start.x, end.x);
	else
		tar = ini_vct_pos(end.x, start.x);
	while (tar.x < tar.y)
	{
		cur = ini_vct_pos(tar.x, floor(m * tar.x + b));
		put_pixel(cur.x, cur.y, color);
		if (tar.x + 1 < tar.y)
			draw_same_x(cur, ini_vct_pos(cur.x, floor(m * (tar.x + 2) + b)), color);
		tar.x++;
	}
}

void	draw_line(t_vct start, t_vct end, int color)
{
	if (f_abs(end.x - start.x) < 2)
		draw_same_x(start, end, color);
	else
		draw_default(start, end, color);
}