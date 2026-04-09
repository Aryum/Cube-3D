#include "hlp.h"

static void	put_image(t_render *r)
{
	t_frame	*cur;

	cur = &r->frame_buff[r->frame_cur];
	mlx_put_image_to_window(r->mlx, r->window, cur->img, 0 , 0);
	r->frame_cur++;
	if (r->frame_cur == FRAMEBUFF)
		r->frame_cur = 0;
	mlx_destroy_image(r->mlx, cur->img);
	cur->img = mlx_new_image(r->mlx, WINDOW_X, WINDOW_Y);
	if (cur->img == NULL)
		exit_error("Failed to create new image");
}

static void	updatefps(t_render *rnd)
{
	time_t	cur;
	long	a;

	cur = get_time();
	a = 500;
	rnd->total_frames++;
	if (cur - rnd->last_time > a)
	{
		rnd->fps = (rnd->frame_count) * (1000 / a);
		rnd->frame_count = 0;
		rnd->last_time = cur;
	}
	else
		rnd->frame_count++;
}



int render_loop(void)
{
	t_render *rnd;
	t_player	*p;

	rnd = render();
	p = player();

	//minimap
	if (!true)
		render_debug_map(p);
	else
		render_cub();

	if (BONUS)
		render_minimap(rnd);
	put_image(rnd);
	updatefps(rnd);
	if (rnd->fps == 1)
		return 0;
	update_rot();
	update_move();
	render_debug_str(rnd);
	return 0;
}
