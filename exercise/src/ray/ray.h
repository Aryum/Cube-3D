#ifndef RAY_H
# define RAY_H

#include "../cub.h"

//ini
t_rayhit	ini_hit(t_ray *r);
t_rayhit	ini_hit_start(t_ray *r);

t_ray		ini_ray(t_vct s, t_vct rot, t_vct *skip_grid);
t_rayhit	ini_miss(void);
t_axis		get_hit_axis(t_ray *r);
t_rayhit	ret_hit(t_ray *r, t_vct pos,  t_dir dir);
t_rayhit	ret_hit_start(t_ray *r, t_vct pos, t_dir dir);


//hlp
t_vct	grid_distance(t_vct pos);
t_vct	pos_to_grid(t_vct pos);
t_vct	grid_to_pos(t_vct pos);
bool	check_next_x(t_ray r);


//hits
bool hit_wall(t_ray *r);
bool miss_rnd_backdoor(t_ray *r);
bool hit_door(t_ray *r);
bool hit_rnd_backdoor(t_ray *r);
bool hit_door_open(t_ray *r);

char get_map_char(t_vct grid_pos);


t_rayhit	raycast(t_ray ray, bool (*hit)(t_ray *), bool (*fail)(t_ray *));

#endif