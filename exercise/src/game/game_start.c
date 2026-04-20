#include "hlp.h"

void	game_start()
{
	t_render *r;

	r = render();
	if(!ini_data(data(), map()))
		exit_error("Failed to ini data");
	if (!setup_mlx(r))
		exit_error("Failed to setup mlx");
	render_ini_images(r);
	setup_settings(r);
	mlx_loop(r->mlx);
	exit_clean(NULL);
}