#include "hlp.h"

static t_vct set_draw_limit(t_vct i[2], t_vct center, t_vct size)
{
	t_vct	ret;

	i[1] = ini_vct_pos(center.x - size.x / 2.0 , center.y - size.y / 2.0);
	i[0] = ini_vct_pos(center.x + size.x / 2.0, center.y + size.y / 2.0);
	ret.x = i[1].y - i[0].y;
	if(i[1].y < 0)
		ret.y = -i[1].y;
	else
		ret.y = 0;
	i[0].x = clamp(i[0].x, 0, WINDOW_X - 1);
	i[0].y = clamp(i[0].y, 0, WINDOW_Y - 1);
	i[1].x = clamp(i[1].x, 0, WINDOW_X - 1);
	i[1].y = clamp(i[1].y, 0, WINDOW_Y - 1);
	return ret;
}

static int	get_color(int x, t_vct i[2], t_vct adj, t_frame *f)
{
	char	*dst;
	int		y;


	y =  (int)floor((i[1].y - i[0].y - adj.y) * (float)(GRIDSIZE)/ adj.x);
	dst = f->addr + y * f->line_len + ((x - 1) % GRIDSIZE) * f->bp;
	return (*(unsigned int *)dst);
}


void	draw_texture(t_draw_info d)
{
	t_vct	i[2];
	t_vct	pivot;
	t_vct	adj;
	t_frame	*f;

	adj = set_draw_limit(i, d.center, d.sq_size);
	f = &render()->frame_buff[render()->frame_cur];
	pivot.x = i[0].x;
	while (i[0].y > i[1].y)
	{
		i[0].x = pivot.x;
		pivot.y = (int)i[0].y * f->line_len;
		while (i[0].x > i[1].x)
		{
			set_pixel_add(f, i[0].x, pivot.y, get_color(d.x, i, adj, d.f));
			i[0].x--;
		}
		i[0].y--;
	}
}


