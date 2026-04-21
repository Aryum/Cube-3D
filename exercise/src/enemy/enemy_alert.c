#include "hlp.h"

void	enemy_alert(t_enemy *e)
{
	t_rayhit	hit;
	t_vct		dir;
	
	dir = ini_vct_vct(e->pos, player()->pos);
	hit = raycast(ini_ray(e->pos, dir, NULL), hit_)
	if ()
	enemy
}