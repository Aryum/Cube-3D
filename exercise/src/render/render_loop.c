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

	border = 1;
	if (map[y][x] == '1')
	{
		cur.x = x * GRIDSIZE + border;
		cur.y = y * GRIDSIZE + border;
		limit.x = cur.x + GRIDSIZE - border;
		limit.y = cur.y + GRIDSIZE - border;
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

	ret.x = (int)pos.x / GRIDSIZE;
	ret.y = (int)pos.y / GRIDSIZE;
	return (ret);
}

t_vct	grid_to_pos(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x * GRIDSIZE + GRIDSIZE / 2;
	ret.y = pos.y * GRIDSIZE + GRIDSIZE / 2;
	return (ret);
}

void increase(float *i)
{
	(*i)+=GRIDSIZE;
}
void decrease(float *i)
{
	(*i)-=GRIDSIZE;
}

t_vct	getfunc(t_vct start, float rad)
{
	t_vct vct;
	float scale;

	vct = rad_vector(rad);

	while (1)
	{
		start = add_vct(start, vct);
		if (reached_clamp(&start.x, 0, render()->window_x))
			break;
		if (reached_clamp(&start.y, 0, render()->window_y))
			break;
		t_vct tmp = pos_to_grid(start);
		if (map()->layout[(int) tmp.y][(int) tmp.x] == '1')
			return (start);
	}
	return (ini_vct(-1, -1));
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
	t_vct v = ini_vct(0,1);
	int y_pos =(int)floor(p->pos.y);
	draw_line(p->pos, add_vct(p->pos, scale_vct(v, ((p->rot_vct.y > 0) * GRIDSIZE - y_pos % GRIDSIZE)) ), 0xff00ae);
	t_vct h = ini_vct(1,0);
	int x_pos =(int)floor(p->pos.x);
	draw_line(p->pos, add_vct(p->pos, scale_vct(h, ( (p->rot_vct.x > 0) * GRIDSIZE - x_pos  % GRIDSIZE)) ), 0xff00ae );
	

	draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, 50) ), 0xfffb00);
	draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, 30) ), 0x00ffcc);

	for (float i = p->rot_rad - PI_90 / 2; i < p->rot_rad + PI_90 / 2; i+=0.01)
	{
		t_vct cast = getfunc(p->pos, i);
		if (cast.x != -1 && cast.y != -1)
			draw_line(p->pos, cast, 0x002200FF);
	}
	

	put_image(rnd);
	updatefps(rnd);
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
	//t_vct grid = pos_to_grid(player()->pos);
	char *x = lib_itoa(p->pos.x);
	char *y = lib_itoa(p->pos.y);
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
