#include "hlp.h"

void	game_start()
{
	t_render *r;

	r = render();
	ini_data(data(), map());
	setup_settings(r);
	setup_mlx(r);
	render_ini(r);
	mlx_loop(r->mlx);
	exit_clean(NULL);
}