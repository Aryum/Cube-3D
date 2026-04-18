#include "cub.h"

int	main(int ac, char **av)
{
	if (ac >= 2)
		data()->debug_2d = lib_strncmp(av[1], "debug", 6) == 0;
	if (0)
		parse(ac, av);
	ini_data();
	render_ini();

}
