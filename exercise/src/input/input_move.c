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

static void wall_adjust(t_player *p, t_vct *mov)
{
	t_vct	v;
	t_vct	h;

	v = ini_vct_pos(0, sign(mov->y) * PLAYERSIZE);
	h = ini_vct_pos(sign(mov->x) * PLAYERSIZE, 0);
	if (hit_wall(pos_to_grid(add_vct(p->pos, v))))
		mov->y = 0;
	if (hit_wall(pos_to_grid(add_vct(p->pos, h))))
		mov->x = 0;
}


static void	update_pos(t_player *p, float rad)
{
	t_vct	pos;
	t_vct	mov;
	float	speed;

	p->mov_vct = ini_vct_rad(rad);
	speed = MOV_SPEED / render()->fps;
	mov = scale_vct(p->mov_vct, speed);
	if (BONUS)
		wall_adjust(p, &mov);
	pos = add_vct(p->pos, mov);
	pos.x = clamp(pos.x, 0, map()->scale.x);
	pos.y = clamp(pos.y, 0, map()->scale.y);
	p->pos = pos;
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
		update_pos(p, rad);
	}
}

