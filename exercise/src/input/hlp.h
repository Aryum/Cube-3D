#ifndef HLP_H
# define HLP_H

#include "input.h"

//call
bool	key_read(t_keys key);
int		input_interact(void);


//rotate
void	update_rot(t_player *p);
void	update_move(t_player *p, t_input *input);


#endif