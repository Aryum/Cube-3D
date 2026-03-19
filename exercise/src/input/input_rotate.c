#include "input.h"

void input_rot_x(float delta)
{
	t_player	*p;

	p = player();
	p->rot_rad += delta;
	if (p->rot_rad > 2 * PI)
		p->rot_rad -= 2 * PI;
	else if (p->rot_rad < 0)
		p->rot_rad += 2 * PI;
	p->rot_vct = rad_vector(p->rot_rad);
}

int	rot_left()
{
	if (render()->fps != 0)
		input_rot_x(-ROT_SPEED / render()->fps);
	return (0);
}

int	rot_right()
{
	if (render()->fps != 0)
		input_rot_x(ROT_SPEED / render()->fps);
	return (0);
}