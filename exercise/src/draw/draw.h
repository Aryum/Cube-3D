#ifndef DRAW_H
# define DRAW_H

#include "../cub.h"

void	draw_line(t_vct start, t_vct end, int color);
void	draw_circle(t_vct ctr, int size, int color);
void	draw_quad(t_quad quad, int color);
void	draw_square(t_vct center, t_vct size, int color);
void	set_pixel_add(t_frame *f, int x, int y, int color);
void	set_pixel_pos(int x, int y, int color);
void	draw_wall(t_vct center, t_vct size, int x, t_frame *texture);

#endif