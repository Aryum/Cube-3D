#include "var_hlp.h"

t_quad	ini_quad(t_vct grid)
{
	t_quad ret;

	ret.pos[0] = scale_vct(grid, GRIDSIZE);
	ret.pos[1] = add_vct(ret.pos[0], ini_vct_pos(GRIDSIZE,0));
	ret.pos[2] = add_vct(ret.pos[0], ini_vct_pos(0,GRIDSIZE));
	ret.pos[3] = add_vct(ret.pos[0], ini_vct_pos(GRIDSIZE,GRIDSIZE));
	return (ret);
}