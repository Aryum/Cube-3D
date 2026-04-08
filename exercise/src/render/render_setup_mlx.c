#include "hlp.h"

static bool	ini_frame(t_render *r, t_frame *f)
{
	f->img = mlx_new_image(r->mlx, WINDOW_X, WINDOW_Y);
	if (f->img == NULL)
		return (false);
	f->addr = mlx_get_data_addr(f->img, &f->byte_pixel, &f->line_len, &f->end);
	f->byte_pixel = f->byte_pixel / 8;
	return (true);
}

static bool	ini_buffer(t_render	*rnd)
{
	int	i;

	i = 0;
	while (i < FRAMEBUFF)
	{
		if (!ini_frame(rnd, &rnd->frame_buff[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	setup_mlx(t_render	*rnd)
{
	rnd->mlx = mlx_init();
	if (rnd->mlx == NULL)
		return (false);
	if (!ini_buffer(rnd))
		return (false);
	rnd->window = mlx_new_window(rnd->mlx, WINDOW_X, WINDOW_Y, "Cub3d");
	if (rnd->window == NULL)
		return (false);
	mlx_hook(rnd->window, KeyPress, KeyPressMask, key_press, NULL);
	mlx_hook(rnd->window, KeyRelease, KeyReleaseMask, key_release, NULL);
	mlx_hook(rnd->window, DestroyNotify, NoEventMask, exit_clean, NULL);
	mlx_loop_hook(render()->mlx, render_loop, NULL);
	return (true);
}