/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:05:48 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/06 14:45:05 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	ini_frame(t_render *r, t_frame *f) // can have error
{
	f->img = mlx_new_image(r->mlx, r->window_x, r->window_y);
	f->addr = mlx_get_data_addr(f->img, &f->bits_pixel, &f->line_len, &f->end);
	f->bits_pixel = f->bits_pixel / 8;
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

t_minimap ini_minimap(t_render *rnd)
{
	t_minimap	ret;

	ret.corner = ini_vct_pos(rnd->window_x, rnd->window_y);
	ret.size = ini_vct_pos(200, 200);
	ret.grid_size = scale_vct(ret.size, 1/8.0);
	ret.size = add_vct(ret.size, ret.grid_size);
	ret.center = add_vct(ret.corner, scale_vct(ret.size, -0.6));
	ret.limit[0] = add_vct(ret.center,scale_vct(ret.size, -0.5));
	ret.limit[1] = add_vct(ret.center,scale_vct(ret.size, 0.5));
	return ret;
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
	rnd->minimap = ini_minimap(rnd); 
	rnd->mlx = mlx_init();
	rnd->ray_count = rnd->window_x;
	rnd->fov_delta = FOV / (float)rnd->ray_count;
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