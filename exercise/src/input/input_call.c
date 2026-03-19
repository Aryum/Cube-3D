#include "input.h"

int	key_update(int code, bool status)
{
	int	i;

	i = 0;
	while (i < KEYCOUNT)
	{
		if (data()->input[i].code == code)
		{
			data()->input[i].status = status;
			if (!data()->input[i].hold_call)
				data()->input[i].func();
			break;
		}
		i++;
	}
	return (0);
}

int	key_press(int code)
{
	return (0);
	return (key_update(code, true));
}

int	key_release(int code)
{
	return (0);
	return (key_update(code, false));
}

void	key_hold()
{
	t_input	*cur;
	int		i;

	i = 0;
	while (i < KEYCOUNT)
	{
		cur = &data()->input[i];
		if (cur->hold_call && cur->status && cur->func != NULL)
			cur->func();
		i++;
	}
}