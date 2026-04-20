#ifndef DATA_H
# define DATA_H

#include "../cub.h"

//singletons
t_data		*data();
t_player	*player();
t_render	*render();
t_map		*map();

//free
int		exit_clean();
void	exit_error(char *msg);

//ini
bool	ini_data(t_data *d, t_map *m);



#endif