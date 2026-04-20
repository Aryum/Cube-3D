#ifndef HLP_H
# define HLP_H

#include "render.h"

typedef	struct s_draw_info
{
	t_frame	*f;
	t_vct	center;
	t_vct	sq_size;
	float	dist;
	float	size_y;
	int		x;
}	t_draw_info;


//cub
t_draw_info	ini_draw_info(t_rayhit *hit, t_draw_ray *d, t_frame *f);
t_draw_ray	ini_draw_ray(int i);
void	draw_texture(t_draw_info *d);


void	draw_map_tile(t_minimap m, int x, int y);
void	render_minimap(t_render *rnd);
void	render_cub(void);

void	setup_settings(t_render *rnd);
bool	setup_mlx(t_render	*rnd);


void	render_debug_str(t_render *rnd);
void	render_debug_map(t_player *p);
int		render_loop(void);

#endif