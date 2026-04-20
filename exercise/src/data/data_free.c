#include "data.h"

void	free_tile(void *ptr)
{
	t_tile	*tile;
	int		i;

	tile = ptr;
	i = 0;
	while (i < map()->len_x)
	{
		free(tile[i].content);
		i++;
	}
	free(ptr);
}

void	clean_img(t_render *r, void *img)
{
	if (img != NULL)
		mlx_destroy_image(r->mlx, img);
}
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
		clean_img(r, r->frame_buff[i].img);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (i < 2)
			clean_img(r, r->door_frame[i].img);
		clean_img(r, r->wall_frame[i].img);
		i++;
	}
	if (render()->mlx != NULL)
		mlx_destroy_display(render()->mlx);
	free(r->mlx);
	lib_free_arr((void **)map()->layout, free_tile);
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