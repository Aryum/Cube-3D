#include "hlp.h"

static void set_limit(t_vct *i, t_vct *end, t_vct center, t_vct size)
{
	*i = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	*end = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	i->x = clamp(i->x, 0, render()->window_x);
	i->y = clamp(i->y, 0, render()->window_y);
	end->x = clamp(end->x, 0, render()->window_x);
	end->y = clamp(end->y, 0, render()->window_y);
}

void	draw_square(t_vct center, t_vct size, int color)
{
	t_vct	i;
	t_vct	end;
	t_frame *f;
	int		x_start;
	int		y_offset;

	set_limit(&i, &end, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	x_start = i.x;
	
	while (i.y < end.y)
	{
		i.x = x_start;
		y_offset = (int)i.y * f->line_len;
		while (i.x < end.x)
		{
			set_pixel_add(f, (int)i.x, y_offset, color);
			i.x++;
		}
		i.y++;
	}
}

void	draw_quad(t_quad quad, int color)
{
	draw_line(quad.pos[0], quad.pos[1], color);
	draw_line(quad.pos[0], quad.pos[2], color);
	draw_line(quad.pos[3], quad.pos[1], color);
	draw_line(quad.pos[3], quad.pos[2], color);
}