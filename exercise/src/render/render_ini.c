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
	f->addr = mlx_get_data_addr(f->img, &f->byte_pixel, &f->line_len, &f->end);
	f->byte_pixel = f->byte_pixel / 8;
	return (true);
}
void	render_ini()
{
	t_render	*rnd;

	rnd = render();
	setup_settings(rnd);
	if (!setup_mlx(rnd))
		exit_error("Failed to setup mlx");
	if(!ini_image(rnd, "test.xpm", &rnd->test_img))
	{
		printf("fuck\n");
		exit_clean(NULL);

		return;
	}
	mlx_loop(rnd->mlx);
	mlx_destroy_image(rnd->mlx, rnd->test_img.img);
	exit_clean(NULL);
}