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
void	ini_data(t_data *d, t_map *m);


//vector

t_vct	ini_vct_pos(float x, float y);
t_vct	scale_vct(t_vct a, float factor);
t_vct	add_vct(t_vct a, t_vct b);
t_vct	ini_vct_rad(float rad);

#endif