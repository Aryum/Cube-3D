#ifndef INPUT_H
# define INPUT_H

#include "../cub.h"

void	setup_inputs(t_data *dt);
void	input_loop(t_player *p, t_input *input);
int		key_press(int key);
int		key_release(int key);
#endif