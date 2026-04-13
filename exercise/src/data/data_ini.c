#include "data.h"

void	*create_door(t_vct pos)
{
	t_door	*door;

	door = lib_calloc(1, sizeof(t_door));
	if (door != NULL)
	{
		door->open = false;
		door->pos = pos;
	}
	return (door);
}

void	*create_enemy(t_vct pos)
{
	t_enemy	*enemy;

	enemy = lib_calloc(1, sizeof(t_enemy));
	if (enemy != NULL)
		enemy->pos = pos;
	return (enemy);
}

bool	add_content(t_list **lst, t_vct pos, void *(*f)(t_vct))
{
	t_list	*tmp;
	void	*content;

	content = f(pos);
	if (content == NULL)
		return (false);
	tmp = lst_new(content);
	if (tmp == NULL)
		return (false);
	lst_add_back(lst, tmp);
	return (true);
}

void	ini_data()
{
	t_map *m;
	t_list	*enemy_lst;
	t_list	*door_lst;
	enemy_lst = NULL;
	door_lst = NULL;

	m = map();
	setup_inputs();


	render()->fps=1;
	char *layout = "\
111111111111\n\
100000E00001\n\
100P00000001\n\
100000111111\n\
100000D00001\n\
100000100001\n\
111111111111";


	m->layout = lib_split(layout, '\n');
	m->len_x = lib_strlen(m->layout[0]);
	while (m->layout[m->len_y] != NULL)
	{
		int i = 0;
		while (m->layout[m->len_y][i] != '\0')
		{
			if (m->layout[m->len_y][i] == 'P')
			{
				player()->pos = ini_vct_pos(i * GRIDSIZE + GRIDSIZE / 2, map()->len_y * GRIDSIZE + GRIDSIZE / 2);
				player()->grid = ini_vct_pos(i,m->len_y);
			}
			if (m->layout[m->len_y][i] == 'E')
				add_content(&enemy_lst, ini_vct_pos(i, m->len_y), create_enemy);
			if (m->layout[m->len_y][i] == 'D')
				add_content(&door_lst, ini_vct_pos(i, m->len_y), create_door);
			i++;
		}
		m->len_y++;
	}

	m->scale = ini_vct_pos(GRIDSIZE * m->len_x, GRIDSIZE * m->len_y);
	if (door_lst != NULL)
	{
		m->door_arr = (t_door **)lst_to_arr(&door_lst);
		for (int i = 0; m->door_arr[i] != NULL; i++)
			printf("Door at (%f, %f)\n", m->door_arr[i]->pos.x, m->door_arr[i]->pos.y);
	}
	if (enemy_lst != NULL)
	{
		m->enemy_arr = (t_enemy **)lst_to_arr(&enemy_lst);
		for (int i = 0; m->enemy_arr[i] != NULL; i++)
			printf("Enemy at (%f, %f)\n", m->enemy_arr[i]->pos.x, m->enemy_arr[i]->pos.y);
	}

	player()->rot_vct = ini_vct_pos(1,0);
	player()->rot_rad = 0;
	player()->tilt = 0;
	exit_clean();
}
