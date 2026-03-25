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

static void	set_tar(t_vct *tar, float *end_y, t_vct start, t_vct end)
{
	if (start.x < end.x)
	{
		*tar = ini_vct_pos(start.x, end.x);
		*end_y = end.y;
	}
	else
	{
		*tar = ini_vct_pos(end.x, start.x);
		*end_y = start.y;
	}
}

static float get_y(float m, float x, float b)
{
	return (floor(m * x + b));
}

static void	draw_default(t_vct start, t_vct end, int color)
{
	t_vct	tar;
	t_vct	cur;
	float	m;
	float	b;
	float	end_y;
	
	m = (end.y - start.y) / (end.x - start.x);
	b = start.y - start.x * m;
	set_tar(&tar, &end_y, start, end);
	while (tar.x < tar.y)
	{
		cur = ini_vct_pos(tar.x, get_y(m, tar.x, b));
		put_pixel(cur.x, cur.y, color);
		tar.x++;
		if (tar.x < tar.y)
			draw_same_x(cur, ini_vct_pos(cur.x, get_y(m, tar.x, b)), color);
		else
			draw_same_x(cur, ini_vct_pos(cur.x, end_y), color);
	}
}

void	draw_line(t_vct start, t_vct end, int color)
{
	if (f_abs(end.x - start.x) < 1)
		draw_same_x(start, end, color);
	else
		draw_default(start, end, color);
}