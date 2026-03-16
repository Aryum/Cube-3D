#ifndef DATA_H
# define DATA_H

#include "../cub.h"

#define KEYCOUNT 5

typedef enum e_keys
{
	key_w,
	key_a,
	key_s,
	key_d,
	key_esc
}	t_keys;

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

typedef struct s_player
{
	t_vector pos;
}	t_player;

typedef struct s_render
{
	void	*window;
	void	*mlx;
	int		fps;
}	t_render;

typedef struct s_data
{
	t_player	player;
	t_render	render;
	int			key_code[KEYCOUNT];
	int			(*key_func[KEYCOUNT])( void );
	char		**map;

}	t_data;

t_data		*data();
t_player	*player();
t_render	*render();
int			key_press(int key);
int			clean_data();

void	ini_data();

#endif