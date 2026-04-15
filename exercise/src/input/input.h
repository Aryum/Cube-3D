#ifndef INPUT_H
# define INPUT_H

#include "../cub.h"

//call
int		key_press(int key);
int		key_release(int key);
bool	key_read(t_keys key);
int		input_interact(void);

//setuo
void	setup_inputs();

//rotate
void	update_move(void);
void	update_rot(void);

#endif