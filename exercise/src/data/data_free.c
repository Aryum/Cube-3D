#include "data.h"

int	exit_clean(void)
{
	int i;

	i = 0;
	if (render()->window != NULL)
		mlx_destroy_window(render()->mlx, render()->window);
	while (i < FRAMEBUFF)
	{
		mlx_destroy_image(render()->mlx, render()->frame_buff[i].img);
		i++;
	}
	if (render()->mlx != NULL)
		mlx_destroy_display(render()->mlx);
	free(render()->mlx);
	lib_split_clean(map()->layout);
	exit(0);
	return (0);
}

void clean_error(char *msg)
{
	if (msg == NULL)
		perror(GAMENAME);
	else
		print_fd(2, "%s: $s", GAMENAME, msg);
	exit_clean();
}