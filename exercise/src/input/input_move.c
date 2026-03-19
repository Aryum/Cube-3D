#include "input.h"

int	update_move()
{
	t_player	*p;
	float		rad;
	float		mod;

	p = player();
	rad = p->rot_rad;
	mod = 1;
	if (data()->input[key_w].status)
		mod = 0.5;
	if (data()->input[key_s].status)
	{
		rad = p->rot_rad + PI;
		mod = -0.5;
	}
	if (data()->input[key_a].status)
		rad -= PI_90 * mod;
	if (data()->input[key_d].status)
		rad += PI_90 * mod;
	p->mov_vct = rad_vector(rad);
	return (0);
}

