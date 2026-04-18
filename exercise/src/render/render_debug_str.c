#include "hlp.h"

static void	fps(t_render *rnd)
{
	char	*fps;

	fps = lib_itoa(rnd->fps_display);
	if (fps != NULL)
		mlx_string_put(rnd->mlx, rnd->window, 25, 25, 0x00ff0000, fps);
	free(fps);
}

static void	cords(t_render *rnd)
{
	t_vct grid;
	char *x;
	char *y;

	grid = grid_distance(player()->pos);
	x = lib_itoa((int) (grid.x) );
	y = lib_itoa((int) (grid.y));
	if (x != NULL)
		mlx_string_put(rnd->mlx, rnd->window, 10, 50,0x002200FF, x);
	free(x);
	if (y != NULL)
		mlx_string_put(rnd->mlx, rnd->window, 40, 50, 0x002200FF , y);
	free(y);
}

static void	rot(t_render *rnd)
{
	char	*rot;
	char	*rot_tmp;

	rot = lib_itoa((player()->tilt * 360) / (PI_360));
	rot_tmp = lib_strjoin("rot: ", rot);
	free(rot);
	if (rot_tmp != NULL)
		mlx_string_put(rnd->mlx, rnd->window, 10, 75,0x00ff00d9 , rot_tmp);
	free(rot_tmp);
}

void	render_debug_str(t_render *rnd)
{
	fps(rnd);
	cords(rnd);
	rot(rnd);
}