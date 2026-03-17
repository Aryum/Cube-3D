#ifndef RENDER_H
# define RENDER_H

#include "../cub.h"
int	render_loop(void);


//display
void	put_image(t_render *rnd);

void	put_pixel(int x, int y, int color);


//ini

void	render_ini();

#endif