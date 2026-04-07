#include "hlp.h"

void	render_ini()
{
	t_render	*rnd;

	rnd = render();
	setup_settings(rnd);
	if (!setup_mlx(rnd))
		exit_error("Failed to setup mlx");
	mlx_loop(render()->mlx);
}