#ifndef INPUT_H
# define INPUT_H

#include "../cub.h"

//call
int		key_press(int key);
int		key_release(int key);
bool	key_read(t_keys key);

//setuo
void	setup_inputs();

//rotate
void	update_move(t_player *p);
void	update_rot(t_player *p);

#endif