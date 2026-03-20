#include "input.h"

int	key_update(int code, bool status)
{
	t_input	*cur;
	int	i;

	i = 0;
	while (i < KEYCOUNT)
	{
		if (data()->input[i].code == code)
		{
			cur = &data()->input[i];
			if (cur->func != NULL && !cur->status)
				data()->input[i].func();
			cur->status = status;
			break;
		}
		i++;
	}
	return (0);
}

int	key_press(int code)
{
	return (key_update(code, true));
}

int	key_release(int code)
{
	return (key_update(code, false));
}

bool	key_read(t_keys key)
{
	t_input	*input;
	int		neg;

	input = data()->input;
	neg = input[key].neg_key;
	if (input[key].status)
		return (neg == -1 || !input[neg].status);
	return (false);
}

