#ifndef VAR_HLP_H
# define VAR_HLP_H

#include "../cub.h"

//	Quad

t_quad	ini_quad(t_vct grid);


//	Math

float	clamp(float val, float min, float max);
bool	reached_clamp(float *val, float min, float max);
float	f_abs(float a);
float	pow_2(float a);
float	add_rad(float rad, float delta);
float	sign(float a);

//	Vector

t_vct	ini_vct_rad(float rad);
t_vct	scale_vct(t_vct a, float factor);
t_vct	add_vct(t_vct a, t_vct b);
t_vct	ini_vct_pos(float x, float y);
float	dist_vct(t_vct a, t_vct b);
bool	equal_vct(t_vct a, t_vct b);

//	Time
long	get_time(void);

//door
t_door	*door_get(t_vct grid);
void	door_switch_state(t_vct grid);
bool	door_get_state(t_vct grid);

#endif