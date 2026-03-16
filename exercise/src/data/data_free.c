#include "data.h"

int	clean_data(void)
{
	if (render()->window != NULL)
		mlx_destroy_window(render()->mlx, render()->window);
	if (render()->mlx != NULL)
		mlx_destroy_display(render()->mlx);
	free(render()->mlx);
	lib_split_clean(data()->map);
	exit(0);
	return (0);
}