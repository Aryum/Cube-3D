#ifndef RENDER_H
# define RENDER_H

#include "../cub.h"
int	render_loop(void);


//display
void	put_image(t_render *rnd);

//ini

void	render_ini();
void	ini_frame(t_render *r, t_frame *f);

//shapes

void	draw_circle(t_vct ctr, int size, int color);

void	draw_line(t_vct start, t_vct end, int color);

//math
float	f_abs(float a);

float clamp(float val, float min, float max);
bool reached_clamp(float *val, float min, float max);
long get_time(void);
float	pow_2(float a);
void draw_map_tile(t_minimap m, int x, int y);

#endif