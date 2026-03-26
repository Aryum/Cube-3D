#ifndef RAY_H
# define RAY_H

#include "../cub.h"

//hlp
t_vct	grid_distance(t_vct pos, t_vct rot);
t_vct	pos_to_grid(t_vct pos);
t_vct	grid_to_pos(t_vct pos);
t_vct	raycast(t_ray ray);
bool	check_next_x(t_ray r);


//hits
bool hit_wall(t_vct grid_pos);

#endif