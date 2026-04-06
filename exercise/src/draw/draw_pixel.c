#include "hlp.h"

void	set_pixel_add(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + y + x * f->bits_pixel;
	*(unsigned int *)dst = color;
}

void	set_pixel_pos(int x, int y, int color)
{
	t_frame	*f;
	char	*dst;
	int		offset;

	f = &render()->frame_buff[render()->frame_cur];
	offset = y * f->line_len + x * f->bits_pixel;
	dst = f->addr + offset;
	*(unsigned int *)dst = color;
}
