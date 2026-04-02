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
	while (x <= x_end)
	{
		y = clamp(ctr.y - size, 0, render()->window_y);
		while (y <= y_end)
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

static void set_limit(t_vct *i, t_vct *end, t_vct center, t_vct size)
{
	*i = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	*end = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	i->x = clamp(i->x, 0, render()->window_x);
	i->y = clamp(i->y, 0, render()->window_y);
	end->x = clamp(end->x, 0, render()->window_x);
	end->y = clamp(end->y, 0, render()->window_y);
}

static void set_pixel(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + y + x;
	*(unsigned int *)dst = color;
}
void	draw_square(t_vct center, t_vct size, int color)
{
	t_vct	i;
	t_vct	end;
	t_frame *f;
	int	x_start;
	int		y_offset;

	set_limit(&i, &end, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	x_start = i.x;
	while (i.y < end.y)
	{
		i.x = x_start;
		y_offset  = (int)i.y * f->line_len;
		while (i.x < end.x)
		{
			set_pixel(f, (int)i.x * f->bits_pixel, y_offset, color);
			i.x++;
		}
		i.y++;
	}
}

/*


static void set_limit(t_vct *i, t_vct *end, t_vct center, t_vct size)
{
	*i = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	*end = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	end->x = clamp(end->x, 0, render()->window_x);
	end->y = clamp(end->y, 0, render()->window_y);

}

static void set_pixel(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + y + x;
	*(unsigned int *)dst = color;
}
void	draw_square(t_vct center, t_vct size, int color)
{
	t_vct	i;
	t_vct	end;
	t_frame *f;
	float	x_start;
	int		y_offset;

	set_limit(&i, &end, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	x_start = clamp(center.x - size.x / 2.0, 0, render()->window_x) ; //clamp this
	while (i.y < end.y)
	{
		i.x = x_start;
		y_offset = (int)i.y * f->line_len;
		while (i.x < end.x)
		{
			set_pixel(f, (int)i.x * f->bits_pixel, y_offset, color);
			i.x++;
		}
		i.y++;
	}
}

f = &render()->frame_buff[render()->frame_cur];
	offset = y * f->line_len + x * (f->bits_pixel / 8);
	dst = f->addr + offset;
	*(unsigned int *)dst = color;
*/