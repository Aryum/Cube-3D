#include "draw.h"

static int set_limit(t_vct i[2], t_vct center, t_vct size)
{
	float	ret;

	i[1] = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	i[0] = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	ret = i[1].y - i[0].y;
	i[0].x = clamp(i[0].x, 0,  WINDOW_X);
	i[0].y = clamp(i[0].y, 0, WINDOW_Y);
	i[1].x = clamp(i[1].x, 0, WINDOW_X);
	i[1].y = clamp(i[1].y, 0, WINDOW_Y);
	return ret;
}

static int	get_color(int x, float y, t_frame *f)
{
	char	*dst;

	dst = f->addr + (int)(y * (float)GRIDSIZE) * f->line_len + (GRIDSIZE-x % (GRIDSIZE)) * f->byte_pixel;
	return (*(unsigned int *)dst);
}
/*
	calculate % based of how much it has already drawn 
*/

void	draw_wall(t_vct center, t_vct size, int x, t_frame *texture)
{
	t_vct	i[2];
	t_vct	pivot;
	float	total;
	t_frame	*f;

	total = set_limit(i, center, size);
	f = &render()->frame_buff[render()->frame_cur];
	pivot.x = i[0].x;
	while (i[0].y > i[1].y)
	{
		i[0].x = pivot.x;
		pivot.y = (int)i[0].y * f->line_len;
		while (i[0].x > i[1].x)
		{
			set_pixel_add(f, i[0].x, pivot.y, get_color(x, (i[1].y - i[0].y) / (total), texture));
			i[0].x--;
		}
		i[0].y--;
	}
}
