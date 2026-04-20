#include "hlp.h"

static void	input_rot_x(t_player *p, float delta)
{
	p->rot_rad = add_rad(p->rot_rad, delta);
	p->rot_vct = ini_vct_rad(p->rot_rad);
}

static void	input_rot_y(t_player *p, float delta)
{
	p->tilt += delta;
	p->tilt = clamp(p->tilt, -PI_90, PI_90);
}

void	update_rot(t_player	*p)
{
	float	delta;

	delta = ROT_SPEED / render()->fps;
	if(key_read(key_right))
		input_rot_x(p, -delta);
	if(key_read(key_left))
		input_rot_x(p, delta);
	if (key_read(key_down))
		input_rot_y(p, -delta);
	if (key_read(key_up))
		input_rot_y(p, delta);

}
