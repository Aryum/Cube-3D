#include "render.h"

void	draw_circle(t_vct ctr, int size, int color)
{
	int	x;
	int	y;
	int	x_end;
	int	y_end;

	x = clamp(ctr.x - size, 0, render()->window_x);
	x_end = clamp(ctr.x + size, 0, render()->window_x);
	y_end = clamp(ctr.y + size, 0, render()->window_y);
	while (x < x_end)
	{
		y = clamp(ctr.y - size, 0, render()->window_y);
		while (y < y_end)
		{
			if (pow(ctr.x-x, 2) + pow(ctr.y-y, 2) < pow(size, 2))
				put_pixel(x, y, color);
			y++;
		}
		x++;
	}
}


void	draw_same_x(t_vct start, t_vct end, int color)
{
	t_vct	tar;

	if (start.y < end.y)
		tar = ini_vct(start.y, end.y);
	else
		tar = ini_vct(end.y, start.y);
	while (tar.x < tar.y)
	{
		put_pixel(start.x, tar.x, color);
		tar.x++;
	}
}

void	draw_default(t_vct start, t_vct end, int color)
{
	t_vct	tar;
	t_vct	cur;
	float	m;
	float	b;

	m = (float)(end.y - start.y) / (float)(end.x - start.x);
	b = start.y - start.x * m;
	if (start.x < end.x)
		tar = ini_vct(start.x, end.x);
	else
		tar = ini_vct(end.x, start.x);
	while (tar.x < tar.y)
	{
		cur = ini_vct(tar.x, floor(m * tar.x + b));
		put_pixel(cur.x, cur.y, color);
		if (tar.x + 1 < tar.y)
			draw_same_x(cur, ini_vct(cur.x, floor(m * (tar.x + 1) + b)), color);
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
