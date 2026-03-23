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

	ret.x = clamp((int)pos.x / GRIDSIZE, 0, map()->size_x);
	ret.y = clamp((int)pos.y / GRIDSIZE, 0, map()->size_y);
	return (ret);
}

t_vct	grid_to_pos(t_vct pos)
{
	t_vct	ret;

	ret.x = pos.x * GRIDSIZE + GRIDSIZE / 2;
	ret.y = pos.y * GRIDSIZE + GRIDSIZE / 2;
	return (ret);
}


t_vct	grid_distance(t_vct pos, t_vct rot)
{
	t_vct ret;

	ret.x = (rot.x > 0) * GRIDSIZE - (int)floor(pos.x) % GRIDSIZE ;
	ret.y = (rot.y > 0) * GRIDSIZE - (int)floor(pos.y) % GRIDSIZE ;
	return (ret);
}

t_vct v_abs(t_vct vct)
{
	return ini_vct(f_abs(vct.x), f_abs(vct.y));
}

float raysize(t_vct rad, t_vct dist)
{
	float ret;

	rad = v_abs(rad);
	dist = v_abs(dist);

	if (dist.x / rad.x < dist.y / rad.y)
		ret = dist.x / rad.x;
	else
		ret = dist.y / rad.y;
	return ret;
}


t_quad	ini_quad(t_vct grid)
{
	t_quad ret;

	ret.pos[0] = scale_vct(grid, GRIDSIZE);
	ret.pos[1] = add_vct(ret.pos[0], ini_vct(GRIDSIZE,0));
	ret.pos[2] = add_vct(ret.pos[0], ini_vct(0,GRIDSIZE));
	ret.pos[3] = add_vct(ret.pos[0], ini_vct(GRIDSIZE,GRIDSIZE));
	return (ret);
}

void	draw_quad(t_quad quad, int color)
{
	draw_line(quad.pos[0], quad.pos[1], color);
	draw_line(quad.pos[0], quad.pos[2], color);
	draw_line(quad.pos[3], quad.pos[1], color);
	draw_line(quad.pos[3], quad.pos[2], color);
}

t_vct	quad_col(t_vct pos, t_vct rad)
{
	t_vct tar;
	t_quad quad;
	float m;
	float b;

	quad = ini_quad(pos_to_grid(pos));
	if (rad.x == 0)
	{
		if (rad.y > 0)
			return ( ini_vct(pos.x, quad.pos[0].y));
		else
			return ( ini_vct(pos.x, quad.pos[3].y));
	}
	if (rad.x > 0)
		tar.x = quad.pos[3].x;
	else
		tar.x = quad.pos[0].x;

	if (rad.y > 0)
		tar.y = quad.pos[3].y;
	else
		tar.y = quad.pos[0].y;
	m = rad.y / rad.x;
	b = pos.y - pos.x * m;

	//loop where it increases target
	while (1)
	{
		if (f_abs((tar.x - pos.x) / rad.x) < f_abs((tar.y - pos.y) / rad.y))
		{
			t_vct grid_pos = pos_to_grid(pos);
			grid_pos = add_vct(grid_pos, ini_vct(rad.x / f_abs(rad.x), 0));
			if (map()->layout[(int)grid_pos.y][(int)grid_pos.x] == '1')
			{
				for (int i = -1; i < 1; i++)
					draw_line(ini_vct(tar.x + i, 0), ini_vct(tar.x + i, render()->window_y), 0x00ff0000);
				return (ini_vct(tar.x, tar.x * m + b));
			}
			pos = ini_vct(tar.x, tar.x * m + b);
			tar.x += (rad.x / f_abs(rad.x)) * GRIDSIZE;
			if (reached_clamp(&tar.x, 0, render()->window_x))
				break;
		}
		else
		{
			t_vct grid_pos = pos_to_grid(pos);
			grid_pos = add_vct(grid_pos, ini_vct(0, rad.y / f_abs(rad.y)));
			if (map()->layout[(int)grid_pos.y][(int)grid_pos.x] == '1')
			{
				for (int i = -1; i < 1; i++)
					draw_line(ini_vct(0, tar.y + i), ini_vct(render()->window_x, tar.y+i), 0x00ff0000);
				return (ini_vct((tar.y - b) / m, tar.y));
			}
			pos = ini_vct((tar.y - b) / m, tar.y);
			tar.y += (rad.y / f_abs(rad.y)) * GRIDSIZE;
			if (reached_clamp(&tar.y, 0, render()->window_y))
				break;
		}
	}
	return (ini_vct(-1,-1));
	
}

t_vct	raycast(t_vct start, float rad)
{
	t_vct rot_vct;

	rot_vct = rad_vector(rad);
	t_vct dist = grid_distance(start, rot_vct);
	float size = raysize(rot_vct, dist);
	start = add_vct(start, scale_vct(rot_vct, size));
	while (1)
	{
		if (reached_clamp(&start.x, 0, render()->window_x))
			break;
		if (reached_clamp(&start.y, 0, render()->window_y))
			break;
		t_vct tmp = pos_to_grid(start);
		if (map()->layout[(int) tmp.y][(int) tmp.x] == '1')
			return (start);
		start = add_vct(start, scale_vct(rot_vct, GRIDSIZE / 10));
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
	

	//move and facing vct
	//draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, 50) ), 0xfffb00);
	//draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, 30) ), 0x00ffcc);

	//quad based raycast
	t_vct quadcol = quad_col(p->pos, p->rot_vct);
	if (quadcol.x != -1)
		draw_line(p->pos, quadcol, 0x00ff0000);

	// raycast working but slow
	/*
	for (float i = -1; i <= 1; i+=0.005)
	{
		t_vct cast = raycast(p->pos, p->rot_rad + i * PI_90 / 2);
		if (0)
			draw_line(p->pos, cast, 0x00ff0000);
	}
	*/
	//vertical
	//t_vct v = ini_vct(0,1);
	//t_vct dist = grid_distance(p->pos, p->rot_vct);
	//draw_line(p->pos, add_vct(p->pos, scale_vct(v, dist.y) ), 0xff00ae);
	//t_vct h = ini_vct(1,0);
	//draw_line(p->pos, add_vct(p->pos, scale_vct(h, dist.x) ), 0xff00ae );
	
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
	mlx_string_put(rnd->mlx, rnd->window, 25, 25, 0x00ff0000, fps);
	free(fps);


	//cords
	//t_vct grid = pos_to_grid(player()->pos);
	char *x = lib_itoa((int) (p->rot_vct.x * 10.0) );
	char *y = lib_itoa((int) (p->rot_vct.y * 10.0));
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
