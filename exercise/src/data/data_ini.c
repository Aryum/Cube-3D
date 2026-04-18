#include "data.h"


bool	create_enemy(t_tile *tile)
{
	t_door	*enemy;

	enemy = lib_calloc(1, sizeof(t_enemy));
	if (enemy == NULL)
		return (false);
	tile->content = enemy;
	return (true);
}

bool	create_door(t_tile *tile)
{
	t_door	*door;

	door = lib_calloc(1, sizeof(t_door));
	if (door == NULL)
		return (false);
	door->open = false;
	tile->content = door;
	return (true);
}

void ini_player(int x, int y)
{
	t_player	*p;

	p = player();
	p->grid = ini_vct_pos(x, y);
	x = x * GRIDSIZE + GRIDSIZE / 2;
	y = y * GRIDSIZE + GRIDSIZE / 2;
	p->pos = ini_vct_pos(x , y);
	p->rot_vct = ini_vct_pos(1,0);
	p->rot_rad = 0;
	p->tilt = 0;
}
bool create_tile(char c, t_tile *tile)
{
	lib_bzero(tile, sizeof(t_tile));
	if (c == 'P' || c == 'E')
	{
		tile->playable = c;
		tile->val = '0';
		if (c == 'E')
			return (create_enemy(tile));
		return (true);
	}
	else
	{
		tile->playable = '\0';
		tile->val = c;
		if (c == 'D')
			return (create_door(tile));
		return (true);
	}
}


void	ini_data()
{
	t_map *m;

	m = map();
	setup_inputs();


	render()->fps=1;
	char *str = "\
111111111111\n\
100000E00001\n\
100P00000001\n\
10000011D111\n\
100100D00001\n\
100000100001\n\
111111111111";

	char **layout =lib_split(str, '\n');
	m->len_x = lib_strlen(layout[0]);

	while(layout[m->len_y] != NULL)
		m->len_y++;
	m->layout = lib_calloc(m->len_y + 1, sizeof(t_tile *));
		//can give error
	int y = 0;
	while (y < m->len_y)
	{
		int x = 0;
		m->layout[y] = lib_calloc(m->len_x, sizeof(t_tile));
			//can give error
		while (x < m->len_x)
		{
			if (!create_tile(layout[y][x], &m->layout[y][x]))
				break; //error
			if (layout[y][x] == 'P')
				ini_player(x, y);
			x++;
		}
		y++;
	}
	lib_split_clean(layout);
	

	m->scale = ini_vct_pos(GRIDSIZE * m->len_x, GRIDSIZE * m->len_y);
}
