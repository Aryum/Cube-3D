#include "render.h"

//update this to a readable thing

void	put_image(t_render *rnd)
{
	t_frame	*cur;

	cur = &rnd->frame_buff[rnd->frame_cur];
	mlx_put_image_to_window(rnd->mlx, rnd->window, cur->img, 0 , 0);
	rnd->frame_cur++;
	if (rnd->frame_cur == FRAMEBUFF)
		rnd->frame_cur = 0;
	mlx_destroy_image(rnd->mlx, cur->img);
	cur->img = mlx_new_image(rnd->mlx, rnd->window_x, rnd->window_y);
}
