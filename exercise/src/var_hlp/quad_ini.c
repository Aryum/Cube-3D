#include "var_hlp.h"

t_quad	ini_quad(t_vct grid)
{
	t_quad ret;

	ret.grid = grid;
	ret.pos[0] = vct_scale(grid, GRIDSIZE);
	ret.pos[1] = vct_add(ret.pos[0], ini_vct_pos(GRIDSIZE,0));
	ret.pos[2] = vct_add(ret.pos[0], ini_vct_pos(0,GRIDSIZE));
	ret.pos[3] = vct_add(ret.pos[0], ini_vct_pos(GRIDSIZE,GRIDSIZE));
	return (ret);
}