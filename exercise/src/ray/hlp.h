
#ifndef HLP_H
# define HLP_H

#include "ray.h"

bool	check_next_x(t_ray r);

t_axis		get_hit_axis(t_ray *r);

t_rayhit	ret_hit(t_ray *r, t_dir dir);

t_rayhit	ret_hit_start(t_ray *r, t_dir dir);
void		update_ray_pos(t_ray *r);

#endif