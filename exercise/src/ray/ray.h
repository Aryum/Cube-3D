#ifndef RAY_H
# define RAY_H

#include "../cub.h"

//ini
t_rayhit	ini_hit(t_ray *r, t_axis axis, float m, float b);
t_ray		ini_ray(t_vct start, t_vct rot, bool (*hit_cond)(t_vct));
t_rayhit	ini_miss(void);

//hlp
t_vct	grid_distance(t_vct pos);
t_vct	pos_to_grid(t_vct pos);
t_vct	grid_to_pos(t_vct pos);
bool	check_next_x(t_ray r);


//hits
bool hit_wall(t_vct grid_pos);
bool hit_any(t_vct grid_pos);
char get_map_char(t_vct grid_pos);

t_rayhit	raycast(t_ray ray);

#endif