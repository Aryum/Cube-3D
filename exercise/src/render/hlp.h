#ifndef HLP_H
# define HLP_H

#include "render.h"

void	draw_map_tile(t_minimap m, int x, int y);
void	render_minimap(t_render *rnd);
void	render_cub(void);

void	setup_settings(t_render *rnd);
bool	setup_mlx(t_render	*rnd);


void	render_debug_str(t_render *rnd);
void	render_debug_map(t_player *p);
int		render_loop(void);

#endif