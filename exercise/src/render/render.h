#ifndef RENDER_H
# define RENDER_H

#include "../cub.h"
int	render_loop(void);


//display
void	put_image(t_render *rnd);

void	put_pixel(int x, int y, int color);


//ini

void	render_ini();
void	ini_frame(t_render *r, t_frame *f);

//shapes

void	draw_circle(t_vct ctr, int size, int color);

void	draw_line(t_vct start, t_vct end, int color);

//math
float	f_abs(float a);

int clamp(int val, int min, int max);

#endif