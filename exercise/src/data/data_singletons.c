#include "data.h"

t_data	*data()
{
	static	t_data dt;

	return (&dt);
}

t_player	*player()
{
	return (&data()->player);
}

t_render	*render()
{
	return (&data()->render);
}

t_map	*map()
{
	return (&data()->map);
}


