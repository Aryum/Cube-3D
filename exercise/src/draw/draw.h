#ifndef DRAW_H
# define DRAW_H

#include "../cub.h"

void	draw_line(t_vct start, t_vct end, int color);
void	draw_circle(t_vct ctr, int size, int color);

void	draw_quad(t_quad quad, int color);

void	draw_square(t_vct center, t_vct size, float color);

#endif