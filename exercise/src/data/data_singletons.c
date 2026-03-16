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

int	key_press(int key)
{
	int	i;

	i = 0;
	while (i < KEYCOUNT)
	{
		if (data()->key_code[i] == key)
		{
			if(data()->key_func[i] != NULL)
			{
				printf("Key %d\n", data()->key_code[i]);
				data()->key_func[i]();
			}
			break;
		}
		i++;
	}
	if (i == KEYCOUNT)
		printf("Key not mapped\n");
	return 0;
}
