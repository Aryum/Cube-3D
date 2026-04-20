#include "hlp.h"

void	input_loop(t_player *p, t_input *input)
{
	update_rot(p);
	update_move(p, input);
}
