#ifndef STRUCTS_H
# define STRUCTS_H


#define GRIDSIZE 64

#define PLAYERSIZE 10

#define FRAMEBUFF 50

#define ROT_SPEED 5.0

#define MOV_SPEED 25.0

#define WINDOW_X 1280
#define WINDOW_Y 720


#define BONUS 1

# define PI	3.14159
# define PI_360 6.28318
# define PI_90 1.57079

#define FOV PI_90

#define KEYCOUNT 10


typedef enum e_keys
{
	key_w,
	key_a,
	key_s,
	key_d,
	key_esc,
	key_left,
	key_right,
	key_up,
	key_down
}	t_keys;

typedef enum e_dir
{
	dir_north,
	dir_south,
	dir_east,
	dir_west
}	t_dir;

typedef enum e_axis
{
	X,
	Y
}	t_axis;

typedef struct s_vct
{
	float x;
	float y;
}	t_vct;

typedef struct s_ray
{
	t_vct	pos;
	t_vct	rot;
	t_vct	axis_dir[2];
	t_vct	cur_grid;
	t_vct	tar;
	bool	(*hit_cond)(t_vct);
}	t_ray;

typedef struct s_rayhit
{
	t_vct	pos;
	t_dir	dir;
	t_axis	axis;
	bool	sucess;
}	t_rayhit;

typedef struct s_player
{
	t_vct	pos;
	t_vct	grid;
	t_vct	grid_dist;
	t_vct	rot_vct;
	float	rot_rad;
	float	tilt;
	bool	is_moving;
	t_vct mov_vct;
}	t_player;


typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bits_pixel;
	int		line_len;
	int		end;
}	t_frame;

typedef	struct s_minimap
{
	t_vct	limit[2];
	t_vct	corner;
	t_vct	size ;
	t_vct	grid_size ;
	t_vct	center ;
}	t_minimap;

typedef struct s_render
{
	t_frame		frame_buff[FRAMEBUFF];
	t_minimap	minimap;
	float		fov_delta;
	float		fov_tar;
	float		resolution;
	void		*window;
	void		*mlx;
	time_t		last_time;
	time_t		start_time;
	long		total_frames;
	long		frame_count;
	long		fps;
	int			frame_cur;
}	t_render;

typedef struct s_quad
{
	t_vct pos[4];
	t_vct grid;

}	t_quad;


typedef struct s_map
{
	t_vct	scale;
	char	**layout;
	int		len_x;
	int		len_y;

}	t_map;

typedef struct s_input
{
	int		code;
	int		neg_key;
	bool	status;
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
