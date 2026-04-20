#include "hlp.h"

bool ini_image(t_render *r, char *path, t_frame *f)
{
	int		x;
	int		y;

	x = GRIDSIZE;
	y = GRIDSIZE;
	f->img = mlx_xpm_file_to_image(r->mlx, path, &x, &y);
	if (f->img == NULL)
		return (false);
	f->addr = mlx_get_data_addr(f->img, &f->bp, &f->line_len, &f->end);
	f->bp = f->bp / 8;
	return (true);
}

void	render_ini_images(t_render *r)
{
	r->fps = 1;
	if(!ini_image(r, "NORTH.xpm", &r->wall_frame[dir_north]))
	{
		exit_clean(NULL);
	}
	if(!ini_image(r, "SOUTH.xpm", &r->wall_frame[dir_south]))
	{
		exit_clean(NULL);
	}
	if(!ini_image(r, "EAST.xpm", &r->wall_frame[dir_east]))
	{
		exit_clean(NULL);
	}
	if(!ini_image(r, "WEST.xpm", &r->wall_frame[dir_west]))
	{
		exit_clean(NULL);
	}


	//doesnt need refactor
	if(!ini_image(r, "close.xpm", &r->door_frame[0]))
	{
		exit_clean(NULL);
	}
		if(!ini_image(r, "open.xpm", &r->door_frame[1]))
	{
		exit_clean(NULL);
	}
}