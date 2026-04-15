#include "data.h"

int	exit_clean(void)
{
	t_render	*r;
	int i;

	i = 0;
	r = render();
	if (r->window != NULL)
		mlx_destroy_window(r->mlx, r->window);
	while (i < FRAMEBUFF)
	{
		if (r->frame_buff[i].img != NULL)
			mlx_destroy_image(r->mlx, r->frame_buff[i].img);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (i < 2)
			mlx_destroy_image(r->mlx, r->door_frame[i].img);
		mlx_destroy_image(r->mlx, r->wall_frame[i].img);
		i++;
	}
	if (render()->mlx != NULL)
		mlx_destroy_display(render()->mlx);
	free(r->mlx);
	lib_free_arr((void **)map()->door_arr, free);
	lib_free_arr((void **)map()->enemy_arr, free);
	lib_split_clean(map()->layout);
	if (r->start_time / 1000 != get_time() / 1000)
		printf("Average framerate %ld\n", r->total_frames / (get_time() / 1000 - r->start_time / 1000));
	exit(0);
	return (0);
}

void exit_error(char *msg)
{
	if (msg == NULL)
		perror(GAMENAME);
	else
		print_fd(2, "%s: %s\n", GAMENAME, msg);
	exit_clean();
}