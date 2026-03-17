#include "cub.h"

int	main()
{
	ini_data();
	render()->mlx = mlx_init();
	if (render()->mlx == NULL)
		return (lib_error("Failed to ini window"), 0);

	
	render()->window = mlx_new_window(render()->mlx, GRIDSIZE * map()->size_x, GRIDSIZE * map()->size_y, "Cub3d");
	mlx_hook(render()->window, KeyPress, KeyPressMask, key_press, NULL);
	mlx_hook(render()->window, DestroyNotify, NoEventMask, clean_data, NULL);
	mlx_loop_hook(render()->mlx, render_loop, NULL);
	mlx_loop(render()->mlx);

}