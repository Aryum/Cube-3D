#include "render.h"

static void	loop_map(t_map	*mp, void (*f)(char **, int, int))
{
	int		x;
	int		y;

	y = 0;
	while (y < mp->len_y)
	{
		x = 0;
		while (x < mp->len_x)
		{
			f(mp->layout, x, y);
			x++;
		}
		y++;
	}
}

void draw(char **map, int x, int y)
{
	t_vct	limit;
	t_vct	cur;
	int		border;

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
	rnd->total_frames++;
	if (cur - rnd->last_time > a)
	{
		rnd->fps = (rnd->frame_count) * ( 1000 / a);
		rnd->frame_count = 0;
		rnd->last_time = cur;
	}
	else
		rnd->frame_count++;
}

t_vct v_abs(t_vct vct)
{
	return ini_vct_pos(f_abs(vct.x), f_abs(vct.y));
}





int render_loop(void)
{
	t_render *rnd;
	t_player	*p;

	rnd = render();
	p = player();

	//minimap
	if (0)
	{
		loop_map(map(), draw);
		draw_circle(p->pos, 5, 0xff0000);
		

		//move and facing vct
		draw_line(p->pos, add_vct(p->pos, scale_vct(p->rot_vct, MOV_SPEED) ), 0xfffb00);
		draw_line(p->pos, add_vct(p->pos, scale_vct(p->mov_vct, MOV_SPEED) ), 0x00ffcc);
		t_vct	v = ini_vct_pos(0, p->mov_vct.y * MOV_SPEED);
		t_vct	h = ini_vct_pos(p->mov_vct.x * MOV_SPEED,0);
		draw_line(p->pos, add_vct(p->pos, v), 0x000000ff);
		draw_line(p->pos, add_vct(p->pos, h ), 0x0000ffff);
		t_quad p_quad = ini_quad(pos_to_grid(p->pos));
		t_quad v_quad = ini_quad(pos_to_grid(add_vct(p->pos, v)));
		t_quad h_quad = ini_quad(pos_to_grid(add_vct(p->pos, h)));
		draw_quad(p_quad, 0x00ff00ff);
		if (v_quad.grid.y != p_quad.grid.y)
			draw_quad(v_quad, 0x000000ff);
		if ( h_quad.grid.x != p_quad.grid.x )
			draw_quad(h_quad, 0x0000ffff);
	}
	else
	{
		//quad based raycast
		float div = (float)rnd->window_x;
		float fov = PI_90;
		float delta = fov / div;
		int a = 0;
		for (float i = -fov / 2 ; i < fov / 2; i+=delta)
		{
			float rad = add_rad(p->rot_rad, i * fov / 2);
			t_ray ray =  ini_ray(p->pos, ini_vct_rad(rad), hit_wall);
			t_rayhit hit = raycast(ray);
			if (hit.sucess)
			{
				//float angle = add_rad(p->rot_rad, i);
				float dist = dist_vct(p->pos, hit.pos) * cos(add_rad(p->rot_rad, -rad));
				float size = render()->window_y * GRIDSIZE / dist;
				t_vct center = ini_vct_pos(a * rnd->window_x /div , rnd->window_y / 2);
				center.y += sin(p->tilt) * (float)(rnd->window_y / 2);
				t_vct sq_size = ini_vct_pos(rnd->window_x / div , size);
				int color[4];
				color[dir_east] = 0x00ff0000;
				color[dir_west] = 0x000000ff;
				color[dir_north] = 0x00ff00ff;
				color[dir_south] = 0x0000ff00;
				draw_square(center, sq_size, color[hit.dir]);
			}
			a++;
		}
		
		for (int y = -5; y <= 5; y++)
		{
			for (int x = -5; x <= 5; x++)
			{
				draw_minisquare(rnd->minimap, x, y);
			}
		}
		draw_circle(rnd->minimap.center, 10,  0xFA05EE);

		//t_vct	corner = ini_vct_pos(rnd->window_x, rnd->window_y);
		//t_vct	size = ini_vct_pos(250, 250);
		//t_vct	center = add_vct(corner, scale_vct(size, -0.5));
		//draw_square(center, size, 0xffffff);
		//t_vct	left = ini_vct_rad(add_rad(p->rot_rad, -fov / 2));
		//t_vct	right = ini_vct_rad(add_rad(p->rot_rad, fov / 2));
		//draw_line(center, add_vct(center, scale_vct(left, MOV_SPEED) ), 0x000000);
		//draw_line(center, add_vct(center, scale_vct(right, MOV_SPEED) ), 0xfffb00);
	}
	

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
	t_vct grid = grid_distance(player()->pos);
	char *x = lib_itoa((int) (grid.x) );
	char *y = lib_itoa((int) (grid.y));
	mlx_string_put(rnd->mlx, rnd->window, 10, 50,0x002200FF, x);
	free(x);
	mlx_string_put(rnd->mlx, rnd->window, 40, 50,0x002200FF , y);
	free(y);

	//rot
	char *rot = lib_itoa((p->tilt * 360) / (2 * PI));
	char *rot_tmp = lib_strjoin("rot: ", rot);
	free(rot);
	mlx_string_put(rnd->mlx, rnd->window, 10, 75,0x00ff00d9 , rot_tmp);
	free(rot_tmp);
	return 0;
}
