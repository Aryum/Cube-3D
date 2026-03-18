#include "render.h"

int clamp(int val, int min, int max)
{
	if (val >= max)
		return max;
	if (val <= min)
		return min;
	return val;
}
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

void	draw_line(t_vct start, t_vct end, int color)
{
	int		x;
	float	m;
	float	b;


	m = (float)(end.y - start.y) / (float)(end.x - start.x);
	b = start.y - start.x * m;
	x = start.x;
	while (x < end.x)
	{
		put_pixel(x, m * x + b, color);
		x++;
	}
}