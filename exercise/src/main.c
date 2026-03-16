#include "cub.h"

int	main()
{
	render()->mlx = mlx_init();
	if (render()->mlx == NULL)
		return (lib_error("Failed to ini window"), 0);
	render()->window = mlx_new_window(render()->mlx, 500, 500, "Long Souls");


}