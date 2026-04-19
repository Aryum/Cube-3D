#include "input.h"

int	input_interact(void)
{
	t_rayhit	hit;

	hit = raycast(ini_ray(player()->pos, player()->rot_vct, hit_door, hit_wall));
	if (hit.sucess && !vct_cmp(hit.grid, player()->grid) )
		door_switch_state(hit.grid);
	return (0);
}