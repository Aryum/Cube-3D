#include "hlp.h"

static bool fail_dir(t_player *p, t_vct vct[3])
{
	t_tile	*tile;
	t_vct	grid;
	int		i;

	i = 0;
	while (i < 3)
	{
		vct[i] = vct_scale(vct[i], PLAYERSIZE);
		grid = pos_to_grid(vct_add(p->pos, vct[i]));
		tile = tile_get(grid);
		draw_circle(vct_add(p->pos, vct[i]), 2, 0x00ff00);
		if (tile != NULL)
		{
			if (tile->val == tile_wall || tile->playable == tile_enemy)
				return (true);
			if (tile->val == 'D' && !((t_door *)tile->content)->open)
				return (true);
		}
		i++;
	}
	return (false);
}

static bool	has_input(void)
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
	t_vct	v[3];
	t_vct	h[3];

	v[0] = ini_vct_pos(0, sign(mov->y));
	v[1] = vct_norm(ini_vct_pos(1, sign(mov->y)));
	v[2] = vct_norm(ini_vct_pos(-1, sign(mov->y)));
	h[0] = ini_vct_pos(sign(mov->x), 0);
	h[1] = vct_norm(ini_vct_pos(sign(mov->x), 1));
	h[2] = vct_norm(ini_vct_pos(sign(mov->x), -1));
	if (fail_dir(p, v))
		mov->y = 0;
	if (fail_dir(p, h))
		mov->x = 0;
}

static void	update_pos(t_player *p, float rad)
{
	t_vct	pos;
	t_vct	mov;
	t_vct	grid;
	float	speed;

	p->mov_vct = ini_vct_rad(rad);
	speed = MOV_SPEED / render()->fps;
	mov = vct_scale(p->mov_vct, speed);
	if (BONUS)
		wall_adjust(p, &mov);
	pos = vct_add(p->pos, mov);
	pos.x = clamp(pos.x, 0, map()->scale.x - 1);
	pos.y = clamp(pos.y, 0, map()->scale.y - 1);
	p->pos = pos;
	p->grid_dist = grid_distance(pos);
	grid = pos_to_grid(pos);
	if (grid.x != p->grid.x || grid.y != p->grid.y)
	{
		map()->layout[(int)p->grid.y][(int)p->grid.x].playable = '\0';
		map()->layout[(int)grid.y][(int)grid.x].playable = 'P';
		p->grid = grid;
	}
}

void	update_move(t_player *p, t_input *input)
{
	float		rad;
	float		mod;

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

