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
	float	delta;

	cur = get_time();
	rnd->total_frames++;
	delta = cur - rnd->last_time;
	rnd->fps = 1000 / delta;
	rnd->last_time = cur;
	if (cur % 50 == 0)
		rnd->fps_display = rnd->fps;
}

void render_loop(t_player *p, t_render *r)
{
	if (data()->debug_2d)
		render_debug_map(p);
	else
		render_cub(p, r);
	if (BONUS)
		render_minimap(r);
	put_image(r);
	updatefps(r);
	render_debug_str(r);
}
