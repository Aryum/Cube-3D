#include "input.h"

int	update_move()
{
	if (data()->input[key_a].status)
		player()->rot_rad += PI_90;
	if (data()->input[key_d].status)
		player()->rot_rad -= PI_90;
	if (data()->input[key_w].status)
		player()->rot_rad += PI;
	return 0;
}

