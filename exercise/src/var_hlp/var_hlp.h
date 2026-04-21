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
t_vct	ini_vct_pos(float x, float y);
t_vct	ini_vct_rad(float rad);
t_vct	ini_vct_vct(t_vct a, t_vct b);
t_vct	ini_vct_dir(t_dir dir);

t_vct	vct_scale(t_vct a, float factor);
t_vct	vct_add(t_vct a, t_vct b);
float	vct_dist(t_vct a, t_vct b);
bool	vct_cmp(t_vct a, t_vct b);
float	vct_angle(t_vct vct);
t_vct	vct_norm(t_vct vct);
float	vct_size(t_vct vct);

//	Time
long	get_time(void);

//door
t_door	*door_get(t_vct grid);
void	door_switch_state(t_vct grid);
bool	door_get_state(t_vct grid);

//tile
char	tile_get_char(t_vct grid);
t_tile	*tile_get(t_vct grid);

#endif