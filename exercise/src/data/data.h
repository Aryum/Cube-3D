#ifndef DATA_H
# define DATA_H

#include "../cub.h"

#define KEYCOUNT 5

typedef enum e_keys
{
	key_w = 119,
	key_a = 97,
	key_s = 115,
	key_d = 100,
	key_esc = 65307
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
	void		(*key_func[KEYCOUNT])( void );
	char		**map;

}	t_data;


t_data		*data(void);
t_player	*player(void);
t_render	*render(void);
void	clean_data(void);

#endif