#ifndef DATA_H
# define DATA_H

#include "../std_header.h"

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

typedef struct s_player
{
	t_vector pos;
}	t_player;

typedef struct s_data
{
	t_player	player;
	char		**map;
}	t_data;


t_data		*data();
t_player	*player();


#endif