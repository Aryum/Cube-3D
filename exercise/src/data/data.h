#ifndef DATA_H
# define DATA_H

#include "../cub.h"

//singletons
t_data		*data();
t_player	*player();
t_render	*render();
t_map		*map();
t_input		*input();

//free
int			exit_clean();

//ini
void	ini_data();


//vector

t_vct	ini_vector(float x, float y);
#endif