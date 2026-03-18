#ifndef STRUCTS_H
# define STRUCTS_H

#define KEYCOUNT 5

#define GRIDSIZE 64

#define FRAMEBUFF 3

#define ROTSPEED 0.5

#define PI 3.14159

typedef enum e_keys
{
	key_w,
	key_a,
	key_s,
	key_d,
	key_esc
}	t_keys;

typedef struct s_vct
{
	float x;
	float y;
}	t_vct;

typedef struct s_player
{
	t_vct pos;
	float rot_rad;
	t_vct rot_vct;
}	t_player;


typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bits_pixel;
	int		line_len;
	int		end;
}	t_frame;

typedef struct s_render
{
	t_frame	frame_buff[FRAMEBUFF];
	int		frame_cur;
	void	*window;
	void	*mlx;
	time_t	last_time;
	long	frame_count;
	long	fps;
	int		window_x;
	int		window_y;

}	t_render;

typedef struct s_map
{
	char	**layout;
	int		size_x;
	int		size_y;
}	t_map;

typedef struct s_input
{
	int		code;
	bool	status;
	bool	hold_call;
	int		(*func)( void );
}	t_input;

typedef struct s_data
{
	t_player	player;
	t_render	render;
	t_map		map;
	t_input		input[KEYCOUNT];
}	t_data;

#endif