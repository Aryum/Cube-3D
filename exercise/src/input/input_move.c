#include "input.h"

bool	has_input(void)
{
	if (key_read(key_w))
		return (true);
	if (key_read(key_s))
		return (true);
	if (key_read(key_a))
		return (true);
	if (key_read(key_d))
		return (true);
	return (false);
}

void	update_move(t_player *p)
{
	t_input		*input;
	float		rad;
	float		mod;

	input = data()->input;
	p->is_moving = has_input();
	rad = p->rot_rad;
	if (p->is_moving)
	{
		mod = 1;
		if (input[key_w].status)
			mod = 0.5;
		if (input[key_s].status)
		{
			rad = p->rot_rad + PI;
			mod = -0.5;
		}
		if (input[key_a].status)
			rad -= PI_90 * mod;
		if (input[key_d].status)
			rad += PI_90 * mod;
		p->pos = add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED / render()->fps));
	}
	p->mov_vct = ini_vct_rad(rad);
}

