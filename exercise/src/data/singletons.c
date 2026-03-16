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

void	press_key(int key)
{
	if (key >= KEYCOUNT)
	{
		print_fd(2, "Key is bigger than keycount\n");
		return ;
	}
	data()->key_func[key]();
}