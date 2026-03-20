#include "input.h"

static void	input_rot_x(t_player *p, float delta)
{
	p->rot_rad += delta;
	if (p->rot_rad > 2 * PI)
		p->rot_rad -= 2 * PI;
	else if (p->rot_rad < 0)
		p->rot_rad += 2 * PI;
	p->rot_vct = rad_vector(p->rot_rad);
}

void	update_rot(t_player *p)
{
	if(key_read(key_right))
		input_rot_x(p, -ROT_SPEED / render()->fps);
	if(key_read(key_left))
		input_rot_x(p, ROT_SPEED / render()->fps);
}
