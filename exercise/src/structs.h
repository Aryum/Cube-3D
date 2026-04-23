#ifndef STRUCTS_H

# define STRUCTS_H


# define GAMENAME "Cube"

#define GRIDSIZE 64

#define PLAYERSIZE 10

#define FRAMEBUFF 50

#define ROT_SPEED 5.0

#define MOV_SPEED 75.0

#define RAYCOUNT 640

#define WINDOW_X 1280
#define WINDOW_Y 720


#define BONUS 1

# define PI	3.14159
# define PI_360 6.28318
# define PI_90 1.57079

#define FOV 1.04719

#define KEYCOUNT 10


typedef enum e_keys
{
	key_w,
	key_a,
	key_s,
	key_d,
	key_e,
	key_esc,
	key_left,
	key_right,
	key_up,
	key_down
}	t_keys;


typedef enum e_tile_char
{
	tile_wall  = '1',
	tile_empty  = '0',
	tile_enemy  = 'E',
	tile_door = 'D',
	tile_player = 'P',
}	t_tile_char;

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

typedef struct s_draw_ray
{
	t_vct	last_grid;
	t_vct	pos_vct;
	t_vct	dir_vct;
	float	cos_adjust;
	int		i;
	bool	first;
}	t_draw_ray;

typedef struct s_ray
{
	t_vct		start_pos;
	t_vct		dir;
	t_vct		axis_dir[2];
	t_vct		cur_grid;
	t_vct		cur_pos;
	t_vct		tar;
	t_vct		skip_grid;
	t_axis		cur_axis;
	bool		(*hit)(struct s_ray *);
	bool		(*fail)(struct s_ray *);
	bool		check_done;
	float		m;
	float		b;
}	t_ray;

typedef struct s_rayhit
{
	t_vct		ray;
	t_vct		pos;
	t_vct		grid;
	t_dir		dir;
	t_axis		axis;
	char		c;
	bool		sucess;

}	t_rayhit;

typedef struct s_player
{
	t_vct	pos;
	t_vct	grid;
	t_vct	grid_dist;
	t_vct	rot_vct;
	t_vct	mov_vct;
	float	rot_rad;
	float	tilt;
	bool	is_moving;
}	t_player;


typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bp;
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
	t_vct		fov_adj;
	t_minimap	minimap;
	float		ray_width;
	float		ray_delta_angle;
	void		*window;
	void		*mlx;
	time_t		last_time;
	time_t		start_time;
	long		total_frames;
	long		fps;
	long		fps_display;
	int			frame_cur;
	t_frame		wall_frame[4];
	t_frame		door_frame[2];
}	t_render;

typedef struct s_quad
{
	t_vct pos[4];
	t_vct grid;

}	t_quad;

typedef struct s_door
{
	bool	open;
}	t_door;

typedef struct s_enemy
{
	t_vct	grid;
	t_vct	pos;
	int		health;
	bool	alerted;
}	t_enemy;


typedef struct s_tile
{
	void	*content;
	char	val;
	char	playable;
}	t_tile;

typedef struct s_map
{
	t_tile	**layout;
	t_vct	scale;
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
	bool		debug_2d;
}	t_data;

#endif
