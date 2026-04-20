#include "hlp.h"

int	game_loop(void)
{
	t_player	*p;
	t_render	*r;

	p = player();
	r = render();
	render_loop(p, r);
	input_loop(p, data()->input);
	return (0);
}