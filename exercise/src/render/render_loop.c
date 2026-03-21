#include "render.h"

static void	loop_map(t_map	*mp, void (*f)(char **, int, int))
{
	int		x;
	int		y;

	y = 0;
	while (y < mp->size_y)
	{
		x = 0;
		while (x < mp->size_x)
		{
			f(mp->layout, x, y);
			x++;
		}
		y++;
	}
}

void draw(char **map, int x, int y)
{
	int border;
	t_vct limit;
	t_vct cur;

	if (map[y][x] != '1')
		return ;
	border = 1;
	cur.x = x * GRIDSIZE + border;
	cur.y = y * GRIDSIZE + border;
	limit.x = cur.x + GRIDSIZE - border * 2;
	limit.y = cur.y + GRIDSIZE - border * 2;
	while (cur.y < limit.y)
	{
		cur.x = x * GRIDSIZE + border;
		while (cur.x < limit.x)
		{
			put_pixel(cur.x, cur.y, 0xffffff);
			cur.x++;
		}
		cur.y++;
	}
}



void	updatefps(t_render *rnd)
{
	time_t	cur;
	long		a;

	cur = get_time();
	a = 500;
	if (cur - rnd->last_time > a)
	{
		rnd->fps = (rnd->frame_count) * ( 1000 / a);
		rnd->frame_count = 0;
		rnd->last_time = cur;
	}
	else
		rnd->frame_count++;
}

t_vct	pos_to_grid(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x / GRIDSIZE;
	ret.y = pos.y / GRIDSIZE;
	return (ret);
}

t_vct	grid_to_pos(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x * GRIDSIZE - GRIDSIZE / 2;
	ret.y = pos.y * GRIDSIZE - GRIDSIZE / 2;
	return (ret);
}
void increase(float *i)
{
	(*i)++;
}
void decrease(float *i)
{
	(*i)--;
}



t_vct	getfunc(t_vct start, float rad)
{
	float	s;
	float	c;

	s = sin(rad);
	c = cos(rad);
	start  = pos_to_grid(start);
	if (s == 1)
	{
		while (start.y >= 0)
		{
			if (map()->layout[(int)start.y][(int)start.x] == '1')
				return ini_vct(start.x, start.y);
			start.y--;
		}
		return ini_vct(-1, -1);
	}
	if (s == -1)
	{
		while (start.y < map()->size_y )
		{
			if (map()->layout[(int)start.y][(int)start.x] == '1')
				return ini_vct(start.x, start.y);
			start.y++;
		}
		return ini_vct(-1, -1);
	}
	if (c == 1)
	{
		while (start.x < map()->size_x)
		{
			if (map()->layout[(int)start.y][(int)start.x] == '1')
				return ini_vct(start.x, start.y);
			start.x++;
		}
		return ini_vct(-1, -1);
	}
	if (c == -1)
	{
		while ((int)start.x >= 0)
		{
			if (map()->layout[(int)start.y][(int)start.x] == '1')
				return ini_vct(start.x, start.y);
			start.x++;
		}
		return ini_vct(-1, -1);
	}

	float m = tan(rad);
	float b = start.y - start.x * m;
	void (*f_x)(float *);
	void (*f_y)(float *);

	if (cos(rad) > 0)
		f_x = increase;
	else
		f_x = decrease;

	if (sin(rad) > 0)
		f_y = increase;
	else
		f_y = decrease;

	while (1)
	{
		int x = clamp((start.y - b) / m, 0, map()->size_x);
		int y = clamp(start.x * m + b, 0, map()->size_y);
		
		if (x <= 0 || x >= map()->size_x)
			break;
		if (y <= 0 || y >= map()->size_y)
			break;
		if (map()->layout[y][x] == '1')
			return ini_vct(start.x, start.y);
		f_x(&start.x);
		f_y(&start.y);
	}
	return ini_vct(-1, -1);
}



int render_loop(void)
{
	t_render *rnd;
	t_player	*p;

	rnd = render();
	p = player();


	loop_map(map(), draw);
	draw_circle(p->pos, 5, 0xff0000);
	
	//vertical
	/*
	t_vct v = ini_vct(0,1);
	int y_pos =(int)floor(p->pos.y);
	draw_line(p->pos, add_vct(p->pos, scale_vct(v, ((p->rot_vct.y > 0) * GRIDSIZE - y_pos % GRIDSIZE)) ), 0xff00ae);
	int x_pos =(int)floor(p->pos.x);
	draw_line(p->pos, add_vct(p->pos, scale_vct(h, ( (p->rot_vct.x > 0) * GRIDSIZE - x_pos  % GRIDSIZE)) ), 0xff00ae );
	*/
	put_image(rnd);
	updatefps(rnd);

	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, 50) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, 30) ), 0x00ffcc);

	t_vct cast = getfunc(p->pos, p->rot_rad);
	if (cast.x != -1 && cast.y != -1)
		draw_line(p->pos, grid_to_pos(cast), 0x002200FF);


	// ===================== MOVE FROM HERE ===================== 
	if (rnd->fps == 1)
		return 0;
	update_rot(p);
	update_move(p);


	// ===================== MOVE FROM HERE ===================== c
	
	//fps
	char *fps = lib_itoa(render()->fps);
	mlx_string_put(rnd->mlx, rnd->window, 25, 25,0x00ff0000, fps);
	free(fps);

	//cords
	t_vct grid = pos_to_grid(player()->pos);
	char *x = lib_itoa(grid.x);
	char *y = lib_itoa(grid.y);
	mlx_string_put(rnd->mlx, rnd->window, 10, 50,0x002200FF, x);
	free(x);
	mlx_string_put(rnd->mlx, rnd->window, 40, 50,0x002200FF , y);
	free(y);

	//rot
	char *rot = lib_itoa((player()->rot_rad * 360) / (2 * PI));
	char *rot_tmp = lib_strjoin("rot: ", rot);
	free(rot);
	mlx_string_put(rnd->mlx, rnd->window, 10, 75,0x00ff00d9 , rot_tmp);
	free(rot_tmp);
	return 0;
}
