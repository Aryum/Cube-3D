#include "ray.h"

t_vct	raycast_old(t_vct start, float rad)
{
	t_vct rot_vct;

	rot_vct = ini_vct_rad(rad);
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
	return (ini_vct_pos(-1, -1));
}
