#include "data.h"

void	ini_data()
{
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


	printf("%s\n", layout);
	map()->layout = lib_split(layout, '\n');
	map()->size_x = lib_strlen(map()->layout[0]);
	while (map()->layout[map()->size_y] != NULL)
	{
		int i = 0;
		while (map()->layout[map()->size_y][i] != '\0')
		{
			if (map()->layout[map()->size_y][i] == 'P')
				player()->pos = ini_vct(i * GRIDSIZE + GRIDSIZE / 2, map()->size_y * GRIDSIZE + GRIDSIZE / 2);
			i++;
		}
		map()->size_y++;
	}

	render()->window_x = map()->size_x * GRIDSIZE;
	render()->window_y = map()->size_y * GRIDSIZE;
	player()->rot_vct = ini_vct(1,0);
	player()->rot_rad = acos(1);
}
