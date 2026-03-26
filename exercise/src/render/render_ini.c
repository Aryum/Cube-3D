/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:05:48 by ricsanto          #+#    #+#             */
/*   Updated: 2026/03/26 17:46:39 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	ini_frame(t_render *r, t_frame *f) // can have error
{
	f->img = mlx_new_image(r->mlx, r->window_x, r->window_y);
	f->addr = mlx_get_data_addr(f->img, &f->bits_pixel, &f->line_len, &f->end);
}

void	ini_buffer(t_render	*rnd) //can have error
{
	int	i;

	i = 0;
	while (i < FRAMEBUFF)
	{
		ini_frame(rnd, &rnd->frame_buff[i]);
		i++;
	}
}

void	render_ini()
{
	t_render	*rnd;

	rnd = render();
	rnd->last_time = get_time();
	
	rnd->frame_count = 0;
	rnd->start_time = get_time();
	rnd->window_x = 1280;
	rnd->window_y = 800;

	rnd->mlx = mlx_init();

	if (rnd->mlx == NULL)
		lib_error("Failed to ini window"); //exit clean
	
	rnd->window = mlx_new_window(rnd->mlx, rnd->window_x, rnd->window_y, "Cub3d");
		//clean on error
	ini_buffer(rnd);
		//clean on error
	
	mlx_hook(rnd->window, KeyPress, KeyPressMask, key_press, NULL);
	mlx_hook(rnd->window, KeyRelease, KeyReleaseMask, key_release, NULL);
	mlx_hook(rnd->window, DestroyNotify, NoEventMask, exit_clean, NULL);
	mlx_loop_hook(render()->mlx, render_loop, NULL);
	mlx_loop(render()->mlx);
}