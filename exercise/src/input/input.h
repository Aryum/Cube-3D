#ifndef INPUT_H
# define INPUT_H

#include "../cub.h"

//call
int		key_press(int key);
int		key_release(int key);
void	key_hold();

//setuo
void	setup_inputs();

//rotate
int	rot_left();
int	rot_right();
int	update_move();

#endif