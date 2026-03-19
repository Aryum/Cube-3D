#include "input.h"

int	update_move()
{
	player()->mov_rad = player()->rot_rad;
	if (data()->input[key_a].status)
		player()->mov_rad += PI_90;
	if (data()->input[key_d].status)
		player()->mov_rad -= PI_90;
	if (data()->input[key_w].status)
		player()->rot_rad += PI;
	return 0;
}

