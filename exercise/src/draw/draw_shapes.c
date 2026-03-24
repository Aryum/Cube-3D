#include "draw.h"

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

void	draw_quad(t_quad quad, int color)
{
	draw_line(quad.pos[0], quad.pos[1], color);
	draw_line(quad.pos[0], quad.pos[2], color);
	draw_line(quad.pos[3], quad.pos[1], color);
	draw_line(quad.pos[3], quad.pos[2], color);
}

