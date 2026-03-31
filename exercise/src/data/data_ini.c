#include "data.h"

void	ini_data()
{
	t_map *m;
	
	m = map();
	setup_inputs();

	render()->fps=1;
	char *layout = "\
111111111111\n\
100000000001\n\
100P00000001\n\
100000111111\n\
100000000001\n\
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
				player()->pos = ini_vct_pos(i * GRIDSIZE + GRIDSIZE / 2, map()->len_y * GRIDSIZE + GRIDSIZE / 2);
			i++;
		}
		m->len_y++;
	}

	m->scale = ini_vct_pos(GRIDSIZE * m->len_x, GRIDSIZE * m->len_y);
	player()->rot_vct = ini_vct_pos(1,0);
	player()->rot_rad = 0;
}
