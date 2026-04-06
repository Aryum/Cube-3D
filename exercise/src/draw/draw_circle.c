#include "hlp.h"

static void set_limit(t_vct *i, t_vct *end, t_vct center, int size)
{
	*i = ini_vct_pos(center.x - size, center.y - size);
	*end = ini_vct_pos(center.x + size, center.y + size);
	i->x = clamp(i->x, 0, render()->window_x);
	i->y = clamp(i->y, 0, render()->window_y);
	end->x = clamp(end->x, 0, render()->window_x);
	end->y = clamp(end->y, 0, render()->window_y);
}

void	draw_circle(t_vct ctr, int size, int color)
{
	t_vct	i;
	t_vct	end;
	t_frame	*f;
	int		x_start;
	int		y_offset;

	set_limit(&i, &end, ctr, size);
	f = &render()->frame_buff[render()->frame_cur];
	x_start = i.x;
	while (i.y <= end.y)
	{
		i.x = x_start;
		y_offset = (int)i.y * f->line_len;
		while (i.x <= end.x)
		{
			if (pow_2(ctr.x-i.x) + pow_2(ctr.y-i.y) < pow_2(size))
				set_pixel_add(f, (int)i.x, y_offset, color);
			i.x++;
		}
		i.y++;
	}
}
