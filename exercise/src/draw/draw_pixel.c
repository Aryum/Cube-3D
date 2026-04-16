#include "draw.h"

void	set_pixel_add(t_frame *f, int x, int y, int color)
{
	char	*dst;

	if (color == 0x555555)
		return ;
	dst = f->addr + y + x * f->byte_pixel;
	*(unsigned int *)dst = color;
}

void	set_pixel_pos(int x, int y, int color)
{
	t_frame	*f;
	char	*dst;
	int		offset;

	if (color == 0x555555)
		return ;
	f = &render()->frame_buff[render()->frame_cur];
	offset = y * f->line_len + x * f->byte_pixel;
	dst = f->addr + offset;
	*(unsigned int *)dst = color;
}
