#include "render.h"

static void	loop_map(t_map	*mp, void (*f)(char **, int, int))
{
	int		x;
	int		y;

	y = 0;
	while (y < mp->size_y)
	{
		x = 0;
		while (x < mp->size_x)
		{
			f(mp->layout, x, y);
			x++;
		}
		y++;
	}
}

void draw(char **map, int x, int y)
{
	int border;
	t_vct limit;
	t_vct cur;

	if (map[y][x] != '1')
		return ;
	border = 1;
	cur.x = x * GRIDSIZE + border;
	cur.y = y * GRIDSIZE + border;
	limit.x = cur.x + GRIDSIZE - border * 2;
	limit.y = cur.y + GRIDSIZE - border * 2;
	while (cur.y < limit.y)
	{
		cur.x = x * GRIDSIZE + border;
		while (cur.x < limit.x)
		{
			put_pixel(cur.x, cur.y, 0xffffff);
			cur.x++;
		}
		cur.y++;
	}
}

long get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit_clean(NULL);
	return (tv.tv_sec);
}

void	updatefps(t_render *rnd)
{
	time_t cur;

	cur = get_time();
	if (cur != rnd->last_time)
	{
		rnd->fps = rnd->frame_count / (cur - rnd->last_time);
		rnd->frame_count = 0;
		rnd->last_time = cur;
	}
	else
		rnd->frame_count++;

	char  *a = lib_itoa(rnd->fps);
	mlx_string_put(rnd->mlx, rnd->window, 25, 25,0xff000000, a);
	free(a);
}



int render_loop(void)
{
	t_render *rnd;

	rnd = render();
	loop_map(map(), draw);
	put_image(rnd);
	updatefps(rnd);

	char *x = lib_itoa(player()->pos.x);
	char *y = lib_itoa(player()->pos.y);

	mlx_string_put(rnd->mlx, rnd->window, 10, 50,0x00ff00d9, x);
	mlx_string_put(rnd->mlx, rnd->window, 40, 50,0x00ff00d9 , y);
	free(x);
	free(y);
	draw_circle(player()->pos, 5, 0xff0000);
	draw_line(player()->pos, ini_vector(player()->pos.x + 50, player()->pos.y + 50),0xfffb00);
	return 0;
}
